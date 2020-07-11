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
		rocketState.sbg = {processFloat(currentRow[0]), processFloat(currentRow[1]), processFloat(currentRow[2]), processFloat(currentRow[3]), processFloat(currentRow[4]), processFloat(currentRow[5]), processDouble(currentRow[6]), processDouble(currentRow[7]), processDouble(currentRow[8]), processFloat(currentRow[9]), processFloat(currentRow[10]), processFloat(currentRow[11]), processFloat(currentRow[12]), processFloat(currentRow[13]),  processFloat(currentRow[14]), processFloat(currentRow[15]), processInt(currentRow[16])};
		data.push(rocketState);
	}

	std::cout << "loaded all lines " << std::endl;
}

rocketState TestingSensors::getLatest() {
	// mutex
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
