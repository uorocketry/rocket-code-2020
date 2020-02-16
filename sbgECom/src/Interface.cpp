#include "Interface.h"
#include "Sensor/TestSensor.h"
#include "Sensor/Sensor.h"
#include<thread>
#include<chrono>
#include<unordered_map>
#include<iostream>

Interface::Interface() {
	std::cout <<"init1\n";
	testSensorThread = std::thread(&Sensor::update, &myTestSensor);
    testSensorThread.detach();
    tm["testSensorThread"] = std::move(testSensorThread);
    std::cout <<"init2\n";
}

Interface::~Interface() {
	ThreadMap::const_iterator it = tm.find("testSensorThread");
	it->second.std::thread::~thread(); // thread not killed
	tm.erase("testSensorThread");
	std::cout << "Thread " << "testSensorThread" << " killed:" << std::endl;
	std::cout << "del";
}

void Interface::initializeSensors() {
	


}

void Interface::update() {

}
rocketState* Interface::getLatest() {
	// update();
	latestState.x = myTestSensor.getValue();

	return &latestState;
}