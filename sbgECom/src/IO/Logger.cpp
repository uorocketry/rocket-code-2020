#ifndef NO_LOGS

#include "Logger.h"
#include "rocketState.h"

#include <sys/stat.h>
#include <iostream>
#include <experimental/filesystem>
#include <thread>
#include <iostream>
#include <fstream>
#include <queue>


void Logger::initialize() {
	std::string filename = "./data/log.csv";
	bool shouldWriteHeader = !std::experimental::filesystem::exists(filename);
	fileStream = new std::ofstream(filename, std::ios_base::app);

	if (shouldWriteHeader) {
		writeHeader(*fileStream);
	}
}

Logger::~Logger() {
	fileStream->close();
	delete fileStream;
	fileStream = nullptr;
}

void Logger::run() {
	while (true) {

		//timing stuff here
		//pause the thread
		dequeueToFile();
	}
}

void Logger::enqueueSensorData(rocketState curSensorData) {
	std::lock_guard<std::mutex> lockGuard(mutex);
	logQueue.push(curSensorData);
}


void Logger::dequeueToFile() {
	if (fileStream != nullptr && !logQueue.empty()) {
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
	} else {
		// TODO: Add some delay or sleeping here
	}
}

void Logger::writeHeader(std::ofstream& fileStream) {
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