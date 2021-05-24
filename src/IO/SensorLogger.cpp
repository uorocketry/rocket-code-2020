#include "config/config.h"
#if USE_LOGGER == 1

#include "SensorLogger.h"

#include "helpers/Helper.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include "boost/filesystem.hpp"

int SensorLogger::working = 0;
SensorLogger::~SensorLogger()
= default;

void SensorLogger::initialize()
{
	IO::initialize();
}

bool SensorLogger::isInitialized()
{
	return (status.fileStatus == READY);
}

void SensorLogger::run()
{
	const int maxLine = 300;
	int lineCount = 0;
	int logId = 0;

	std::string path = helper::getEnvOrDefault("LOG_PATH", "/data/");
	std::string ext = ".uorocketlog";
	if (path.back() != '/') path += "/";

	int bootId = getBootId(path);

	writingLock = std::unique_lock<std::mutex>(writingMutex);

	if (!boost::filesystem::exists(path))
    {
        boost::filesystem::create_directories(path);
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
				std::ofstream::sync_with_stdio(true);
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

int SensorLogger::getBootId(std::string &path)
{
	int bootId = 0;

	for (auto &p : boost::filesystem::directory_iterator(path))
    {
		std::string itemPath = p.path().string();
		std::vector<std::string> tokens1;

		// stringstream class check1
		std::stringstream check1(itemPath);
		std::string intermediate;

		// splitting string with '/'
		while (getline(check1, intermediate, '/'))
		{
			tokens1.push_back(intermediate);
		}

		if (!tokens1.empty())
		{
			std::string currentLog = tokens1[tokens1.size() - 1];
			std::vector<std::string> tokens2;

			std::stringstream check2(currentLog);

			// splitting string with '.'
			while (getline(check2, intermediate, '.'))
			{
				tokens2.push_back(intermediate);
			}

			if (atoi(tokens2[0].c_str()) + 1 > bootId)
			{
				bootId = atoi(tokens2[0].c_str()) + 1;
			}
		}
    }

	return bootId;
}

void SensorLogger::enqueueSensorData(const sensorsData& curSensorData)
{
	std::lock_guard<std::mutex> lockGuard(mutex);
	logQueue.push(curSensorData);

	writingCondition.notify_one();
}

void SensorLogger::dequeueToFile(std::ofstream &fileStream)
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
		SPDLOG_LOGGER_ERROR(logger, "Unable to open log file.");
		working = 0;
	}
}

void SensorLogger::writeHeader(std::ofstream &fileStream)
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

void SensorLogger::writeData(std::ofstream &fileStream, const sensorsData &currentState)
{
	const char* sep = ",";

	// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
	fileStream << currentState.timeStamp << sep;
	fileStream << currentState.currentStateNo << sep;


#if USE_GPIO == 1
	for (std::pair<std::string, int> output : currentState.gpioData.digitalOutputMap)
	{
		fileStream << output.second << sep;
	}

	for (std::pair<std::string, int> output : currentState.gpioData.pwmOutputMap)
	{
		fileStream << output.second << sep;
	}
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

	// Initialization data
#if USE_LOGGER
    fileStream << currentState.loggerIsInitialized << sep;
#endif

#if USE_SOCKET_CLIENT
    fileStream << currentState.clientIsInitialized << sep;
#endif

#if USE_SBG
    fileStream << currentState.sbgIsInitialized << sep;
#endif

#if USE_INPUT
    fileStream << currentState.inputIsInitialized << sep;
#endif

#if USE_RADIO
    fileStream << currentState.radioIsInitialized << sep;
#endif

#if USE_GPIO
    fileStream << currentState.gpioIsInitialized << sep;
#endif

	fileStream << "\n";

	fileStream.flush();
}

bool SensorLogger::queueEmpty() {
	return logQueue.empty();
}

#endif
