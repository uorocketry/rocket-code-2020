#include "config/config.h"
#if USE_LOGGER == 1

#include "Logger.h"
#include "data/sensorsData.h"

#include "helpers/Helper.h"

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <mutex>
#include <string>
#include <vector>

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
	const int maxLine = 300;
	int lineCount = 0;
	int logId = 0;

	std::string path = helper::getEnvOrDefault("LOG_PATH", "/data/");
	std::string ext = ".uorocketlog";

	int bootId = getBootId(path);

	writingLock = std::unique_lock<std::mutex>(writingMutex);

//	if (!std::experimental::filesystem::exists(path))
//	{
//		std::experimental::filesystem::create_directories(path);
//	}

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
	std::ofstream fileStream;
	fileStream.open(path + std::to_string(bootId) + "." + std::to_string(logId) + ext, std::ios_base::ate);
	while (true)
	{
		if (!logQueue.empty())
		{
			if (lineCount >= maxLine)
			{
				fileStream.close();
				lineCount = 0;
				logId++;
				fileStream.open(path + std::to_string(bootId) + "." + std::to_string(logId) + ext, std::ios_base::ate);
				fileStream.sync_with_stdio(true);
			}


			dequeueToFile(fileStream);

			lineCount++;
		}
		else
		{
			writingCondition.wait_for(writingLock, ONE_SECOND);
		}
	}
}

int Logger::getBootId(std::string &path)
{
	int bootId = 0;

//	for (auto &p : std::experimental::filesystem::directory_iterator(path))
//	{
//		std::string itemPath = p.path();
//		std::vector<std::string> tokens1;
//
//		// stringstream class check1
//		std::stringstream check1(itemPath);
//		std::string intermediate;
//
//		// splitting string with '/'
//		while (getline(check1, intermediate, '/'))
//		{
//			tokens1.push_back(intermediate);
//		}
//
//		if (tokens1.size() > 0)
//		{
//			std::string currentLog = tokens1[tokens1.size() - 1];
//			std::vector<std::string> tokens2;
//
//			std::stringstream check2(currentLog);
//
//			// splitting string with '.'
//			while (getline(check2, intermediate, '.'))
//			{
//				tokens2.push_back(intermediate);
//			}
//
//			if (atoi(tokens2[0].c_str()) + 1 > bootId)
//			{
//				bootId = atoi(tokens2[0].c_str()) + 1;
//			}
//		}
//	}

	return bootId;
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
	}

	if (fileStream.is_open())
	{
		working = 1;
		writeData(fileStream, currentState);

		// Pop data now that it has been successfully written
		{
			std::lock_guard<std::mutex> lockGuard(mutex);
			logQueue.pop();
		}
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
	const char* sep = ","; 

	// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
	fileStream << currentState.timeStamp << sep;
	fileStream << currentState.currentStateNo << sep;


#if USE_GPIO == 1

	for (std::pair<std::string, int> output : currentState.gpioData.outputMap)
	{
		fileStream << output.first << "=" << output.second << ":";
	}
	for (std::pair<std::string, int> output : currentState.gpioData.pwmOutputMap)
	{
		fileStream << output.first << "=" << output.second << ":";
	}
	fileStream << sep;
#endif

#if USE_SBG == 1
	fileStream << currentState.sbg.roll << sep;
	fileStream << currentState.sbg.pitch << sep;
	fileStream << currentState.sbg.yaw << sep;

	fileStream << currentState.sbg.rollAccuracy << sep;
	fileStream << currentState.sbg.pitchAccuracy << sep;
	fileStream << currentState.sbg.yawAccuracy << sep;

	fileStream << currentState.sbg.gpsLatitude << sep;
	fileStream << currentState.sbg.gpsLongitude << sep;
	fileStream << currentState.sbg.gpsAltitude << sep;

	fileStream << currentState.sbg.barometricAltitude << sep;
	fileStream << currentState.sbg.relativeBarometricAltitude << sep;

	fileStream << currentState.sbg.velocityN << sep;
	fileStream << currentState.sbg.velocityE << sep;
	fileStream << currentState.sbg.velocityD << sep;

	fileStream << currentState.sbg.filteredXaccelerometer << sep;
	fileStream << currentState.sbg.filteredYaccelerometer << sep;
	fileStream << currentState.sbg.filteredZaccelerometer << sep;

	fileStream << currentState.sbg.solutionStatus << sep;

	fileStream << currentState.sbg.gpsPosStatus << sep;

	fileStream << currentState.sbg.gpsPosAccuracyLatitude << sep;
	fileStream << currentState.sbg.gpsPosAccuracyLongitude << sep;
	fileStream << currentState.sbg.gpsPosAccuracyAltitude << sep;

	fileStream << (int) currentState.sbg.NumSvUsed << sep;

	fileStream << currentState.sbg.velocityNAccuracy << sep;
	fileStream << currentState.sbg.velocityEAccuracy << sep;
	fileStream << currentState.sbg.velocityDAccuracy << sep;

	fileStream << currentState.sbg.latitudeAccuracy << sep;
	fileStream << currentState.sbg.longitudeAccuracy << sep;
	fileStream << currentState.sbg.altitudeAccuracy << sep;

	fileStream << currentState.sbg.pressureStatus << sep;
	fileStream << currentState.sbg.barometricPressure << sep;

	fileStream << currentState.sbg.imuStatus << sep;

	fileStream << currentState.sbg.gyroX << sep;
	fileStream << currentState.sbg.gyroY << sep;
	fileStream << currentState.sbg.gyroZ << sep;

	fileStream << currentState.sbg.temp << sep;

	fileStream << currentState.sbg.deltaVelX << sep;
	fileStream << currentState.sbg.deltaVelY << sep;
	fileStream << currentState.sbg.deltaVelZ << sep;

	fileStream << currentState.sbg.deltaAngleX << sep;
	fileStream << currentState.sbg.deltaAngleY << sep;
	fileStream << currentState.sbg.deltaAngleZ << sep;

#endif
	fileStream << "\n";

	fileStream.flush();
}

bool Logger::queueEmpty() {
	return logQueue.empty();
}

#endif
