#include "Interface.h"
#include "IO/IO.h"
#include "data/RocketSMData.h"
#include <iostream>

#ifdef TESTING
#include "IO/TestingSensors.h"
#endif // TESTING

Interface::Interface() {
	
}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {
#ifdef TESTING
	testingSensors.initialize();
#else
	// initialize all sensors
	mySbgSensor.initialize();

	input.initialize();

#ifndef NO_SOCKET_CONTROL
	client.initialize();
#endif

#endif

#ifndef NO_LOGS
	logger.initialize();
#endif
}

bool Interface::sensorsInitialized() {
#ifndef NO_LOGS
	if (logger.isInitialized() && mySbgSensor.isInitialized() && input.isInitialized())
#else
	if (mySbgSensor.isInitialized() && input.isInitialized())
#endif
		return true;
	return false;
}	

void Interface::update(const RocketSMData* rocketSMData) {
#ifdef TESTING
	latestState = testingSensors.getLatest();
#else
	latestState.sbg = mySbgSensor.getData();

	latestState.inputEventNumber = input.getData();

#ifndef NO_SOCKET_CONTROL
	latestState.clientEventNumber = client.getData();
#endif

#endif

	latestState.rocketSMData = *rocketSMData;

#ifndef NO_LOGS
	logger.enqueueSensorData(latestState);
#endif
}

rocketState* Interface::getLatest() {
	return &latestState;
}