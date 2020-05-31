#include "Interface.h"
#include "Sensor/Sensor.h"

Interface::Interface() {

}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {
#ifdef TESTING
	testingInterface.initializeSensors();
	return;
#endif

}

void Interface::update() {
#ifdef TESTING
	testingInterface.update();
	return;
#endif


	latestState.sbg = mySbgSensor.getData();

}
rocketState* Interface::getLatest() {
	
	return &latestState;
}