#pragma once

#include "config/config.h"
#if USE_GPIO

#include "../data/GpioData.h"
#include "IO.h"
#include "IO/PwmOutput.h"
#include <queue>
#include <mutex>
#include <thread>
#include <fstream>
#include <iostream>
#include <condition_variable>
#include <string>
#include <unordered_map>

class Gpio : public IO
{
public:
	~Gpio();

	void initialize();
	void run();
	bool isInitialized();

	void createNewGpioPwmOutput(std::string name, int pinNbr);
	void setOutputs(const GpioData data);

protected:
	std::mutex mutex;

private:
	std::unordered_map<std::string, PwmOutput> pwmOutputsMap;

	struct InitFlags
	{
		InitStatus gpioSatus = INIT;
	} status;
};

#endif