#include "Sensor.h"
#include "iostream"
#include<thread>

Sensor::Sensor() {
	// create thread
	std::cout << "create thread" << std::endl;

	thisThread = std::thread(&Sensor::run, this);
    thisThread.detach();
}

Sensor::~Sensor() {
	// destroy thread
	std::cout << "destroy thread" << std::endl;
	thisThread.~thread(); // thread not killed
	std::cout << "Thread " << "testSensorThread" << " killed:" << std::endl;
}

void Sensor::initialize() {

}

void Sensor::run() {

}

//	TESTS	//
#ifdef TESTING

void Sensor::randomRun() {

}

#endif