#include "Interface.h"
#include "Sensor/Sensor.h"

#ifdef TESTING
#include "Sensor/TestingSensors.h"
#endif // TESTING


Interface::Interface() {
	initializeSensors();
}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {
#ifdef TESTING
	testingSensors.initialize();

	return;
#else
	// initialize all sensors
	return;
#endif

}

void Interface::update() {
#ifdef TESTING
	latestState = testingSensors.getLatest();

	return;
#else

	latestState.sbg = mySbgSensor.getData();
	return;
#endif



}
rocketState* Interface::getLatest() {
	
	return &latestState;
}