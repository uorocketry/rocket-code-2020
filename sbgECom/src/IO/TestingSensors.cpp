#include "config/config.h"
#if TESTING

#include "helpers/Helper.h"
#include "data/sensorsData.h"
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

	std::ifstream logFile(helper::getEnvOrDefault("TESTING_INPUT_FILE", "./data/test-data.csv"));

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

		// Will keep increasing by one for each read
		int count = 0;

		//TODO: Load timestamp
		currentData.timeStamp = processUInt64(currentRow[count++]);

#if USE_SBG
		// SBG:
		currentData.sbg.roll = processFloat(currentRow[count++]);
		currentData.sbg.pitch = processFloat(currentRow[count++]);
		currentData.sbg.yaw = processFloat(currentRow[count++]);

		currentData.sbg.rollAccuracy = processFloat(currentRow[count++]);
		currentData.sbg.pitchAccuracy = processFloat(currentRow[count++]);
		currentData.sbg.yawAccuracy = processFloat(currentRow[count++]);

		currentData.sbg.gpsLatitude = processDouble(currentRow[count++]);
		currentData.sbg.gpsLongitude = processDouble(currentRow[count++]);
		currentData.sbg.gpsAltitude = processDouble(currentRow[count++]);

		currentData.sbg.barometricAltitude = processFloat(currentRow[count++]);
		currentData.sbg.relativeBarometricAltitude = processFloat(currentRow[10]);

		currentData.sbg.velocityN = processFloat(currentRow[count++]);
		currentData.sbg.velocityE = processFloat(currentRow[count++]);
		currentData.sbg.velocityD = processFloat(currentRow[count++]);

		currentData.sbg.filteredXaccelerometer = processFloat(currentRow[count++]);
		currentData.sbg.filteredYaccelerometer = processFloat(currentRow[count++]);
		currentData.sbg.filteredZaccelerometer = processFloat(currentRow[count++]);

		currentData.sbg.solutionStatus = processInt(currentRow[16]);

		// Ignore the state, that's an output value
		count++;

		currentData.sbg.gpsPosStatus = processFloat(currentRow[count++]);

		currentData.sbg.gpsPosAccuracyLatitude = processFloat(currentRow[count++]);
		currentData.sbg.gpsPosAccuracyLongitude = processFloat(currentRow[count++]);
		currentData.sbg.gpsPosAccuracyAltitude = processFloat(currentRow[count++]);

		currentData.sbg.NumSvUsed = processFloat(currentRow[count++]);

		currentData.sbg.velocityNAccuracy = processFloat(currentRow[count++]);
		currentData.sbg.velocityEAccuracy = processFloat(currentRow[count++]);
		currentData.sbg.velocityDAccuracy = processFloat(currentRow[count++]);

		currentData.sbg.latitudeAccuracy = processFloat(currentRow[count++]);
		currentData.sbg.longitudeAccuracy = processFloat(currentRow[count++]);
		currentData.sbg.altitudeAccuracy = processFloat(currentRow[count++]);

		currentData.sbg.pressureStatus = processFloat(currentRow[count++]);
		currentData.sbg.barometricPressure = processFloat(currentRow[count++]);

		currentData.sbg.imuStatus = processFloat(currentRow[count++]);

		currentData.sbg.gyroX = processFloat(currentRow[count++]);
		currentData.sbg.gyroY = processFloat(currentRow[count++]);
		currentData.sbg.gyroZ = processFloat(currentRow[count++]);

		currentData.sbg.temp = processFloat(currentRow[count++]);

		currentData.sbg.deltaVelX = processFloat(currentRow[count++]);
		currentData.sbg.deltaVelY = processFloat(currentRow[count++]);
		currentData.sbg.deltaVelZ = processFloat(currentRow[count++]);

		currentData.sbg.deltaAngleX = processFloat(currentRow[count++]);
		currentData.sbg.deltaAngleY = processFloat(currentRow[count++]);
		currentData.sbg.deltaAngleZ = processFloat(currentRow[count++]);

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

uint64_t TestingSensors::processUInt64(std::string data)
{
	return strtoull(data.c_str(), nullptr, 10);
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
