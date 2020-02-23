#include "TestSensor2.h"
#include<chrono>
#include<thread>

void TestSensor2::run() {
	for(int i = 0; i < 5; ++i)
	{	
		std::this_thread::sleep_for (std::chrono::milliseconds(500));
		increment();
		
	}
}

void TestSensor2::increment() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	sensorValue++;
}
void TestSensor2::initialize() {
	
}

int TestSensor2::getValue() {
	std::lock_guard<std::mutex> lockGuard(mutex);
	return sensorValue;
}