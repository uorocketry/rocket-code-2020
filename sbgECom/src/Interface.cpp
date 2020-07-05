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


	logger.enqueueSensorData(latestState);
}

rocketState* Interface::getLatest() {
	
	return &latestState;
}