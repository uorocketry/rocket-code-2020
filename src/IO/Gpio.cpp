#include "config/config.h"
#if USE_GPIO

#include "Gpio.h"
#include "data/sensorsData.h"

#include "helpers/Helper.h"
#include <wiringPi.h>
#include <string>


Gpio::~Gpio()
{
}

void Gpio::run() {
	return;
}


void Gpio::initialize()
{

	status.gpioSatus = (wiringPiSetupGpio() == 0) ? READY : INIT;
	//status.gpioSatus = READY;
	
	// init servos

	createThread = false;
	IO::initialize();
}

bool Gpio::isInitialized()
{
	return (status.gpioSatus == READY);
}

void Gpio::setOutputs(const GpioData data) {
	std::cout<< "SetOutputs called with " << data.testValue << "\n";
}

void Gpio::createNewGpioPwmOutput(std::string name, int pinNbr) {

}

#endif
