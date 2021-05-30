#include "config/config.h"
#if USE_GPIO == 1

#include "Gpio.h"
#include "data/sensorsData.h"

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

GpioData Gpio::setOutputs(const GpioData& data) {
	for (std::pair<std::string, int> output : data.pwmOutputMap)
	{
		pwmOutputsMap.at(output.first).setValue(output.second);
	}
	for (std::pair<std::string, int> output : data.digitalOutputMap)
	{
		digitalOutputsMap.at(output.first).setValue(output.second);
	}

	GpioData result;
	result.digitalOutputMap = toRawMap(digitalOutputsMap);
	result.pwmOutputMap = toRawMap(pwmOutputsMap);

	return result;
}

void Gpio::createNewGpioOutput(const std::string& name, int pinNbr) {
	digitalOutputsMap.insert({name, DigitalOutput(name, pinNbr)});
}

void Gpio::createNewGpioPwmOutput(const std::string &name, int pinNbr, bool softPWM) {
	pwmOutputsMap.insert({name, PwmOutput(name, pinNbr, softPWM)});
}

/**
 * Convert a map with Output to a map with numbers
 */
template<typename T, typename std::enable_if<std::is_base_of<Output, T>::value>::type*>
std::map<std::string, int> Gpio::toRawMap(std::map<std::string, T> map) {
	std::map<std::string, int> result;
	for (std::pair<const std::string, T> output : map)
	{
		result.insert({output.first, output.second.getValue()});
	}

	return result;
}

#endif
