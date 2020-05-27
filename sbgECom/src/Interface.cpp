#include "Interface.h"
#include "Sensor/Sensor.h"


Interface::Interface() {

}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {

}

void Interface::update() {
	#ifdef TESTING
	return;
	#endif


	latestState.sbg = mySbgSensor.getData();

}
rocketState* Interface::getLatest() {
	
	return &latestState;
}