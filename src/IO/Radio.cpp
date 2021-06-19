#include "config/config.h"
#if USE_RADIO == 1

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
#include <spdlog/spdlog.h>
#include "SensorLogger.h"

Radio::Radio(EventQueue &eventQueue) 
	: eventQueue(eventQueue)
{
	logger = spdlog::default_logger();
}

Radio::~Radio()
= default;

void Radio::initialize()
{



	if ((fd = serialOpen("/dev/ttyAMA0", 57600)) < 0) {
		SPDLOG_LOGGER_ERROR(logger, "Error while opening serial communication!");
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
		if(serialDataAvail(fd) > 0) 
		{
			eventQueue.push(serialGetchar(fd));
		}
		
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

void Radio::enqueueSensorData(const sensorsData& curSensorData)
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


void Radio::sendData(const sensorsData &currentState) const
{
	serialPrintf(fd, std::to_string(currentState.timeStamp).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.currentStateNo).c_str());
	serialPrintf(fd, ",");

#if USE_SBG == 1
	serialPrintf(fd, std::to_string(currentState.sbg.roll).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.pitch).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.yaw).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.rollAccuracy).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.pitchAccuracy).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.yawAccuracy).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.gpsLatitude).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.gpsLongitude).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.gpsAltitude).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.relativeBarometricAltitude).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.velocityN).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.velocityE).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.velocityD).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.filteredXaccelerometer).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.filteredYaccelerometer).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.filteredZaccelerometer).c_str());
	serialPrintf(fd, ",");
	serialPrintf(fd, std::to_string(currentState.sbg.solutionStatus).c_str());
	serialPrintf(fd, ",");
#endif // USE_SBG

#if USE_GPIO == 1
	for (std::pair<std::string, int> output : currentState.gpioData.digitalOutputMap)
	{
		serialPrintf(fd, std::to_string(output.second).c_str());
		serialPrintf(fd, ",");
	}
	for (std::pair<std::string, int> output : currentState.gpioData.pwmOutputMap)
	{
		serialPrintf(fd, std::to_string(output.second).c_str());
		serialPrintf(fd, ",");
	}
#endif

#if USE_LOGGER == 1
	serialPrintf(fd, std::to_string(SensorLogger::working).c_str());
	serialPrintf(fd, ",");
#endif // USE_LOGGER

	serialPrintf(fd, "\r\n");
}

#endif // USE_RADIO
