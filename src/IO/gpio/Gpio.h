#pragma once

#include "config/config.h"
#if USE_GPIO == 1

#include "data/GpioData.h"
#include "IO/IO.h"
#include "IO/gpio/PwmOutput.h"
#include "IO/gpio/DigitalOutput.h"
#include <queue>
#include <mutex>
#include <thread>
#include <fstream>
#include <iostream>
#include <condition_variable>
#include <string>
#include <map>

class Gpio : public IO
{
public:
	~Gpio();

	void initialize() override;

	void run() override;

	bool isInitialized() override;

	void createNewGpioOutput(const std::string &name, int pinNbr);

	void createNewGpioPwmOutput(const std::string &name, int pinNbr, bool softPWM = false);

	GpioData setOutputs(const GpioData &data);

protected:
	std::mutex mutex;

private:
	std::map<std::string, DigitalOutput> digitalOutputsMap;
	std::map<std::string, PwmOutput> pwmOutputsMap;

	struct InitFlags
	{
		InitStatus gpioSatus = INIT;
	} status;

	template<typename T, typename std::enable_if<std::is_base_of<Output, T>::value>::type* = nullptr>
	std::map<std::string, int> toRawMap(std::map<std::string, T> map);
};

#endif