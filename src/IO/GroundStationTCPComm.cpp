#include "GroundStationTCPComm.h"
#include <GroundStationComm.pb.h>
#include <spdlog/spdlog.h>

#include <utility>

GroundStationTCPComm::GroundStationTCPComm(EventQueue &eventQueue)
    : GroundStationComm(eventQueue), sendingSocket(zmq_ctx, zmq::socket_type::pub),
      receiveSocket(zmq_ctx, zmq::socket_type::rep), sendingMonitor(sendingSocket, "inproc://sending", "sending"),
      receiveMonitor(receiveSocket, "inproc://receive", "receive")
{
    sendingSocket.bind("tcp://0.0.0.0:8080");
    receiveSocket.bind("tcp://0.0.0.0:8081");

    // Note. The receiveSocket is not thread safe. However, creating a thread creates a full memory barrier,
    // which makes this safe. However, this socket should no longer be used in this thread, only in the new thread.
    std::thread receiveThread(&GroundStationTCPComm::receiveLoop, this);
    receiveThread.detach();
}

void GroundStationTCPComm::sendMessage(const RocketryProto::GroundStationIn &message)
{
    //    sendingMonitor.check_event(10);
    auto packet = GroundStationEncoder::encode(message);

    zmq::message_t msg(packet.data.get(), packet.length);

    auto res = sendingSocket.send(msg, zmq::send_flags::dontwait);
    if (!res.has_value())
    {
        SPDLOG_WARN("Could not send message to ground-station, queue is full. Dropping it...");
    }
}

[[noreturn]] void GroundStationTCPComm::receiveLoop()
{
    while (true)
    {
        zmq::message_t msg;
        auto res = receiveSocket.recv(msg);
        if (!res.has_value())
        {
            SPDLOG_WARN("Error receiving message. Ignoring it...");
            continue;
        }

        auto pbData = GroundStationEncoder::decode<RocketryProto::GroundStationOut>(msg.data(), msg.size());

        receiveSocket.send(zmq::message_t("", 0), zmq::send_flags::none);

        handleMessage(pbData);
    }
}

GroundStationTCPCommMonitor::GroundStationTCPCommMonitor(zmq::socket_t &socket, const char *addr,
                                                         std::string socketName)
    : socketName(std::move(socketName))
{
    init(socket, addr);
    auto thread = std::thread([this] {
        while (check_event(-1))
        {
        }
    });
    thread.detach();
}

void GroundStationTCPCommMonitor::on_event_accepted(const zmq_event_t &event, const char *addr)
{
    SPDLOG_INFO("New client connected on {} socket", socketName);
}

void GroundStationTCPCommMonitor::on_event_disconnected(const zmq_event_t &event_, const char *addr_)
{
    SPDLOG_INFO("Client disconnected on {} socket", socketName);
}
