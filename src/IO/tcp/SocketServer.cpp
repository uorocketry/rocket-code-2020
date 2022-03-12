#include "config.h"

#include "SocketServer.h"
#include "common/pch.h"
#include <chrono>
#include <data/SensorsData.h>
#include <spdlog/spdlog.h>
#include <thread>

using namespace boost::asio;

#define PORT 8080

SocketServer::SocketServer(EventQueue &eventQueue)
    : eventQueue(eventQueue), sendingBuffer(SENDING_BUFFER_CAPACITY), endpoint(boost::asio::ip::tcp::v4(), PORT),
      acceptor(io_service, endpoint)
{
}

SocketServer::~SocketServer()
{
}

void SocketServer::run()
{
    std::thread sendingThread([this] { sendingLoop(); });
    sendingThread.detach();

    waitForConnection();
}

void SocketServer::waitForConnection()
{
    SPDLOG_INFO("Waiting for connection...");
    auto socket(std::make_shared<ip::tcp::socket>(io_service));

    initialized = true;

    boost::system::error_code err;
    acceptor.accept(*socket, err);
    if (err)
    {
        SPDLOG_ERROR(err.message());
    }
    else
    {
        SPDLOG_ERROR("Connected to device. Currently connected to {} clients", clients.size() + 1);

        std::shared_ptr<SocketClient> client = std::make_shared<SocketClient>(
            socket, [this](auto b) { this->received(b); }, [this](auto client) { this->closed(client); });
        clients.push_back(client);
    }

    // Wait for another connection
    std::thread waitingThread([this] { waitForConnection(); });
    waitingThread.detach();
}

void SocketServer::sendingLoop()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(sendingMutex);
        sendingCondition.wait_for(lk, MAX_WAIT);

        while (!sendingBuffer.empty())
        {
            auto data = sendingBuffer.front();

            std::lock_guard<std::mutex> lockGuard(clientsMutex);

            for (auto &client : clients)
            {
                client->send(data);
            }

            sendingBuffer.pop_front();
        }
    }
}

void SocketServer::received(const char b[])
{
    eventQueue.push((int)b[0]);
}

void SocketServer::closed(const SocketClient *client)
{
    std::lock_guard<std::mutex> lockGuard(clientsMutex);

    clients.erase(std::remove_if(clients.begin(), clients.end(),
                                 [client](const std::shared_ptr<SocketClient> &c) { return c.get() == client; }),
                  clients.end());
}

void SocketServer::enqueueSensorData(const SensorsData &data)
{
    auto dataStr = data.convertToReducedString();
    dataStr += "\r\n";

    std::lock_guard<std::mutex> guard(sendingMutex);
    sendingBuffer.push_back(dataStr);

    sendingCondition.notify_one();
}

bool SocketServer::isInitialized()
{
    return initialized;
}

uint64_t SocketServer::getLastConnectionTimestamp()
{
    std::lock_guard<std::mutex> lockGuard(clientsMutex);

    if (!clients.empty())
    {
        lastConnectionTimestamp =
            std::chrono::duration_cast<time_point::duration>(std::chrono::steady_clock::now().time_since_epoch())
                .count();
    }

    return lastConnectionTimestamp;
}