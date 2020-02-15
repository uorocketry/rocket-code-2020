#ifndef _TESTSENSOR_H
#define _TESTSENSOR_H

#include "Sensor.h"

class TestSensor : public Sensor
{
public:
	TestSensor();
	~TestSensor();

	int update();

};

#endif