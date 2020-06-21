#ifndef _SENSOR_H
#define _SENSOR_H

#include "testing/SensorType.h"

#include<mutex>
#include<thread>

class Sensor
{
public:
	Sensor();
	~Sensor();

	virtual void initialize();
	virtual void run();

	#ifdef TESTING
	virtual void setData(int index, const char* dataInput);
	virtual std::string getDataLabel();
	virtual SensorType getSensorType();
	#endif

protected:
	std::mutex mutex;
	
private:
	std::thread thisThread;
};


#endif
