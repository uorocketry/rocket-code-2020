#include "config.h"
#if TESTING == 1

#include "TestingSensors.h"
#include "data/sensorsData.h"
#include "helpers/Helper.h"

#include <fstream>


void TestingSensors::run()
{
}

void TestingSensors::initialize()
{
    createThread = false;

    std::ifstream logFile(helper::getEnvOrDefault("TESTING_INPUT_FILE", "./data/test-data.csv"));

    std::string line;
    while (std::getline(logFile, line))
    {
        std::stringstream lineStream(line);
        std::string cell;

        std::vector<std::string> currentRow;
        boost::split(currentRow, line, boost::is_any_of(","));

        sensorsData currentData;

        // Will keep increasing by one for each read
        int count = 0;

        currentData.timeStamp = helper::processUInt64(currentRow[count++]);

        // Ignore the state, that's an output value
        count++;

#if USE_SBG == 1
        // SBG:
        currentData.sbg.roll = helper::processFloat(currentRow[count++]);
        currentData.sbg.pitch = helper::processFloat(currentRow[count++]);
        currentData.sbg.yaw = helper::processFloat(currentRow[count++]);

        currentData.sbg.rollAccuracy = helper::processFloat(currentRow[count++]);
        currentData.sbg.pitchAccuracy = helper::processFloat(currentRow[count++]);
        currentData.sbg.yawAccuracy = helper::processFloat(currentRow[count++]);

        currentData.sbg.gpsLatitude = helper::processDouble(currentRow[count++]);
        currentData.sbg.gpsLongitude = helper::processDouble(currentRow[count++]);
        currentData.sbg.gpsAltitude = helper::processDouble(currentRow[count++]);

        currentData.sbg.barometricAltitude = helper::processFloat(currentRow[count++]);
        currentData.sbg.relativeBarometricAltitude = helper::processFloat(currentRow[count++]);

        currentData.sbg.velocityN = helper::processFloat(currentRow[count++]);
        currentData.sbg.velocityE = helper::processFloat(currentRow[count++]);
        currentData.sbg.velocityD = helper::processFloat(currentRow[count++]);

        currentData.sbg.filteredXaccelerometer = helper::processFloat(currentRow[count++]);
        currentData.sbg.filteredYaccelerometer = helper::processFloat(currentRow[count++]);
        currentData.sbg.filteredZaccelerometer = helper::processFloat(currentRow[count++]);

        currentData.sbg.solutionStatus = helper::processUInt32(currentRow[count++]);

        currentData.sbg.gpsPosStatus = helper::processUInt32(currentRow[count++]);

        currentData.sbg.gpsPosAccuracyLatitude = helper::processFloat(currentRow[count++]);
        currentData.sbg.gpsPosAccuracyLongitude = helper::processFloat(currentRow[count++]);
        currentData.sbg.gpsPosAccuracyAltitude = helper::processFloat(currentRow[count++]);

        currentData.sbg.NumSvUsed = helper::processUInt32(currentRow[count++]);

        currentData.sbg.velocityNAccuracy = helper::processFloat(currentRow[count++]);
        currentData.sbg.velocityEAccuracy = helper::processFloat(currentRow[count++]);
        currentData.sbg.velocityDAccuracy = helper::processFloat(currentRow[count++]);

        currentData.sbg.latitudeAccuracy = helper::processFloat(currentRow[count++]);
        currentData.sbg.longitudeAccuracy = helper::processFloat(currentRow[count++]);
        currentData.sbg.altitudeAccuracy = helper::processFloat(currentRow[count++]);

        currentData.sbg.pressureStatus = helper::processUInt32(currentRow[count++]);
        currentData.sbg.barometricPressure = helper::processFloat(currentRow[count++]);

        currentData.sbg.imuStatus = helper::processUInt32(currentRow[count++]);

        currentData.sbg.gyroX = helper::processFloat(currentRow[count++]);
        currentData.sbg.gyroY = helper::processFloat(currentRow[count++]);
        currentData.sbg.gyroZ = helper::processFloat(currentRow[count++]);

        currentData.sbg.temp = helper::processFloat(currentRow[count++]);

        currentData.sbg.deltaVelX = helper::processFloat(currentRow[count++]);
        currentData.sbg.deltaVelY = helper::processFloat(currentRow[count++]);
        currentData.sbg.deltaVelZ = helper::processFloat(currentRow[count++]);

        currentData.sbg.deltaAngleX = helper::processFloat(currentRow[count++]);
        currentData.sbg.deltaAngleY = helper::processFloat(currentRow[count++]);
        currentData.sbg.deltaAngleZ = helper::processFloat(currentRow[count++]);

#endif

        // Initialization data
#if USE_LOGGER == 1
        currentData.loggerIsInitialized = helper::processUInt32(currentRow[count++]);
#endif

#if USE_SOCKET_CLIENT == 1
        currentData.clientIsInitialized = helper::processUInt32(currentRow[count++]);
#endif

#if USE_SBG == 1
        currentData.sbgIsInitialized = helper::processUInt32(currentRow[count++]);
#endif

#if USE_INPUT == 1
        currentData.inputIsInitialized = helper::processUInt32(currentRow[count++]);
#endif

#if USE_RADIO == 1
        currentData.radioIsInitialized = helper::processUInt32(currentRow[count++]);
#endif

#if USE_GPIO == 1
        currentData.gpioIsInitialized = helper::processUInt32(currentRow[count++]);
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
        sensorsData currentData;
        currentData.outOfData = true;

        return currentData;
    }
}

bool TestingSensors::isInitialized()
{
    // Unused when in testing mode
    return true;
}

#endif
