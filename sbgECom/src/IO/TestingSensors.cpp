#include "config/config.h"
#if TESTING

#include "../helpers/Helper.h"
#include "../data/sensorsData.h"
#include "TestingSensors.h"

#include <sstream>
#include <fstream>
#include <string>
#include <vector>

void TestingSensors::run()
{
	return;
}

void TestingSensors::initialize()
{
	createThread = false;

	std::ifstream logFile("./data/test-data.csv");

	std::string line;
	bool headerRow = true;
	while (std::getline(logFile, line))
	{
		if (headerRow)
		{
			headerRow = false;
			continue;
		}

		std::stringstream lineStream(line);
		std::string cell;

		std::vector<std::string> currentRow = helper::stringSplit(line, ',');

		sensorsData currentData;

#if USE_SBG
		// SBG:
		currentData.sbg.Xangle = processFloat(currentRow[0]);
		currentData.sbg.Yangle = processFloat(currentRow[1]);
		currentData.sbg.Zangle = processFloat(currentRow[2]);
		currentData.sbg.XangleAcc = processFloat(currentRow[3]);
		currentData.sbg.YangleAcc = processFloat(currentRow[4]);
		currentData.sbg.ZangleAcc = processFloat(currentRow[5]);
		currentData.sbg.gpsLatitude = processDouble(currentRow[6]);
		currentData.sbg.gpsLongitude = processDouble(currentRow[7]);
		currentData.sbg.gpsAltitude = processDouble(currentRow[8]);
		currentData.sbg.barometricAltitude = processFloat(currentRow[9]);
		currentData.sbg.velocityN = processFloat(currentRow[10]);
		currentData.sbg.velocityE = processFloat(currentRow[11]);
		currentData.sbg.velocityD = processFloat(currentRow[12]);
		currentData.sbg.filteredXacc = processFloat(currentRow[13]);
		currentData.sbg.filteredYacc = processFloat(currentRow[14]);
		currentData.sbg.filteredZacc = processFloat(currentRow[15]);
		currentData.sbg.solutionStatus = processInt(currentRow[16]);
#endif

		data.push(currentData);
	}

	IO::initialize();
}

sensorsData TestingSensors::getLatest()
{
	if (!data.empty())
	{
		sensorsData currentData = data.front();
		data.pop();

		return currentData;
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

bool TestingSensors::isInitialized()
{
	// Unused when in testing mode
	return true;
}

int TestingSensors::processInt(std::string data)
{
	return strtol(data.c_str(), nullptr, 10);
}

float TestingSensors::processFloat(std::string data)
{
	return strtof(data.c_str(), nullptr);
}

double TestingSensors::processDouble(std::string data)
{
	return strtod(data.c_str(), nullptr);
}

#endif
