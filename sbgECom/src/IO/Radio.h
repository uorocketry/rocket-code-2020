#pragma once

#include "../data/sensorsData.h"
#include "IO.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class Radio : public IO
{
public:
	~Radio();

	void initialize();
	void run();
	bool isInitialized();

	//write data to sensorsData struct and push to queue on main thread
	void enqueueSensorData(sensorsData curSensorData);

protected:
	std::mutex mutex;

private:
	//pop queue and log the data from sensorsData on logging thread
	void dequeueToRadio();

	void sendData(std::ofstream &file, const sensorsData &currentState);

	const std::chrono::duration<int64_t, std::ratio<1, 1>> ONE_SECOND = std::chrono::duration<int64_t, std::ratio<1, 1>>(1);

	std::thread thisThread;

	//queue of sensor data to be logged
	std::queue<sensorsData> logQueue;

	std::mutex writingMutex;
	std::unique_lock<std::mutex> writingLock;
	std::condition_variable writingCondition;

	std::shared_ptr<std::ofstream> fileStream = nullptr;

	struct InitFlags
	{
		InitStatus fileStatus = INIT;
	} status;
};
