#include "Interface.h"
#include "Sensor/TestSensor.h"
#include "Sensor/Sensor.h"
#include<thread>
#include<chrono>
#include<unordered_map>


Interface::Interface() {

}
Interface::~Interface() {
	
}

void Interface::initializeSensors() {
	Sensor* testSensorptr; 
    TestSensor d; 
    testSensorptr = &d; 

	TestSensor testSensor;

	std::thread thread1 = std::thread(&Sensor::update, testSensorptr);

    typedef std::unordered_map<std::string, std::thread> ThreadMap;
    ThreadMap tm_;

    thread1.detach();
    tm_["thread1"] = std::move(thread1);

}

void Interface::update() {

}
rocketState Interface::getLatest() {
	return rocketState();
}