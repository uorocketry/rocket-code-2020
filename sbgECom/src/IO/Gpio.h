#pragma once

#include "config/config.h"
#if USE_GPIO

#include "../data/GpioData.h"
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

	void setOutputs(const GpioData data);

protected:
	std::mutex mutex;

private:
	
	struct InitFlags
	{
		InitStatus gpioSatus = INIT;
	} status;
};

#endif