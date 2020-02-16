#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"
#include<unordered_map>
#include<thread>
#include "Sensor/TestSensor.h"
#include "Sensor/Sensor.h"


class Interface
{
public:
	Interface();
	~Interface();

	void initializeSensors();

	// to get the latest rocket state 
	rocketState* getLatest();
	void update();
private:
	rocketState latestState {0, 0, 0};

    Sensor* testSensorptr; 
    TestSensor myTestSensor;

};


#endif
