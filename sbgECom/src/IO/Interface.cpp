#include "config/config.h"
#include "Interface.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <iostream>
#include "IO/TestingSensors.h"


Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::initialize() 
{
	initializeSensors();
	initializeOutputs();
}

void Interface::initializeSensors()
{
#if TESTING
	std::cout << "Initializing TESTING...\n";
	testingSensors.initialize();
#else
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
#endif //!TESTING
}

void Interface::initializeOutputs() 
{
#if USE_LOGGER
	std::cout << "Initializing LOGGER...\n";
	logger.initialize();
#endif
#if USE_RADIO
	std::cout << "Initializing RADIO...\n";
	radio.initialize();
#endif
}


bool Interface::isInitialized()
{
#if SKIP_INIT
	std::cout << "Skipping init\n";
	return true;
#endif

	bool result = 1;

#if USE_LOGGER
	result &= logger.isInitialized();
#endif

#if USE_SOCKET_CLIENT
	result &= client.isInitialized();
#endif

#if USE_SBG
	result &= mySbgSensor.isInitialized();
#endif

#if USE_INPUT
	result &= input.isInitialized();
#endif

#if USE_RADIO
	result &= radio.isInitialized();
#endif

	return result;
}

void Interface::update(const UOSMData *smdata, int currentStateNo)
{
	latestState.timeStamp = smdata->now.time_since_epoch().count();

	if (!updateSensors()) {
		return;
	}

	// Save current state no matter what
	latestState.currentStateNo = currentStateNo;

	if (!updateOutputs()) {
		return;
	}
}

bool Interface::updateSensors()
{
#if TESTING
	latestState = testingSensors.getLatest();

	if (latestState.outOfData) {
		#if USE_LOGGER
		if (!logger.queueEmpty()) {
			// Wait for logger to finish
			return false;
		}
		#endif

		exit(EXIT_SUCCESS);
	}
#else

 	//Normal case
#if USE_SBG
	latestState.sbg = mySbgSensor.getData();
#endif

#if USE_INPUT
	latestState.inputEventNumber = input.getData();
#endif

#if USE_SOCKET_CLIENT
	latestState.clientEventNumber = client.getData();
#endif

#endif //!TESTING

	return true;
}

bool Interface::updateOutputs() 
{
#if USE_LOGGER
	logger.enqueueSensorData(latestState);
#endif

#if USE_RADIO
	radio.enqueueSensorData(latestState);
#endif

	return true;
}

void Interface::calibrateTelemetry() 
{
#if USE_SBG
	mySbgSensor.setZeroBarometricAltitude();
#endif
}


sensorsData *Interface::getLatest()
{
	return &latestState;
}
