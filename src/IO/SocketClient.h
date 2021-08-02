#pragma once

#include "config/config.h"
#if USE_SOCKET_CLIENT == 1

#include "IO.h"
#include "../data/SBGData.h"
#include "EventQueue.h"
#include <iostream>
#include <queue>
#include <boost/circular_buffer.hpp>
#include <data/sensorsData.h>
#include <condition_variable>
#include <boost/asio.hpp>

class SocketClient : public IO
{
public:
    SocketClient(EventQueue &eventQueue);
    ~SocketClient();

    void run();
    void initialize();
    bool isInitialized();
    void enqueueSensorData(const sensorsData &data);

private:
    void sendingLoop(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket);
    void receivingLoop(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket);
    void waitForConnection();

    const int SENDING_BUFFER_CAPACITY = 32;

    int connected = 0;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::acceptor acceptor;

    EventQueue &eventQueue;
    boost::circular_buffer<std::string> sendingBuffer;

    std::condition_variable sendingCondition;
    std::mutex sendingMutex;

    struct InitFlags
    {
        InitStatus socketCreated = INIT;
        InitStatus socketBinded = INIT;
        InitStatus serverConnection = INIT;
    } status;
};

#endif
