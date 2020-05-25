#include "Interface.h"
#include "Sensor/TestSensor.h"
#include "Sensor/TestSensor2.h"
#include "Sensor/Sensor.h"


Interface::Interface() {

}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {

}

void Interface::update() {
	latestState.sbg = mySbgSensor.getData();

}
rocketState* Interface::getLatest() {
	
	return &latestState;
}