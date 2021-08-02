#include "config/config.h"
#if USE_SOCKET_CLIENT == 1

#include "SocketClient.h"
#include "../data/SBGData.h"
#include "IO.h"
#include "../helpers/Types.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <data/sensorsData.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <spdlog/spdlog.h>

using namespace std::chrono_literals;
using namespace boost::asio;

#define PORT 8080

SocketClient::SocketClient(EventQueue &eventQueue) :
    eventQueue(eventQueue), 
    sendingBuffer(SENDING_BUFFER_CAPACITY),
    endpoint(boost::asio::ip::tcp::v4(), PORT),
    acceptor(io_service, endpoint) 
{
}

SocketClient::~SocketClient()
{
}

void SocketClient::run()
{
    waitForConnection();
}

void SocketClient::waitForConnection() {
    SPDLOG_LOGGER_INFO(logger, "Waiting for connection...");
    auto socket(std::make_shared<ip::tcp::socket>(io_service));

    boost::system::error_code err;
    acceptor.accept(*socket, err);
    if (err) {
        SPDLOG_LOGGER_ERROR(logger, err.message());
    } else {
        connected++;
        SPDLOG_LOGGER_INFO(logger, "Connected to device. Currently connected to {} clients", connected);

        std::thread sendingThread([this, socket] { sendingLoop(socket); });
        sendingThread.detach();
        std::thread recievingThread([this, socket] { receivingLoop(socket); });
        recievingThread.detach();
    }

    // Wait for another connection
    std::thread waitingThread([this] { waitForConnection(); });
    waitingThread.detach();
}

void SocketClient::sendingLoop(const std::shared_ptr<ip::tcp::socket> &socket) {
    std::unique_lock<std::mutex> lk(sendingMutex);
    while (socket->is_open()) {
        sendingCondition.wait_for(lk, 100ms);

        while (!sendingBuffer.empty() && socket->is_open()) {
            boost::system::error_code err;
            if (write(*socket, buffer(sendingBuffer[0]), err) == -1 || err) {
                if (err) {
                    SPDLOG_LOGGER_ERROR(logger, err.message());
                } else {
                    SPDLOG_LOGGER_ERROR(logger, "Could not successfully send the TCP message");
                }
            }

            sendingBuffer.pop_front();
        }
    }
}

void SocketClient::receivingLoop(const std::shared_ptr<ip::tcp::socket> &socket) {
    while (socket->is_open()) {
        char b[1] = {(char)-1};
        boost::system::error_code err;
        socket->read_some(buffer(b), err);

        SPDLOG_LOGGER_INFO(logger, "Recieved data: {}", (int) b[0]);

        if (err) {
            SPDLOG_LOGGER_ERROR(logger, err.message());

            if (err == boost::asio::error::eof) { 
                SPDLOG_LOGGER_INFO(logger, "Connection closed by the device");
                socket->close();
                return;
            }
        } else {
            eventQueue.push((int)b[0]);
        }
    }

    connected--;
}

void SocketClient::enqueueSensorData(const sensorsData &data) {
    auto dataStr = data.convertToReducedString();
    dataStr += "\r\n";

    std::lock_guard<std::mutex> guard(sendingMutex);
    sendingBuffer.push_back(dataStr);

    sendingCondition.notify_one();
}

void SocketClient::initialize()
{
    std::cout << "initialize client thread"
              << "\n";
    IO::initialize();
};

bool SocketClient::isInitialized()
{
    return (status.socketCreated == READY && status.socketBinded == READY && status.serverConnection == READY);
}

#endif
