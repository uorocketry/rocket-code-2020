#include "Interface.h"
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