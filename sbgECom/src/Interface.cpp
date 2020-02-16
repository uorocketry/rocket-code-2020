#include "Interface.h"
#include "Sensor/TestSensor.h"
#include "Sensor/Sensor.h"
#include<thread>
#include<chrono>
#include<unordered_map>
#include<iostream>

Interface::Interface() {

}

Interface::~Interface() {
	
}

void Interface::initializeSensors() {

}

void Interface::update() {

}
rocketState* Interface::getLatest() {
	latestState.x = myTestSensor.getValue();

	return &latestState;
}