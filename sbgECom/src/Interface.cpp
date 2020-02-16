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

    testSensorptr = &d; 

	testSensorThread = new std::thread(&Sensor::update, testSensorptr);

    // typedef std::unordered_map<std::string, std::thread> ThreadMap;
    // ThreadMap tm_;

    testSensorThread->detach();
}

void Interface::update() {

}
rocketState Interface::getLatest() {
	update();
	// latestState.x = testSensorptr->getValue();

	return rocketState();
}