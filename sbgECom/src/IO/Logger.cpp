#ifndef NO_LOGS

#include "Logger.h"
#include "data/rocketstate.h"

#include <sys/stat.h>
#include <iostream>
#include <experimental/filesystem>
#include <thread>
#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>
#include <mutex>

void Logger::initialize() {
	writingLock = std::unique_lock<std::mutex>(writingMutex);

	std::string path = "./data/";
	std::string filename = "log.csv";
	if (!std::experimental::filesystem::exists(path)) {
		std::experimental::filesystem::create_directories(path);
	}

	bool shouldWriteHeader = !std::experimental::filesystem::exists(path + filename);
	fileStream = std::make_shared<std::ofstream>(path + filename, std::ios_base::app);

	if (shouldWriteHeader) {
		writeHeader(*fileStream);
	}

	IO::initialize();
}

Logger::~Logger() {
	fileStream->close();
}

void Logger::run() {
	while (true) {
		if (!logQueue.empty()) {
			dequeueToFile();
		} else {
			writingCondition.wait_for(writingLock, ONE_SECOND);
		}
 	}
}

void Logger::enqueueSensorData(rocketState curSensorData) {
	std::lock_guard<std::mutex> lockGuard(mutex);
	logQueue.push(curSensorData);

	writingCondition.notify_one();
}


void Logger::dequeueToFile() {
	if (fileStream != nullptr) {
		rocketState currentState;
		{
			std::lock_guard<std::mutex> lockGuard(mutex);
			currentState = logQueue.front();
			logQueue.pop();
		}

		if(fileStream->is_open()) {
			writeData(*fileStream, currentState);
		} else {
			std::cout << "Unable to open log file." << "\n";
		}
	}
}

void Logger::writeHeader(std::ofstream& fileStream) {
	fileStream << "Timestamp (Relative),";

	fileStream << "Xangle,";
	fileStream << "Yangle,";
	fileStream << "Zangle,";

	fileStream << "XangleAcc,";
	fileStream << "YangleAcc,";
	fileStream << "ZangleAcc,";

	fileStream << "gpsLatitude,";
	fileStream << "gpsLongitude,";
	fileStream << "gpsAltitude,";

	fileStream << "barometricAltitude,";

	fileStream << "velocityN,";
	fileStream << "velocityE,";
	fileStream << "velocityD,";

	fileStream << "filteredXacc,";
	fileStream << "filteredYacc,";
	fileStream << "filteredZacc,";

	fileStream << "solutionStatus,\n";

	fileStream.flush();
}

void Logger::writeData(std::ofstream& fileStream, const rocketState& currentState) {

	// Keep in mind, this is NOT the time since unix epoch (1970), and not the system time
	fileStream << currentState.rocketSMData.now.time_since_epoch().count() << ",";

	fileStream << currentState.sbg.Xangle << ",";
	fileStream << currentState.sbg.Yangle << ",";
	fileStream << currentState.sbg.Zangle << ",";

	fileStream << currentState.sbg.XangleAcc << ",";
	fileStream << currentState.sbg.YangleAcc << ",";
	fileStream << currentState.sbg.ZangleAcc << ",";

	fileStream << currentState.sbg.gpsLatitude << ",";
	fileStream << currentState.sbg.gpsLongitude << ",";
	fileStream << currentState.sbg.gpsAltitude << ",";

	fileStream << currentState.sbg.barometricAltitude << ",";

	fileStream << currentState.sbg.velocityN << ",";
	fileStream << currentState.sbg.velocityE << ",";
	fileStream << currentState.sbg.velocityD << ",";

	fileStream << currentState.sbg.filteredXacc << ",";
	fileStream << currentState.sbg.filteredYacc << ",";
	fileStream << currentState.sbg.filteredZacc << ",";

	fileStream << currentState.sbg.solutionStatus << ",";

	fileStream << "\n";

	fileStream.flush();
}

#endif