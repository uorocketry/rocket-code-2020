#include "config/config.h"
#if USE_RADIO

#include "wiringPi.h"
#include "wiringSerial.h"
#include "Radio.h"
#include "data/sensorsData.h"

#include <iostream>
#include <thread>
#include <queue>
#include <chrono>
#include <mutex>

Radio::~Radio()
{
	
}

void Radio::initialize()
{
	wiringPiSetupGpio();

	pinMode(14, OUTPUT);
	pinMode(15, INPUT);

	fd = serialOpen("/dev/ttyS0", 57600);
	if (fd < 0) {
		std::cout << "Error while opening serial communication!\n";
		status.wiringPiStatus = INIT; 
	} else {
		status.wiringPiStatus = READY; 
	}

	IO::initialize();
}

bool Radio::isInitialized()
{
	return (status.wiringPiStatus == READY);
}

void Radio::run()
{
	writingLock = std::unique_lock<std::mutex>(writingMutex);

	while (true)
	{
		if (!logQueue.empty())
		{
			dequeueToRadio();
		}
		else
		{
			writingCondition.wait_for(writingLock, ONE_SECOND);
		}
	}
}

void Radio::enqueueSensorData(sensorsData curSensorData)
{
	std::lock_guard<std::mutex> lockGuard(mutex);
	logQueue.push(curSensorData);

	writingCondition.notify_one();
}

void Radio::dequeueToRadio()
{
	static unsigned char c = 0;
	serialPutchar (fd, c++);	
	// if (fileStream != nullptr)
	// {
	// 	sensorsData currentState;
	// 	{
	// 		std::lock_guard<std::mutex> lockGuard(mutex);
	// 		currentState = logQueue.front();
	// 		logQueue.pop();
	// 	}

	// 	if (fileStream->is_open())
	// 	{
	// 		sendData(*fileStream, currentState);
	// 	}
	// 	else
	// 	{
	// 		std::cout << "Unable to open log file."
	// 				  << "\n";
	// 	}
	// }
}


void Radio::sendData(const sensorsData &currentState)
{
	static unsigned char c = 0;
	serialPutchar (fd, c++);

// 	// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
// 	fileStream << currentState.SMData.now.time_since_epoch().count() << ",";

// #if USE_SBG
// 	fileStream << currentState.sbg.Xangle << ",";
// 	fileStream << currentState.sbg.Yangle << ",";
// 	fileStream << currentState.sbg.Zangle << ",";

// 	fileStream << currentState.sbg.XangleAcc << ",";
// 	fileStream << currentState.sbg.YangleAcc << ",";
// 	fileStream << currentState.sbg.ZangleAcc << ",";

// 	fileStream << currentState.sbg.gpsLatitude << ",";
// 	fileStream << currentState.sbg.gpsLongitude << ",";
// 	fileStream << currentState.sbg.gpsAltitude << ",";

// 	fileStream << currentState.sbg.barometricAltitude << ",";

// 	fileStream << currentState.sbg.velocityN << ",";
// 	fileStream << currentState.sbg.velocityE << ",";
// 	fileStream << currentState.sbg.velocityD << ",";

// 	fileStream << currentState.sbg.filteredXacc << ",";
// 	fileStream << currentState.sbg.filteredYacc << ",";
// 	fileStream << currentState.sbg.filteredZacc << ",";

// 	fileStream << currentState.sbg.solutionStatus << ",";
// #endif
// 	fileStream << "\n";

// 	fileStream.flush();
}

#endif