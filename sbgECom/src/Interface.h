#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"
#include "Sensor/SBGData.h"
#include "Sensor/SBGSensor.h"
#include "Sensor/Sensor.h"

#ifdef TESTING
#include "testing/TestingInterface.h"
#endif // TESTING

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

#ifdef TESTING
	TestingInterface testingInterface;
#endif // TESTING

private:
	rocketState latestState;

    SBGSensor mySbgSensor;


};


#endif
