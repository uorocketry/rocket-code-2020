#pragma once

#ifndef TESTING

#include "IO.h"
#include "../data/SBGData.h"
#include <iostream>

class SocketClient : public IO {
public:
    SocketClient();
    ~SocketClient();
    
	void run();
	void initialize();

    int getData();
	// rocketState getLatest();
};

#endif
