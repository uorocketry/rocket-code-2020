#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"
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

	// log sensor data to filename 
	// if debugState is true print what is logging to terminal
	void log(std::string filename, bool debugState);

private:
	rocketState latestState;

    SBGSensor mySbgSensor;


};


#endif
