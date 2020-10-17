#include "Interface.h"
#include "IO/IO.h"
#include "data/UOSMData.h"
#include <iostream>

#ifdef TESTING
#include "IO/TestingSensors.h"
#endif // TESTING

Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::initializeSensors()
{
#if TESTING
	testingSensors.initialize();
#endif
#if USE_SBG
	mySbgSensor.initialize();
#endif
#if USE_INPUT
	input.initialize();
#endif
#if USE_SOCKET_CONTROL
	client.initialize();
#endif
#if USE_LOGGER
	logger.initialize();
#endif
}

bool Interface::sensorsInitialized()
{
#ifdef SKIP_INIT
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

	latestState.SMData = *smdata;

#if USE_LOGGER
	logger.enqueueSensorData(latestState);
#endif
}

sensorsData *Interface::getLatest()
{
	return &latestState;
}
