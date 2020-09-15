#pragma once

#include "../data/rocketState.h"
#include "IO.h"
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

class Logger : public IO {
public:
	~Logger();

	void initialize();
	void run();
	bool isInitialized();

	//write data to rocketState struct and push to queue on main thread
	void enqueueSensorData(rocketState curSensorData);

protected:
	std::mutex mutex;

private:
    //pop queue and log the data from rocketState on logging thread
	void dequeueToFile();

	void writeHeader(std::ofstream& file);
	void writeData(std::ofstream& file, const rocketState& currentState);

	const std::chrono::duration<int64_t, std::ratio<1,1>> ONE_SECOND = std::chrono::duration<int64_t, std::ratio<1,1>>(1);

	std::thread thisThread;

    //queue of sensor data to be logged 
	std::queue<rocketState> logQueue;

	std::mutex writingMutex;
	std::unique_lock<std::mutex> writingLock;
	std::condition_variable writingCondition;

	std::shared_ptr<std::ofstream> fileStream = nullptr;

	struct InitFlags
	{
		InitStatus fileStatus = INIT;
	};
	InitFlags status;

	
};
