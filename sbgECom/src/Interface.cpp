#include "Interface.h"
#include "Sensor/TestSensor.h"
#include "Sensor/Sensor.h"
#include<thread>
#include<chrono>
#include<unordered_map>
#include<iostream>



Interface::~Interface() {
	// ThreadMap::const_iterator it = tm.find("testSensorThread");
	// it->second.std::thread::~thread(); // thread not killed
	// tm.erase("testSensorThread");
	// std::cout << "Thread " << "testSensorThread" << " killed:" << std::endl;
	// delete testSensorThread;
}

void Interface::initializeSensors() {
	std::cout << "Initialize all sensors"; 

	testSensorThread = std::thread(&Sensor::update, &myTestSensor);
    testSensorThread.detach();


}

void Interface::update() {

}
rocketState Interface::getLatest() {
	update();
	latestState.x = myTestSensor.getValue();

	return rocketState();
}