#pragma once

#include "config/config.h"
#if USE_SOCKET_CLIENT

#include "IO.h"
#include "../data/SBGData.h"
#include "EventQueue.h"
#include <iostream>
#include <queue>

class SocketClient : public IO
{
public:
    SocketClient(EventQueue &eventQueue);
    ~SocketClient();

    void run();
    void initialize();
    bool isInitialized();

    // rocketState getLatest();

private:
    EventQueue &eventQueue;

    struct InitFlags
    {
        InitStatus socketCreated = INIT;
        InitStatus socketBinded = INIT;
        InitStatus serverConnection = INIT;
    } status;
};

#endif
