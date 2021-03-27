#include "config/config.h"
#if USE_GPIO

#include "IO/Gpio.h"
#include "data/sensorsData.h"
#include "IO/PwmOutput.h"

#include "helpers/Helper.h"
#include <string>
#include <iostream>

#if USE_WIRING_Pi
#include <wiringPi.h>
#endif


Gpio::~Gpio()
{
}

void Gpio::run() {
	return;
}


void Gpio::initialize()
{

	#if USE_WIRING_Pi
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

void Gpio::setOutputs(const GpioData data) {
	for (std::pair<std::string, int> output : data.pwmOutputMap)
	{
		pwmOutputsMap.at(output.first).setValue(output.second);
	}
	for (std::pair<std::string, int> output : data.outputMap)
	{
		outputsMap.at(output.first).setValue(output.second);
	}
}

void Gpio::createNewGpioOutput(std::string name, int pinNbr) {
	outputsMap.insert({name, Output(name, pinNbr)});

}

void Gpio::createNewGpioPwmOutput(std::string name, int pinNbr) {
	pwmOutputsMap.insert({name, PwmOutput(name, pinNbr)});

}

#endif
