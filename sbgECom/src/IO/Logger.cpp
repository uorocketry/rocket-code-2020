#include "config/config.h"
#if USE_LOGGER

#include "Logger.h"
#include "data/sensorsData.h"

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <mutex>
#include <string>

int Logger::working = 0;
Logger::~Logger()
{
}


void Logger::initialize()
{
	IO::initialize();
}

bool Logger::isInitialized()
{
	return (status.fileStatus == READY);
}

void Logger::run()
{
	const int maxLine = 1000;
	int logId = 0;
	int lineCount = 0;

	std::string path = "./data/";
	std::string filename = "log";
	std::string ext = ".csv";

	writingLock = std::unique_lock<std::mutex>(writingMutex);

	if (!std::experimental::filesystem::exists(path))
	{
		std::experimental::filesystem::create_directories(path);
	}

	// bool shouldWriteHeader = !std::experimental::filesystem::exists(path + filename);
	// fileStream = std::make_shared<std::ofstream>(path + filename, std::ios_base::app);

	// if (shouldWriteHeader)
	// {
	// 	std::ofstream fileStream;
	// 	fileStream.open(path + filename, std::ios_base::app);
	// 	writeHeader(fileStream);
	// 	fileStream.close();
	// }

	status.fileStatus = READY;

	while (true)
	{
		if (!logQueue.empty())
		{
			std::ofstream fileStream;

			if (lineCount >= maxLine)
			{
				lineCount = 0;
				logId++;
			}

			fileStream.open(path + filename + std::to_string(logId) + ext, std::ios_base::app);

			dequeueToFile(fileStream);

			fileStream.close();
			lineCount++;
		}
		else
		{
			writingCondition.wait_for(writingLock, ONE_SECOND);
		}
	}
}

void Logger::enqueueSensorData(sensorsData curSensorData)
{
	std::lock_guard<std::mutex> lockGuard(mutex);
	logQueue.push(curSensorData);

	writingCondition.notify_one();
}

void Logger::dequeueToFile(std::ofstream &fileStream)
{
	sensorsData currentState;
	{
		std::lock_guard<std::mutex> lockGuard(mutex);
		currentState = logQueue.front();
		logQueue.pop();
	}

	if (fileStream.is_open())
	{
		working=1;
		writeData(fileStream, currentState);
	}
	else
	{
		std::cout << "Unable to open log file."
					 << "\n";
		working = 0;
	}
}

void Logger::writeHeader(std::ofstream &fileStream)
{
	fileStream << "Timestamp (Relative),";

	fileStream << "roll,";
	fileStream << "pitch,";
	fileStream << "yaw,";

	fileStream << "rollAccuracy,";
	fileStream << "pitchAccuracy,";
	fileStream << "yawAccuracy,";

	fileStream << "gpsLatitude,";
	fileStream << "gpsLongitude,";
	fileStream << "gpsAltitude,";

	fileStream << "barometricAltitude,";

	fileStream << "velocityN,";
	fileStream << "velocityE,";
	fileStream << "velocityD,";

	fileStream << "filteredXaccelerometer,";
	fileStream << "filteredYaccelerometer,";
	fileStream << "filteredZaccelerometer,";

	fileStream << "solutionStatus,";

	fileStream << "currentStateNo,\n";

	fileStream.flush();
}

void Logger::writeData(std::ofstream &fileStream, const sensorsData &currentState)
{

	// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
	fileStream << currentState.timeStamp << ",";

#if USE_SBG
	fileStream << currentState.sbg.roll << ",";
	fileStream << currentState.sbg.pitch << ",";
	fileStream << currentState.sbg.yaw << ",";

	fileStream << currentState.sbg.rollAccuracy << ",";
	fileStream << currentState.sbg.pitchAccuracy << ",";
	fileStream << currentState.sbg.yawAccuracy << ",";

	fileStream << currentState.sbg.gpsLatitude << ",";
	fileStream << currentState.sbg.gpsLongitude << ",";
	fileStream << currentState.sbg.gpsAltitude << ",";

	fileStream << currentState.sbg.barometricAltitude << ",";

	fileStream << currentState.sbg.velocityN << ",";
	fileStream << currentState.sbg.velocityE << ",";
	fileStream << currentState.sbg.velocityD << ",";

	fileStream << currentState.sbg.filteredXaccelerometer << ",";
	fileStream << currentState.sbg.filteredYaccelerometer << ",";
	fileStream << currentState.sbg.filteredZaccelerometer << ",";

	fileStream << currentState.sbg.solutionStatus << ",";

	fileStream << currentState.currentStateNo << ",";

	fileStream << currentState.sbg.gpsPosStatus << ",";

	fileStream << currentState.sbg.gpsPosAccuracyLatitude << ",";
	fileStream << currentState.sbg.gpsPosAccuracyLongitude << ",";
	fileStream << currentState.sbg.gpsPosAccuracyAltitude << ",";

	fileStream << currentState.sbg.NumSvUsed << ",";

	fileStream << currentState.sbg.velocityNAccuracy << ",";
	fileStream << currentState.sbg.velocityEAccuracy << ",";
	fileStream << currentState.sbg.velocityDAccuracy << ",";

	fileStream << currentState.sbg.latitudeAccuracy << ",";
	fileStream << currentState.sbg.longitudeAccuracy << ",";
	fileStream << currentState.sbg.altitudeAccuracy << ",";

	fileStream << currentState.sbg.pressureStatus << ",";
	fileStream << currentState.sbg.barometricPressure << ",";

	fileStream << currentState.sbg.imuStatus << ",";

	fileStream << currentState.sbg.gyroX << ",";
	fileStream << currentState.sbg.gyroY << ",";
	fileStream << currentState.sbg.gyroZ << ",";

	fileStream << currentState.sbg.temp << ",";

	fileStream << currentState.sbg.deltaVelX << ",";
	fileStream << currentState.sbg.deltaVelY << ",";
	fileStream << currentState.sbg.deltaVelZ << ",";

	fileStream << currentState.sbg.deltaAngleX << ",";
	fileStream << currentState.sbg.deltaAngleY << ",";
	fileStream << currentState.sbg.deltaAngleZ << ",";

#endif
	fileStream << "\n";

	fileStream.flush();
}

#endif