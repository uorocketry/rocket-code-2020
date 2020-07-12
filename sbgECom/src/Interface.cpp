#include "Interface.h"
#include "IO/IO.h"


Interface::Interface() {

}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {

}

void Interface::update() {
	latestState.sbg = mySbgSensor.getData();

#ifndef NO_LOGS
	logger.enqueueSensorData(latestState);
#endif
}

rocketState* Interface::getLatest() {
	
	return &latestState;
}