#pragma once

#include "config/config.h"
#if USE_SOCKET_CLIENT == 1

#include "IO/IO.h"
#include "data/SBGData.h"
#include "IO/EventQueue.h"
#include "SocketClient.h"
#include <iostream>
#include <queue>
#include <boost/circular_buffer.hpp>
#include <data/sensorsData.h>
#include <condition_variable>
#include <boost/asio.hpp>
#include <chrono>

class SocketServer : public IO
{
public:
    SocketServer(EventQueue &eventQueue);
    ~SocketServer();

    void run();
    bool isInitialized();
    void enqueueSensorData(const sensorsData &data);

private:
    void sendingLoop();
    void received(const char b[]);
    void closed(const SocketClient* client);
    void waitForConnection();

    const int SENDING_BUFFER_CAPACITY = 32;
    const duration_ms MAX_WAIT = duration_ms(1);

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::acceptor acceptor;

    std::vector<std::shared_ptr<SocketClient>> clients;
    std::mutex clientsMutex;

    EventQueue &eventQueue;
    boost::circular_buffer<std::string> sendingBuffer;

    std::condition_variable sendingCondition;
    std::mutex sendingMutex;

    bool initialized = false;
};

#endif
