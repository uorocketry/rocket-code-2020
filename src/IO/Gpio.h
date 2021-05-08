#pragma once

#include "config/config.h"
#if USE_GPIO == 1

#include "../data/GpioData.h"
#include "IO.h"
#include "IO/PwmOutput.h"
#include "IO/Output.h"
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

	void initialize() override;
	void run() override;
	bool isInitialized() override;

	void createNewGpioOutput(const std::string& name, int pinNbr);
	void createNewGpioPwmOutput(const std::string& name, int pinNbr);

	void setOutputs(const GpioData& data);

protected:
	std::mutex mutex;

private:
	std::unordered_map<std::string, Output> outputsMap;
	std::unordered_map<std::string, PwmOutput> pwmOutputsMap;

	struct InitFlags
	{
		InitStatus gpioSatus = INIT;
	} status;
};

#endif