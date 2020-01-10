#include "ReadSensors.h"
#include<iostream>
#include<thread>


Sensors::Sensors(){}
int Sensors:: get_value(){return sensor_value; }
void Sensors::add_value(int max_value)
{
	std::lock_guard<std::mutex> lockGuard(mutex);
	for(int i = 0; i < max_value; ++i)
	{	
		std::this_thread::sleep_for (std::chrono::milliseconds(1000));
		sensor_value++;
		
	}
}

