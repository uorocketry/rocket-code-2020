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

        std::vector<std::string> currentRow = helper::stringSplit(line, ',');

        // Trim all elements in currentRow
        for (auto &element : currentRow)
            boost::trim(element);

        sensorsData currentData;

        // Will keep increasing by one for each read
        int count = 0;

        currentData.timeStamp = boost::lexical_cast<uint64_t>(currentRow[count++]);

        // Ignore the state, that's an output value
        count++;

#if USE_SBG == 1
        // SBG:
        currentData.sbg.roll = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.pitch = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.yaw = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.rollAccuracy = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.pitchAccuracy = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.yawAccuracy = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.gpsLatitude = boost::lexical_cast<double>(currentRow[count++]);
        currentData.sbg.gpsLongitude = boost::lexical_cast<double>(currentRow[count++]);
        currentData.sbg.gpsAltitude = boost::lexical_cast<double>(currentRow[count++]);

        currentData.sbg.barometricAltitude = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.relativeBarometricAltitude = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.velocityN = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.velocityE = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.velocityD = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.filteredXaccelerometer = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.filteredYaccelerometer = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.filteredZaccelerometer = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.solutionStatus = boost::lexical_cast<uint32_t>(currentRow[count++]);

        currentData.sbg.gpsPosStatus = boost::lexical_cast<uint32_t>(currentRow[count++]);

        currentData.sbg.gpsPosAccuracyLatitude = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.gpsPosAccuracyLongitude = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.gpsPosAccuracyAltitude = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.NumSvUsed = boost::lexical_cast<int>(currentRow[count++]);

        currentData.sbg.velocityNAccuracy = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.velocityEAccuracy = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.velocityDAccuracy = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.latitudeAccuracy = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.longitudeAccuracy = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.altitudeAccuracy = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.pressureStatus = boost::lexical_cast<uint16_t>(currentRow[count++]);
        currentData.sbg.barometricPressure = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.imuStatus = boost::lexical_cast<uint32_t>(currentRow[count++]);

        currentData.sbg.gyroX = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.gyroY = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.gyroZ = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.temp = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.deltaVelX = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.deltaVelY = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.deltaVelZ = boost::lexical_cast<float>(currentRow[count++]);

        currentData.sbg.deltaAngleX = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.deltaAngleY = boost::lexical_cast<float>(currentRow[count++]);
        currentData.sbg.deltaAngleZ = boost::lexical_cast<float>(currentRow[count++]);

#endif

        // Initialization data
#if USE_LOGGER == 1
        currentData.loggerIsInitialized = boost::lexical_cast<bool>(currentRow[count++]);
#endif

#if USE_SOCKET_CLIENT == 1
        currentData.clientIsInitialized = boost::lexical_cast<bool>(currentRow[count++]);
#endif

#if USE_SBG == 1
        currentData.sbgIsInitialized = boost::lexical_cast<bool>(currentRow[count++]);
#endif

#if USE_INPUT == 1
        currentData.inputIsInitialized = boost::lexical_cast<bool>(currentRow[count++]);
#endif

#if USE_RADIO == 1
        currentData.radioIsInitialized = boost::lexical_cast<bool>(currentRow[count++]);
#endif

#if USE_GPIO == 1
        currentData.gpioIsInitialized = boost::lexical_cast<bool>(currentRow[count++]);
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
