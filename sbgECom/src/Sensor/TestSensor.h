#ifndef _TESTSENSOR_H
#define _TESTSENSOR_H

#include "Sensor.h"

class TestSensor : public Sensor
{
public:
	void run();
	void initialize();
	int getValue();
private:
	int sensorValue = 100;
	void increment();
};

#endif