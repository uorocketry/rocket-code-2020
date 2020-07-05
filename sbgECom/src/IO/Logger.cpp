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
        //pause the thread
        dequeueToFile("Log.txt");
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

		std::ofstream myfile(filename.c_str(), std::ios_base::app); //append
    	if(myfile.is_open()) {
			myfile << "Xangle: "<< currentState.sbg.Xangle << "\n";
			myfile << "Yangle: "<< currentState.sbg.Yangle << "\n";
			myfile << "Zangle: "<< currentState.sbg.Zangle << "\n";

			myfile << "XangleAcc: "<< currentState.sbg.XangleAcc << "\n";
			myfile << "YangleAcc: "<< currentState.sbg.YangleAcc << "\n";
			myfile << "ZangleAcc: "<< currentState.sbg.ZangleAcc << "\n";

			myfile << "gpsLatitude: "<< currentState.sbg.gpsLatitude << "\n";
			myfile << "gpsLongitude: "<< currentState.sbg.gpsLongitude << "\n";
			myfile << "gpsAltitude: "<< currentState.sbg.gpsAltitude << "\n";

			myfile << "barometricAltitude: "<< currentState.sbg.barometricAltitude << "\n";

			myfile << "velocityN: "<< currentState.sbg.velocityN << "\n";
			myfile << "velocityE: "<< currentState.sbg.velocityE << "\n";
			myfile << "velocityD: "<< currentState.sbg.velocityD << "\n";

			myfile << "filteredXacc: "<< currentState.sbg.filteredXacc << "\n";
			myfile << "filteredYacc: "<< currentState.sbg.filteredYacc << "\n";
			myfile << "filteredZacc: "<< currentState.sbg.filteredZacc << "\n";

			myfile << "solutionStatus: "<< currentState.sbg.solutionStatus << "\n";

			myfile.close();
		}
		else {
			std::cout << "Unable to open " << filename.c_str() << "\n";
		}
	}
}