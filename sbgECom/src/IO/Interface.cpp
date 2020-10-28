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

void Interface::initializeSensors()
{
#if TESTING
	std::cout << "Initializing TESTING...\n";
	testingSensors.initialize();
#endif
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
#if USE_LOGGER
	std::cout << "Initializing LOGGER...\n";
	logger.initialize();
#endif
#if USE_RADIO
	std::cout << "Initializing RADIO...\n";
	radio.initialize();
#endif
}

bool Interface::sensorsInitialized()
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

void Interface::update(const UOSMData *smdata)
{
#if TESTING
	latestState = testingSensors.getLatest();
#endif

#if USE_SBG
	latestState.sbg = mySbgSensor.getData();
#endif

#if USE_INPUT
	latestState.inputEventNumber = input.getData();
#endif

#if USE_SOCKET_CLIENT
	latestState.clientEventNumber = client.getData();
#endif

#if USE_LOGGER
	logger.enqueueSensorData(latestState);
#endif

#if USE_RADIO
	static int count = 0;
	count++;
	if(count>=7) {
		count = 0;
		radio.enqueueSensorData(latestState);
	}
#endif
	latestState.timeStamp = smdata->now.time_since_epoch().count();

}


sensorsData *Interface::getLatest()
{
	return &latestState;
}
