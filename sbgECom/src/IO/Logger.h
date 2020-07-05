#pragma once

#include "rocketState.h"
#include "IO.h"

#include <queue>
#include <mutex>
#include <thread>


class Logger : public IO
{
public:

	virtual void initialize();
	virtual void run();

	//write data to rocketState struct and push to queue on main thread
	void enqueueSensorData(rocketState curSensorData);

protected:
	std::mutex mutex;

private:
    //pop queue and log the data from rocketState on logging thread
	void dequeueToFile(std::string filename);

	std::thread thisThread;

    //queue of sensor data to be logged 
	std::queue<rocketState> logQueue;
};
