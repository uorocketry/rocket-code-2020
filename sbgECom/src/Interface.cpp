#include "Interface.h"
#include "IO/IO.h"

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
#endif

#ifndef NO_LOGS
	logger.initialize();
#endif
}

void Interface::update() {
#ifdef TESTING
	latestState = testingSensors.getLatest();
#else
	latestState.sbg = mySbgSensor.getData();
#endif

#ifndef NO_LOGS
	logger.enqueueSensorData(latestState);
#endif
}

rocketState* Interface::getLatest() {
	return &latestState;
}