#include "Interface.h"
#include "IO/IO.h"
#include "data/RocketSMData.h"
#include "data/UOSMData.h"
#include <iostream>

#ifdef TESTING
#include "IO/TestingSensors.h"
#endif // TESTING

template <class SMData>
Interface<SMData>::Interface()
{
}

template <class SMData>
Interface<SMData>::~Interface()
{
}

template <class SMData>
void Interface<SMData>::initializeSensors()
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

template <class SMData>
bool Interface<SMData>::sensorsInitialized()
{
#ifdef SKIP_INIT
	return true;
#endif

	bool result = 1;

#ifndef NO_LOGS
	result &= logger.isInitialized();
#endif
#ifndef NO_SOCKET_CONTROL
	result &= client.isInitialized();
#endif
	result &= (mySbgSensor.isInitialized() && input.isInitialized());

	return result;
}

template <class SMData>
void Interface<SMData>::update(const SMData *SMData)
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
#if USE_SOCKET_CONTROL
	latestState.clientEventNumber = client.getData();
#endif

	latestState.SMData = *SMData;

#ifndef NO_LOGS
	logger.enqueueSensorData(latestState);
#endif
}

template <class SMData>
sensorsData *Interface<SMData>::getLatest()
{
	return &latestState;
}