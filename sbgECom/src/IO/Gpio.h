#pragma once

#include "config/config.h"
#if USE_GPIO

#include "../data/sensorsData.h"
#include "IO.h"
#include <queue>
#include <mutex>
#include <thread>
#include <fstream>
#include <iostream>
#include <condition_variable>

class Gpio : public IO
{
public:
	~Gpio();

	void initialize();
	void run();
	bool isInitialized();

protected:
	std::mutex mutex;

private:

	std::thread thisThread;

	//queue of sensor data to be logged
	std::queue<sensorsData> logQueue;

	std::mutex writingMutex;
	std::unique_lock<std::mutex> writingLock;
	std::condition_variable writingCondition;
	
	struct InitFlags
	{
		InitStatus gpioSatus = INIT;
	} status;
};

#endif