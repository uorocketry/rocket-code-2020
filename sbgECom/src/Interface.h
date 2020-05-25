#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"
#include "Sensor/TestSensor.h"
#include "Sensor/TestSensor2.h"
#include "Sensor/SBGData.h"
#include "Sensor/SBGSensor.h"
#include "Sensor/Sensor.h"


class Interface
{
public:
	Interface();
	~Interface();

	// not used yet
	void initializeSensors();

	// to get the latest rocket state. return a pointer to latestState
	rocketState* getLatest();

	// loop over each sensor and update the latestState
	void update();
private:
	rocketState latestState;

    // Sensor* testSensorptr; 
    TestSensor2 myTestSensor2;
    SBGSensor mySbgSensor;


};


#endif
