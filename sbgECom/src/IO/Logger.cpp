#include "Logger.h"
#include "rocketState.h"

#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include <queue>


void Logger::initialize() {

}

void Logger::run() {
    while (true) {

        //timing stuff here
        dequeueToFile("Log.txt");
    }
}

void Logger::enqueueSensorData(rocketState curSensorData) {
    std::lock_guard<std::mutex> lockGuard(mutex);
	logQueue.push(curSensorData);
}


void Logger::dequeueToFile(std::string filename) {
    std::lock_guard<std::mutex> lockGuard(mutex);
	while(!logQueue.empty()) {
		rocketState temp = logQueue.front();
		logQueue.pop();
		std::ofstream myfile(filename.c_str(), std::ios_base::app); //append
    	if(myfile.is_open()) {
			myfile << "Xangle: "<< temp.sbg.Xangle << "\n";
			myfile << "Yangle: "<< temp.sbg.Yangle << "\n";
			myfile << "Zangle: "<< temp.sbg.Zangle << "\n";

			myfile << "XangleAcc: "<< temp.sbg.XangleAcc << "\n";
			myfile << "YangleAcc: "<< temp.sbg.YangleAcc << "\n";
			myfile << "ZangleAcc: "<< temp.sbg.ZangleAcc << "\n";

			myfile << "gpsLatitude: "<< temp.sbg.gpsLatitude << "\n";
			myfile << "gpsLongitude: "<< temp.sbg.gpsLongitude << "\n";
			myfile << "gpsAltitude: "<< temp.sbg.gpsAltitude << "\n";

			myfile << "barometricAltitude: "<< temp.sbg.barometricAltitude << "\n";

			myfile << "velocityN: "<< temp.sbg.velocityN << "\n";
			myfile << "velocityE: "<< temp.sbg.velocityE << "\n";
			myfile << "velocityD: "<< temp.sbg.velocityD << "\n";

			myfile << "filteredXacc: "<< temp.sbg.filteredXacc << "\n";
			myfile << "filteredYacc: "<< temp.sbg.filteredYacc << "\n";
			myfile << "filteredZacc: "<< temp.sbg.filteredZacc << "\n";

			myfile << "solutionStatus: "<< temp.sbg.solutionStatus << "\n";

			myfile.close();
		}
		else {
			std::cout << "Unable to open " << filename.c_str() << "\n";
		}
	}
}