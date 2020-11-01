#pragma once

#include "config/config.h"
#if USE_SOCKET_CLIENT

#include "IO.h"
#include "../data/SBGData.h"
#include <iostream>
#include <queue>

class SocketClient : public IO
{
public:
	SocketClient();
	~SocketClient();

	void run();
	void initialize();
	bool isInitialized();

	int getData();
	// rocketState getLatest();

private:
	std::queue<int> eventNumberQueue;

	struct InitFlags
	{
		InitStatus socketCreated = INIT;
		InitStatus socketBinded = INIT;
		InitStatus serverConnection = INIT;
	} status;
};

#endif
