#include "config/config.h"
#if USE_SOCKET_CLIENT == 1

#include "SocketClient.h"
#include "../data/SBGData.h"
#include "IO.h"
#include "../helpers/Types.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <queue>
#include <spdlog/spdlog.h>

#define PORT 8080
#define HOST_IP "127.0.0.1"
#define RECONNECT_WAIT_TIME_NS duration_ns(1000000000) // 1 second
#define UPDATE_WAIT_TIME_NS duration_ns(10000000)      // 100th of a second

SocketClient::SocketClient(EventQueue &eventQueue) : eventQueue(eventQueue) {}

SocketClient::~SocketClient()
{
}

void SocketClient::run()
{
    while (true)
    {
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

            status.serverConnection = READY;

            char buffer[1] = {(char)-1};
            bool connected = true;
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
