#include "TestSensor.h"
#include<iostream>
#include<chrono>
#include<thread>

void TestSensor::update() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	for(int i = 0; i < 5; ++i)
	{	
		std::this_thread::sleep_for (std::chrono::milliseconds(1000));
		sensorValue++;
		
	}
}
void TestSensor::initialize() {

}

int TestSensor::getValue() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	return sensorValue;
}