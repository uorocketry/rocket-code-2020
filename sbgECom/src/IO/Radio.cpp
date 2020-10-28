#include "config/config.h"
#if USE_RADIO

#include <string>
#include <unistd.h>
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



	if ((fd = serialOpen("/dev/ttyAMA0", 57600)) < 0) {
		std::cout << "Error while opening serial communication!\n";
		status.wiringPiStatus = INIT; 
	} else {
		status.wiringPiStatus = READY; 
	}

	wiringPiSetup();
	
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
		dequeueToRadio();
		if (!logQueue.empty())
		{
			//dequeueToRadio();
		}
		else
		{
			//writingCondition.wait_for(writingLock, ONE_SECOND);
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
	
	//const char *c1;
	//std::string s1("Hello world\n");
	//c1 = s1.c_str();
	//char *s = "Hello world\r\n";
	//serialPutchar(fd, hello);
	//serialPrintf(fd, "Hello world\n");
	std::cout << "Send\n";
	serialPrintf(fd, "HELLOOOO");
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
	// static unsigned char c = 0;
	// serialPutchar(fd, c++);

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
