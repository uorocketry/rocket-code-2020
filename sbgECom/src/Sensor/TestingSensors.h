#ifdef TESTING
#ifndef _TESTING_SENSORS_H
#define _TESTING_SENSORS_H

#include "Sensor.h"
#include "SBGData.h"
#include <iostream>
#include <queue>

class TestingSensors : public Sensor
{
public:
	void run();
	void initialize();

	rocketState getLatest();
private:
	std::queue<rocketState> data;

	int processInt(std::string data);
	float processFloat(std::string data);
	double processDouble(std::string data);
};

#endif
#endif