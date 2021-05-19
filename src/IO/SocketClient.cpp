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

#define PORT 8080
#define HOST_IP "127.0.0.1"
#define RECONNECT_WAIT_TIME_NS duration_ns(1000000000) // 1 second
#define UPDATE_WAIT_TIME_NS duration_ns(10000000)      // 100th of a second

/**
 * Send the specified data over the socket. This function will try to send all of the data, making multiple send()
 * calls if necessary.
 * @return 0 if everything was sent successfully, -1 otherwise
 */
int sendTCPData(int socket, const char *data, int length) {
    int data_sent = 0;
    while (data_sent < length) {
        int bytes_sent = send(socket, data+data_sent, length-data_sent, 0);
        if (bytes_sent == -1) {
            return bytes_sent;
        }
        data_sent += bytes_sent;
    }

    return 0;
}

SocketClient::SocketClient(EventQueue &eventQueue) : eventQueue(eventQueue), sendingBuffer(SENDING_BUFFER_CAPACITY) {}

SocketClient::~SocketClient()
{
}

[[noreturn]] void SocketClient::run()
{
    while (true)
    {
        connected = false;

        std::this_thread::sleep_for(RECONNECT_WAIT_TIME_NS);
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            SPDLOG_LOGGER_ERROR(logger, "Socket creation error");
            continue;
        }

        status.socketCreated = READY;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, HOST_IP, &serv_addr.sin_addr) <= 0)
        {
            SPDLOG_LOGGER_ERROR(logger, "Invalid address / Address not supported");
            continue;
        }

        status.socketBinded = READY;

        SPDLOG_LOGGER_INFO(logger, "Trying to connect...");
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
        {
            SPDLOG_LOGGER_INFO(logger, "Connected");
            connected = true;

            std::thread sendingThread(&SocketClient::sendingLoop, this, sock);

            status.serverConnection = READY;

            char buffer[1] = {(char)-1};
            while (connected)
            {
                valread = read(sock, buffer, 1);

                if (valread == 0)
                {
                    connected = false;
                    close(sock);
                }

                eventQueue.push((int)buffer[0]);

                std::this_thread::sleep_for(UPDATE_WAIT_TIME_NS);
            }
        }
    }
}

void SocketClient::sendingLoop(int sock) {
    std::unique_lock<std::mutex> lk(sendingMutex);
    while (connected) {
        sendingCondition.wait_for(lk, 100ms, [this]{return !connected;});

        while (!sendingBuffer.empty()) {
            auto data = sendingBuffer[0].c_str();

            int error = sendTCPData(sock, data, strlen(data));
            if (error == -1) {
                std::cout << "Could not successfully send the TCP message" << std::endl;
            }
            sendingBuffer.pop_front();
        }
    }
}

void SocketClient::enqueueSensorData(const sensorsData &data) {
    auto dataStr = data.convertToReducedString();

    {
        std::lock_guard<std::mutex> guard(sendingMutex);
        sendingBuffer.push_back(dataStr);
    }
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
