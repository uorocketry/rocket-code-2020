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

class SocketClient : public IO
{
public:
    SocketClient(EventQueue &eventQueue);
    ~SocketClient();

    [[noreturn]] void run();
    void initialize();
    bool isInitialized();
    void enqueueSensorData(const sensorsData &data);

private:
    void sendingLoop(int sock);

    const int SENDING_BUFFER_CAPACITY = 32;

    bool connected = false;

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
