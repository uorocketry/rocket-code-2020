#include "config/config.h"
#if TESTING != 1

#include "InterfaceImpl.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <iostream>
#include <chrono>
#include "helpers/Types.h"
#include "IO/TestingSensors.h"
#include <string>
#include <spdlog/spdlog.h>


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
    logger = spdlog::default_logger();
}

InterfaceImpl::~InterfaceImpl()
= default;

void InterfaceImpl::initialize() 
{
	initializeInputs();
	initializeOutputs();
}

void InterfaceImpl::initializeInputs()
{
	#if USE_SBG == 1
		SPDLOG_LOGGER_INFO(logger, "Initializing SBG...");
		mySbgSensor.initialize();
	#endif
	#if USE_INPUT == 1
		SPDLOG_LOGGER_INFO(logger, "Initializing INPUT...");
		input.initialize();
	#endif
	#if USE_SOCKET_CLIENT == 1
		SPDLOG_LOGGER_INFO(logger, "Initializing SOCKET_CLIENT...");
		client.initialize();
	#endif
}

void InterfaceImpl::initializeOutputs() 
{
#if USE_LOGGER == 1
	SPDLOG_LOGGER_INFO(logger, "Initializing SENSOR_LOGGER...");
	sensorLogger.initialize();
#endif
#if USE_RADIO == 1
	SPDLOG_LOGGER_INFO(logger, "Initializing RADIO...");
	radio.initialize();
#endif
#if USE_GPIO == 1
	SPDLOG_LOGGER_INFO(logger, "Initializing GPIO...");
	gpio.initialize();
#endif
}

bool InterfaceImpl::updateInputs()
{
	latestState = std::make_shared<sensorsData>();

	latestState->timeStamp = std::chrono::duration_cast<time_point::duration>(std::chrono::steady_clock::now().time_since_epoch()).count();

#if USE_SBG == 1
	latestState->sbg = mySbgSensor.getData();
#endif

	latestState->eventNumber = eventQueue.pop();

	
#if USE_LOGGER == 1
    latestState->loggerIsInitialized = sensorLogger.isInitialized();
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

	return true;
}

bool InterfaceImpl::updateOutputs(std::shared_ptr<sensorsData> data) 
{

#if USE_GPIO == 1
	data->gpioData = gpio.setOutputs(data->gpioData);
#endif

#if USE_LOGGER == 1
	sensorLogger.enqueueSensorData(*data);
#endif

#if USE_RADIO == 1
	radio.enqueueSensorData(*data);
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

	return latestState;
}

time_point InterfaceImpl::getCurrentTime()
{
	return std::chrono::steady_clock::now();
}

#endif