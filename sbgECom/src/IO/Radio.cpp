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
#include <string>

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
	sensorsData currentState;
	{
		std::lock_guard<std::mutex> lockGuard(mutex);
		currentState = logQueue.front();
		logQueue.pop();
	}


	sendData(currentState);
}


void Radio::sendData(const sensorsData &currentState)
{

	serialPrintf(fd, std::to_string(currentState.timeStamp).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.Xangle).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.Yangle).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.Zangle).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.XangleAcc).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.YangleAcc).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.ZangleAcc).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.gpsLatitude).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.gpsLongitude).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.gpsAltitude).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.barometricAltitude).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.velocityN).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.velocityE).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.velocityD).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.filteredXacc).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.filteredYacc).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.filteredZacc).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.sbg.solutionStatus).c_str());
	serialPrintf(fd, ";");
	serialPrintf(fd, std::to_string(currentState.currentStateNo).c_str());
	serialPrintf(fd, "\r\n");
}

#endif
