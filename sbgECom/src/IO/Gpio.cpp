#include "config/config.h"
#if USE_GPIO

#include "Gpio.h"
#include "data/sensorsData.h"

#include "helpers/Helper.h"
#include <wiringPi.h>


Gpio::~Gpio()
{
}

void Gpio::run() {
	return;
}


void Gpio::initialize()
{

	status.gpioSatus = (wiringPiSetupGpio() == 0) ? READY : INIT;
	
	// init servos

	createThread = false;
	IO::initialize();
}

bool Gpio::isInitialized()
{
	return (status.gpioSatus == READY);
}


#endif
