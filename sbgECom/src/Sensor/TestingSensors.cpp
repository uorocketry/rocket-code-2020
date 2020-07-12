#ifdef TESTING
#include "../helpers/Helper.h"
#include "../rocketState.h"
#include "TestingSensors.h"

#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void TestingSensors::run() {
	return;
}


void TestingSensors::initialize() {
	ifstream logFile("./data/test.csv");

	std::cout << "read file" << std::endl;

	string line;
	bool headerRow = true;
	while (std::getline(logFile, line)) {
		if (headerRow) { 
			headerRow = false;
			continue;
		}

		stringstream lineStream(line);
		string cell;

		vector<std::string> currentRow = helper::stringSplit(line, ',');
		std::cout << "current line: " << line << std::endl;

		rocketState rocketState;
		
		// SBG:
		rocketState.sbg.Xangle = processFloat(currentRow[0]);
		rocketState.sbg.Yangle = processFloat(currentRow[1]);
		rocketState.sbg.Zangle = processFloat(currentRow[2]);
		rocketState.sbg.XangleAcc = processFloat(currentRow[3]);
		rocketState.sbg.YangleAcc = processFloat(currentRow[4]);
		rocketState.sbg.ZangleAcc = processFloat(currentRow[5]);
		rocketState.sbg.gpsLatitude = processDouble(currentRow[6]);
		rocketState.sbg.gpsLongitude = processDouble(currentRow[7]);
		rocketState.sbg.gpsAltitude = processDouble(currentRow[8]);
		rocketState.sbg.barometricAltitude = processFloat(currentRow[9]);
		rocketState.sbg.velocityN = processFloat(currentRow[10]);
		rocketState.sbg.velocityE = processFloat(currentRow[11]);
		rocketState.sbg.velocityD = processFloat(currentRow[12]);
		rocketState.sbg.filteredXacc = processFloat(currentRow[13]);
		rocketState.sbg.filteredYacc = processFloat(currentRow[14]);
		rocketState.sbg.filteredZacc = processFloat(currentRow[15]);
		rocketState.sbg.solutionStatus = processInt(currentRow[16]);
		
		data.push(rocketState);
	}

	std::cout << "loaded all lines " << std::endl;
}

rocketState TestingSensors::getLatest() {
	rocketState currentData = data.front();
	data.pop();

	return currentData;
}

int TestingSensors::processInt(std::string data) {
	return strtol(data.c_str(), nullptr, 10);
}

float TestingSensors::processFloat(std::string data) {
	return strtof(data.c_str(), nullptr);
}

double TestingSensors::processDouble(std::string data) {
	return strtod(data.c_str(), nullptr);
}

#endif
