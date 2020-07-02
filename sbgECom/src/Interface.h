#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"
#include "Sensor/SBGData.h"
#include "Sensor/SBGSensor.h"
#include "Sensor/Sensor.h"

#ifdef TESTING
#include "Sensor/TestingSensors.h"
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


private:
	rocketState latestState;

#ifdef TESTING
	TestingSensors testingSensors;
#else
    SBGSensor mySbgSensor;

#endif



};


#endif
