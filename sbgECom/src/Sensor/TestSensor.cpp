#include "TestSensor.h"
#include<chrono>
#include<thread>

void TestSensor::run() {
	for(int i = 0; i < 5; ++i)
	{	
		std::this_thread::sleep_for (std::chrono::milliseconds(1000));
		increment();
		
	}
}

void TestSensor::increment() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	sensorValue++;
}
void TestSensor::initialize() {
	
}

int TestSensor::getValue() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	return sensorValue;
}