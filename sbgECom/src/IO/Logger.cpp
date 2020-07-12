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

}

void Logger::run() {
	while (true) {

		//timing stuff here
		//pause the thread
		dequeueToFile("./data/log.csv");
	}
}

void Logger::enqueueSensorData(rocketState curSensorData) {
	std::lock_guard<std::mutex> lockGuard(mutex);
	logQueue.push(curSensorData);
}


void Logger::dequeueToFile(std::string filename) {
	if (!logQueue.empty()) {
		rocketState currentState;
		{
			std::lock_guard<std::mutex> lockGuard(mutex);
			currentState = logQueue.front();
			logQueue.pop();
		}

		bool shouldWriteHeader = false;
		if (!headerWritten) {
			shouldWriteHeader = !std::experimental::filesystem::exists(filename);
			headerWritten = true;
		}

		std::ofstream file(filename.c_str(), std::ios_base::app); //append
		if(file.is_open()) {
			if (shouldWriteHeader) {
				writeHeader(file);
			} else {
				writeData(file, currentState);
			}

			file.close();
		} else {
			std::cout << "Unable to open " << filename.c_str() << "\n";
		}
	}
}

void Logger::writeHeader(std::ofstream& file) {
	file << "Xangle,";
	file << "Yangle,";
	file << "Zangle,";

	file << "XangleAcc,";
	file << "YangleAcc,";
	file << "ZangleAcc,";

	file << "gpsLatitude,";
	file << "gpsLongitude,";
	file << "gpsAltitude,";

	file << "barometricAltitude,";

	file << "velocityN,";
	file << "velocityE,";
	file << "velocityD,";

	file << "filteredXacc,";
	file << "filteredYacc,";
	file << "filteredZacc,";

	file << "solutionStatus,\n";
}

void Logger::writeData(std::ofstream& file, const rocketState& currentState) {
	file << currentState.sbg.Xangle << ",";
	file << currentState.sbg.Yangle << ",";
	file << currentState.sbg.Zangle << ",";

	file << currentState.sbg.XangleAcc << ",";
	file << currentState.sbg.YangleAcc << ",";
	file << currentState.sbg.ZangleAcc << ",";

	file << currentState.sbg.gpsLatitude << ",";
	file << currentState.sbg.gpsLongitude << ",";
	file << currentState.sbg.gpsAltitude << ",";

	file << currentState.sbg.barometricAltitude << ",";

	file << currentState.sbg.velocityN << ",";
	file << currentState.sbg.velocityE << ",";
	file << currentState.sbg.velocityD << ",";

	file << currentState.sbg.filteredXacc << ",";
	file << currentState.sbg.filteredYacc << ",";
	file << currentState.sbg.filteredZacc << ",";

	file << currentState.sbg.solutionStatus << ",";

	file << "\n";
}

#endif