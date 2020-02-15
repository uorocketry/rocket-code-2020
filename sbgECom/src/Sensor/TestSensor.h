#ifndef _TESTSENSOR_H
#define _TESTSENSOR_H

#include "Sensor.h"

class TestSensor : public Sensor
{
public:
	TestSensor();
	~TestSensor();

	void update();
	int getValue();
private:
	int sensorValue = 0;
};

#endif