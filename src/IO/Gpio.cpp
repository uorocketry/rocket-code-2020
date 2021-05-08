#include "config/config.h"
#if USE_GPIO == 1

#include "IO/Gpio.h"
#include "data/sensorsData.h"
#include "IO/PwmOutput.h"

#include "helpers/Helper.h"
#include <string>
#include <iostream>

#if USE_WIRING_Pi == 1
#include <wiringPi.h>
#endif


Gpio::~Gpio()
= default;

void Gpio::run() {
	}


void Gpio::initialize()
{

	#if USE_WIRING_Pi == 1
	status.gpioSatus = (wiringPiSetupGpio() == 0) ? READY : INIT;
	#else
	status.gpioSatus = READY;
	#endif
	// init servos

	createThread = false;
	IO::initialize();
}

bool Gpio::isInitialized()
{
	return (status.gpioSatus == READY);
}

void Gpio::setOutputs(const GpioData& data) {
	for (std::pair<std::string, int> output : data.pwmOutputMap)
	{
		pwmOutputsMap.at(output.first).setValue(output.second);
	}
	for (std::pair<std::string, int> output : data.outputMap)
	{
		outputsMap.at(output.first).setValue(output.second);
	}
}

void Gpio::createNewGpioOutput(const std::string& name, int pinNbr) {
	outputsMap.insert({name, Output(name, pinNbr)});

}

void Gpio::createNewGpioPwmOutput(const std::string& name, int pinNbr) {
	pwmOutputsMap.insert({name, PwmOutput(name, pinNbr)});

}

#endif
