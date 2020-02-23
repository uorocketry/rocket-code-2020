#ifndef _TESTSENSOR2_H
#define _TESTSENSOR2_H

#include "Sensor.h"

class TestSensor2 : public Sensor
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