#include "SensorsRead.h"
#include<mutex>
#include<iostream>
#include<thread>


Sensors::Sensors(){}
int Sensors:: get_value(){return sensor_value; }
void Sensors::add_value(int money)
{
	std::lock_guard<std::mutex> lockGuard(mutex);
	for(int i = 0; i < money; ++i)
	{	
		sensor_value++;
		std::this_thread::sleep_for (std::chrono::seconds(1));
		if (i == 100) {
			std::cout << "end";
			std::terminate();
		}
	}
}


