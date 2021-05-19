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
    std::string data;

	data += std::to_string(currentState.timeStamp);
	data += ",";
	data += std::to_string(currentState.currentStateNo);
	data += ",";

#if USE_SBG == 1
	data += std::to_string(currentState.sbg.roll);
	data += ",";
	data += std::to_string(currentState.sbg.pitch);
	data += ",";
	data += std::to_string(currentState.sbg.yaw);
	data += ",";
	data += std::to_string(currentState.sbg.rollAccuracy);
	data += ",";
	data += std::to_string(currentState.sbg.pitchAccuracy);
	data += ",";
	data += std::to_string(currentState.sbg.yawAccuracy);
	data += ",";
	data += std::to_string(currentState.sbg.gpsLatitude);
	data += ",";
	data += std::to_string(currentState.sbg.gpsLongitude);
	data += ",";
	data += std::to_string(currentState.sbg.gpsAltitude);
	data += ",";
	data += std::to_string(currentState.sbg.relativeBarometricAltitude);
	data += ",";
	data += std::to_string(currentState.sbg.velocityN);
	data += ",";
	data += std::to_string(currentState.sbg.velocityE);
	data += ",";
	data += std::to_string(currentState.sbg.velocityD);
	data += ",";
	data += std::to_string(currentState.sbg.filteredXaccelerometer);
	data += ",";
	data += std::to_string(currentState.sbg.filteredYaccelerometer);
	data += ",";
	data += std::to_string(currentState.sbg.filteredZaccelerometer);
	data += ",";
	data += std::to_string(currentState.sbg.solutionStatus);
	data += ",";
#endif // USE_SBG

#if USE_GPIO == 1
	for (std::pair<std::string, int> output : currentState.gpioData.digitalOutputMap)
	{
		data += std::to_string(output.second);
		data += ",";
	}
	for (std::pair<std::string, int> output : currentState.gpioData.pwmOutputMap)
	{
		data += std::to_string(output.second);
		data += ",";
	}
#endif

#if USE_LOGGER == 1
	data += std::to_string(SensorLogger::working);
	data += ",";
#endif // USE_LOGGER

	data += "\r\n";

    serialPrintf(fd, data.c_str());
}

#endif // USE_RADIO
