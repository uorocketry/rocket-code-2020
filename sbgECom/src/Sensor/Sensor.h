#ifndef _SENSOR_H
#define _SENSOR_H

#include<mutex>
#include<iostream>


class Sensor
{
public:
	std::mutex mutex;

	virtual void initialize();
	virtual void update();
	
};


#endif
