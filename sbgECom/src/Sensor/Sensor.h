#ifndef _SENSORSREAD_H
#define _SENSORSREAD_H

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
