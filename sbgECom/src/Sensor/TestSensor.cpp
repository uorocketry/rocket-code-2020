#include "TestSensor.h"
#include<thread>
#include<iostream>


void TestSensor::update() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	for(int i = 0; i < 5; ++i)
	{	
		std::this_thread::sleep_for (std::chrono::milliseconds(1000));
		sensorValue++;
		
	}
}

int TestSensor::getValue() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	return sensorValue;
}