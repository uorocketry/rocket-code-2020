#include "Interface.h"
#include "IO/IO.h"
#include "data/RocketSMData.h"

#ifdef TESTING
#include "IO/TestingSensors.h"
#endif // TESTING

Interface::Interface() {
	initializeSensors();
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
#endif

#ifndef NO_LOGS
	logger.initialize();
#endif
}

void Interface::update(const RocketSMData* rocketSMData) {
#ifdef TESTING
	latestState = testingSensors.getLatest();
#else
	latestState.sbg = mySbgSensor.getData();

	latestState.inputEventNumber = input.getData();
#endif

	latestState.rocketSMData = *rocketSMData;

#ifndef NO_LOGS
	logger.enqueueSensorData(latestState);
#endif
}

rocketState* Interface::getLatest() {
	return &latestState;
}