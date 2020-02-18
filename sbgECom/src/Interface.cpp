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
	latestState.x = myTestSensor.getValue();
	latestState.y = myTestSensor2.getValue();
}
rocketState* Interface::getLatest() {
	
	return &latestState;
}