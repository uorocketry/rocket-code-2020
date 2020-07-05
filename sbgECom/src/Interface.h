#ifndef _INTERFACE_H
#define _INTERFACE_H
#include "rocketState.h"
#include "Sensor/SBGData.h"
#include "Sensor/SBGSensor.h"
#include "Sensor/Sensor.h"
#include <queue>


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
	void log(std::string filename);

private:
	rocketState latestState;

    SBGSensor mySbgSensor;

	//queue of sensor data to be logged 
	std::queue<rocketState> myqueue;

	//called by log
	//write data to rocketState struct and push to queue on main thread
	void EnqueueSensorData(rocketState cur_sensor_data);

	//called by log 
	//pop queue and log the data from rocketState on logging thread
	void DequeueToFile(std::string filename);

};


#endif
