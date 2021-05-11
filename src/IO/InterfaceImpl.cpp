#include "config/config.h"
#if TESTING != 1

#include "InterfaceImpl.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <iostream>
#include "IO/TestingSensors.h"
#include <string>


InterfaceImpl::InterfaceImpl() : eventQueue()
#if USE_INPUT == 1
        , input(eventQueue)
#endif
#if USE_SOCKET_CLIENT == 1
        , client(eventQueue)
#endif
#if USE_RADIO == 1
        , radio(eventQueue)
#endif
{
}

InterfaceImpl::~InterfaceImpl()
{
}

void InterfaceImpl::initialize() 
{
	initializeInputs();
	initializeOutputs();
}

void InterfaceImpl::initializeInputs()
{
	#if USE_SBG == 1
		std::cout << "Initializing SBG...\n";
		mySbgSensor.initialize();
	#endif
	#if USE_INPUT == 1
		std::cout << "Initializing INPUT...\n";
		input.initialize();
	#endif
	#if USE_SOCKET_CLIENT == 1
		std::cout << "Initializing SOCKET_CLIENT...\n";
		client.initialize();
	#endif
}

void InterfaceImpl::initializeOutputs() 
{
#if USE_LOGGER == 1
	std::cout << "Initializing LOGGER...\n";
	logger.initialize();
#endif
#if USE_RADIO == 1
	std::cout << "Initializing RADIO...\n";
	radio.initialize();
#endif
#if USE_GPIO == 1
	std::cout << "Initializing GPIO...\n";
	gpio.initialize();
#endif
}

bool InterfaceImpl::updateInputs()
{
	latestState = std::make_shared<sensorsData>();

#if USE_SBG == 1
	latestState->sbg = mySbgSensor.getData();
#endif

	latestState->eventNumber = eventQueue.pop();

	return true;
}

bool InterfaceImpl::updateOutputs(std::shared_ptr<sensorsData> data) 
{
#if USE_LOGGER == 1
	logger.enqueueSensorData(*data);
#endif

#if USE_RADIO == 1
	radio.enqueueSensorData(*data);
#endif


#if USE_GPIO == 1
	gpio.setOutputs((*data).gpioData);
#endif

	return true;
}

#if USE_GPIO == 1
void InterfaceImpl::createNewGpioOutput(std::string name, int pinNbr) 
{
	gpio.createNewGpioOutput(name, pinNbr);
}

void InterfaceImpl::createNewGpioPwmOutput(std::string name, int pinNbr) 
{
	gpio.createNewGpioPwmOutput(name, pinNbr);
}
#endif

void InterfaceImpl::calibrateTelemetry() 
{
#if USE_SBG == 1
	mySbgSensor.setZeroBarometricAltitude();
#endif
}


std::shared_ptr<sensorsData> InterfaceImpl::getLatest()
{
#if USE_LOGGER == 1
	latestState->loggerIsInitialized = logger.isInitialized();
#endif

#if USE_SOCKET_CLIENT == 1
	latestState->clientIsInitialized = client.isInitialized();
#endif

#if USE_SBG == 1
	latestState->sbgIsInitialized = mySbgSensor.isInitialized();
#endif

#if USE_INPUT == 1
	latestState->inputIsInitialized = input.isInitialized();
#endif

#if USE_RADIO == 1
	latestState->radioIsInitialized = radio.isInitialized();
#endif

#if USE_GPIO == 1
	latestState->gpioIsInitialized = gpio.isInitialized();
#endif

	return latestState;
}

time_point InterfaceImpl::getCurrentTime()
{
	return std::chrono::steady_clock::now();
}

#endif