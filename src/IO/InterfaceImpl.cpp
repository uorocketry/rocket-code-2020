#include "config/config.h"
#if !TESTING

#include "InterfaceImpl.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <iostream>
#include "IO/TestingSensors.h"
#include <string>


InterfaceImpl::InterfaceImpl() : eventQueue()
#if USE_INPUT
        , input(eventQueue)
#endif
#if USE_SOCKET_CLIENT
        , client(eventQueue)
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
	#if USE_SBG
		std::cout << "Initializing SBG...\n";
		mySbgSensor.initialize();
	#endif
	#if USE_INPUT
		std::cout << "Initializing INPUT...\n";
		input.initialize();
	#endif
	#if USE_SOCKET_CLIENT
		std::cout << "Initializing SOCKET_CLIENT...\n";
		client.initialize();
	#endif
}

void InterfaceImpl::initializeOutputs() 
{
#if USE_LOGGER
	std::cout << "Initializing LOGGER...\n";
	logger.initialize();
#endif
#if USE_RADIO
	std::cout << "Initializing RADIO...\n";
	radio.initialize();
#endif
#if USE_GPIO
	std::cout << "Initializing GPIO...\n";
	gpio.initialize();
#endif
}


bool InterfaceImpl::isInitialized()
{
#if SKIP_INIT
	std::cout << "Skipping init\n";
	return true;
#endif

	bool result = 1;



	return result;
}

bool InterfaceImpl::updateInputs()
{
	latestState = std::make_shared<sensorsData>();

#if USE_SBG
	latestState->sbg = mySbgSensor.getData();
#endif

	latestState->eventNumber = eventQueue.pop();

	return true;
}

bool InterfaceImpl::updateOutputs(std::shared_ptr<sensorsData> data) 
{
#if USE_LOGGER
	logger.enqueueSensorData(*data);
#endif

#if USE_RADIO
	radio.enqueueSensorData(*data);
#endif


#if USE_GPIO
	gpio.setOutputs((*data).gpioData);
#endif

	return true;
}

#if USE_GPIO
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
#if USE_SBG
	mySbgSensor.setZeroBarometricAltitude();
#endif
}


std::shared_ptr<sensorsData> InterfaceImpl::getLatest()
{
#if USE_LOGGER
	latestState->loggerIsInitialized = logger.isInitialized();
#endif

#if USE_SOCKET_CLIENT
	latestState->clientIsInitialized = client.isInitialized();
#endif

#if USE_SBG
	latestState->sbgIsInitialized = mySbgSensor.isInitialized();
#endif

#if USE_INPUT
	latestState->inputIsInitialized = input.isInitialized();
#endif

#if USE_RADIO
	latestState->radioIsInitialized = radio.isInitialized();
#endif

#if USE_GPIO
	latestState->gpioIsInitialized = gpio.isInitialized();
#endif
	
	return latestState;
}

time_point InterfaceImpl::getCurrentTime()
{
	return std::chrono::steady_clock::now();
}

#endif