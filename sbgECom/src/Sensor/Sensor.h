#ifndef _SENSOR_H
#define _SENSOR_H

#include<mutex>
#include<iostream>
#include<thread>

class Sensor
{
public:
	Sensor();
	~Sensor();

	virtual void initialize();
	virtual void update();

protected:
	std::mutex mutex;
	
private:
	std::thread thisThread;
};


#endif
