#ifndef _SENSORSREAD_H
#define _SENSORSREAD_H

#include<mutex>
#include<iostream>


class Sensors
{
public:
	int sensor_value = 0;
	std::mutex mutex;
	Sensors();
	int get_value();
	void add_value(int money);

};




#endif
