#include "config.h"
#if USE_LOGGER == 1

#include "SensorLogger.h"

#include "boost/filesystem.hpp"
#include "common/utils.h"
#include <iostream>
#include <mutex>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>
#include <vector>

int SensorLogger::working = 0;
SensorLogger::~SensorLogger() = default;

void SensorLogger::initialize()
{
    IO::initialize();
}

bool SensorLogger::isInitialized()
{
    return (status.fileStatus == READY);
}

void SensorLogger::run()
{
    auto path = utils::getEnvOrDefault<std::string>("LOG_PATH", "./sensor-data");
    std::string ext = ".uorocketlog";
    if (path.back() != '/')
        path += "/";

    writingLock = std::unique_lock<std::mutex>(writingMutex);

    if (!boost::filesystem::exists(path))
    {
        boost::filesystem::create_directories(path);
    }

    std::string filename = std::to_string(getBootId(path)) + ext;
    bool shouldWriteHeader = true;
    std::ofstream fileStream{path + filename, std::ios_base::ate};

    status.fileStatus = READY;

    bool isFirstLine = true;

    while (true)
    {
        if (restartingLogger)
        {
            restartingLogger = false;
            isFirstLine = true;
            filename = std::to_string(getBootId(path)) + ext;
            shouldWriteHeader = true;
        }

        if (!logQueue.empty())
        {

            // get data
            StateData currentState = getCurrentState();

            // write the headers if necessary
            if (shouldWriteHeader && isFirstLine)
            {
                writeToHeader(currentState, path, filename);
                isFirstLine = false;
            }

            // write to file
            bool successful = sendToWriteFile(fileStream, currentState, path, filename);

            // pop data if writing was succesful
            if (successful)
            {
                popData();
            }

            // close File Stream
            fileStream.close();
        }
        else
        {
            writingCondition.wait_for(writingLock, ONE_SECOND);
        }
    }
}

int SensorLogger::getBootId(std::string &path)
{
    int bootId = 0;

    for (auto &p : boost::filesystem::directory_iterator(path))
    {
        std::string itemPath = p.path().string();

        std::vector<std::string> tokens1;

        // stringstream class check1
        std::stringstream check1(itemPath);
        std::string intermediate;

        // splitting string with '/'
        while (getline(check1, intermediate, '/'))
        {
            tokens1.push_back(intermediate);
        }

        if (!tokens1.empty())
        {
            std::string currentLog = tokens1[tokens1.size() - 1];
            std::vector<std::string> tokens2;

            std::stringstream check2(currentLog);

            // splitting string with '.'
            while (getline(check2, intermediate, '.'))
            {
                tokens2.push_back(intermediate);
            }

            if (atoi(tokens2[0].c_str()) + 1 > bootId)
            {
                bootId = atoi(tokens2[0].c_str()) + 1;
            }
        }
    }

    return bootId;
}

void SensorLogger::enqueueSensorData(const StateData &curSensorData)
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    logQueue.push(curSensorData);

    writingCondition.notify_one();
}

bool SensorLogger::writeToFile(std::ofstream &fileStream, StateData currentState)
{
    if (fileStream.is_open())
    {
        working = 1;
        writeData(fileStream, currentState);
        return true;
    }
    else
    {
        SPDLOG_LOGGER_ERROR(logger, "Unable to open log file.");
        working = 0;
        return false;
    }
}

StateData SensorLogger::getCurrentState()
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    return logQueue.front();
}

void SensorLogger::writeToHeader(StateData currentState, std::string path, std::string filename)
{
    std::ofstream fileStream;
    fileStream.open(path + filename, std::ios_base::app);
    writeHeader(fileStream, currentState);
    fileStream.close();
}

bool SensorLogger::sendToWriteFile(std::ofstream &fileStream, StateData currentState, std::string path,
                                   std::string filename)
{
    fileStream.open(path + filename, std::ios_base::app);
    return writeToFile(fileStream, currentState);
}

void SensorLogger::popData()
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    logQueue.pop();
}

void SensorLogger::writeHeader(std::ofstream &fileStream, StateData currentState)
{

    fileStream << "Timestamp (Relative),";

    fileStream << "State Number,";

#if USE_GPIO == 1
    for (std::pair<std::string, int> output : currentState.gpioData.digitalOutputMap)
    {
        fileStream << output.first << ", ";
    }

    for (std::pair<std::string, int> output : currentState.gpioData.pwmOutputMap)
    {
        fileStream << output.first << ", ";
    }
#endif

#if USE_SBG == 1
    fileStream << "roll,";
    fileStream << "pitch,";
    fileStream << "yaw,";

    fileStream << "rollAccuracy,";
    fileStream << "pitchAccuracy,";
    fileStream << "yawAccuracy,";

    fileStream << "gpsLatitude,";
    fileStream << "gpsLongitude,";
    fileStream << "gpsAltitude,";

    fileStream << "barometricAltitude,";
    fileStream << "relativeBarometricAltitude,";

    fileStream << "velocityN,";
    fileStream << "velocityE,";
    fileStream << "velocityD,";

    fileStream << "filteredXaccelerometer,";
    fileStream << "filteredYaccelerometer,";
    fileStream << "filteredZaccelerometer,";

    fileStream << "solutionStatus,";

    fileStream << "gpsPosStatus,";

    fileStream << "gpsPosAccurracyLatitude,";
    fileStream << "gpsPosAccuracyLongitude,";
    fileStream << "gpsPosAccuracyAltitude,";

    fileStream << "NumSvUsed,";

    fileStream << "velocityNAccuracy,";
    fileStream << "velocityEAccuracy,";
    fileStream << "velocityDAccuracy,";

    fileStream << "latitudeAccuracy,";
    fileStream << "longitudeAccuracy,";
    fileStream << "altitudeAccuracy,";

    fileStream << "pressureStatus,";
    fileStream << "barometricPressure,";

    fileStream << "imuStatus,";

    fileStream << "gyroX,";
    fileStream << "gyroY,";
    fileStream << "gyroZ,";

    fileStream << "temp,";

    fileStream << "deltaVelX,";
    fileStream << "deltaVelY,";
    fileStream << "deltaVelZ,";

    fileStream << "deltaAngleX,";
    fileStream << "deltaAngleY,";
    fileStream << "deltaAngleZ,";
#endif

#if USE_SENSOR_SUITE == 1
    fileStream << "pressure1,";
    fileStream << "pressure2,";
    fileStream << "pressure3,";
    fileStream << "pressure4,";
    fileStream << "tankTransducer,";
    fileStream << "thrustTransducer,";
    fileStream << "digitalInputs,";
    fileStream << "daqSampleCount,";
    fileStream << "daqSampleCount2,";
    fileStream << "temp1,";
    fileStream << "temp2,";
    fileStream << "temp3,";
    fileStream << "temp4,";
    fileStream << "temp5,";
    fileStream << "temp6,";
    fileStream << "temp7,";
    fileStream << "temp8,";
    fileStream << "sensorSuiteTimestamp,";
#endif

// Initialization data
#if USE_LOGGER
    fileStream << "loggerInitialized, ";
#endif

#if USE_SOCKET_CLIENT
    fileStream << "clientInitialized, ";
    fileStream << "lastActiveClientTimestamp, ";
#endif

#if USE_SBG
    fileStream << "sbgInitialized, ";
#endif

#if USE_INPUT
    fileStream << "inputInitialized, ";
#endif

#if USE_RADIO
    fileStream << "radioInitialized, ";
#endif

#if USE_GPIO
    fileStream << "gpioInitialized, ";
#endif

#if USE_ARDUINO_PROXY
    fileStream << "arduinoProxyInitialized, ";
#endif
    fileStream << "\n";
    fileStream.flush();
}

void SensorLogger::writeData(std::ofstream &fileStream, const StateData &currentState)
{
    const char *sep = ",";

    // Keep in mind, this is NOT the time since unix epoch (1970), and not the
    // system time
    fileStream << currentState.timeStamp << sep;
    fileStream << currentState.currentStateNo << sep;

#if USE_GPIO == 1
    for (std::pair<std::string, int> output : currentState.gpioData.digitalOutputMap)
    {
        fileStream << output.second << sep;
    }

    for (std::pair<std::string, int> output : currentState.gpioData.pwmOutputMap)
    {
        fileStream << output.second << sep;
    }
#endif

#if USE_SBG == 1
    fileStream << currentState.sbg.roll << sep;
    fileStream << currentState.sbg.pitch << sep;
    fileStream << currentState.sbg.yaw << sep;

    fileStream << currentState.sbg.rollAccuracy << sep;
    fileStream << currentState.sbg.pitchAccuracy << sep;
    fileStream << currentState.sbg.yawAccuracy << sep;

    fileStream << currentState.sbg.gpsLatitude << sep;
    fileStream << currentState.sbg.gpsLongitude << sep;
    fileStream << currentState.sbg.gpsAltitude << sep;

    fileStream << currentState.sbg.barometricAltitude << sep;
    fileStream << currentState.sbg.relativeBarometricAltitude << sep;

    fileStream << currentState.sbg.velocityN << sep;
    fileStream << currentState.sbg.velocityE << sep;
    fileStream << currentState.sbg.velocityD << sep;

    fileStream << currentState.sbg.filteredXaccelerometer << sep;
    fileStream << currentState.sbg.filteredYaccelerometer << sep;
    fileStream << currentState.sbg.filteredZaccelerometer << sep;

    fileStream << currentState.sbg.solutionStatus << sep;

    fileStream << currentState.sbg.gpsPosStatus << sep;

    fileStream << currentState.sbg.gpsPosAccuracyLatitude << sep;
    fileStream << currentState.sbg.gpsPosAccuracyLongitude << sep;
    fileStream << currentState.sbg.gpsPosAccuracyAltitude << sep;

    fileStream << (int)currentState.sbg.NumSvUsed << sep;

    fileStream << currentState.sbg.velocityNAccuracy << sep;
    fileStream << currentState.sbg.velocityEAccuracy << sep;
    fileStream << currentState.sbg.velocityDAccuracy << sep;

    fileStream << currentState.sbg.latitudeAccuracy << sep;
    fileStream << currentState.sbg.longitudeAccuracy << sep;
    fileStream << currentState.sbg.altitudeAccuracy << sep;

    fileStream << currentState.sbg.pressureStatus << sep;
    fileStream << currentState.sbg.barometricPressure << sep;

    fileStream << currentState.sbg.imuStatus << sep;

    fileStream << currentState.sbg.gyroX << sep;
    fileStream << currentState.sbg.gyroY << sep;
    fileStream << currentState.sbg.gyroZ << sep;

    fileStream << currentState.sbg.temp << sep;

    fileStream << currentState.sbg.deltaVelX << sep;
    fileStream << currentState.sbg.deltaVelY << sep;
    fileStream << currentState.sbg.deltaVelZ << sep;

    fileStream << currentState.sbg.deltaAngleX << sep;
    fileStream << currentState.sbg.deltaAngleY << sep;
    fileStream << currentState.sbg.deltaAngleZ << sep;
#endif

#if USE_SENSOR_SUITE == 1
    fileStream << currentState.sensorSuiteState.pressure1 << sep;
    fileStream << currentState.sensorSuiteState.pressure2 << sep;
    fileStream << currentState.sensorSuiteState.pressure3 << sep;
    fileStream << currentState.sensorSuiteState.pressure4 << sep;
    fileStream << currentState.sensorSuiteState.tankTransducer << sep;
    fileStream << currentState.sensorSuiteState.thrustTransducer << sep;
    fileStream << currentState.sensorSuiteState.digitalInputs << sep;
    fileStream << currentState.sensorSuiteState.daqSampleCount << sep;
    fileStream << currentState.sensorSuiteState.daqSampleCount2 << sep;
    fileStream << currentState.sensorSuiteState.temp1 << sep;
    fileStream << currentState.sensorSuiteState.temp2 << sep;
    fileStream << currentState.sensorSuiteState.temp3 << sep;
    fileStream << currentState.sensorSuiteState.temp4 << sep;
    fileStream << currentState.sensorSuiteState.temp5 << sep;
    fileStream << currentState.sensorSuiteState.temp6 << sep;
    fileStream << currentState.sensorSuiteState.temp7 << sep;
    fileStream << currentState.sensorSuiteState.temp8 << sep;
    fileStream << currentState.sensorSuiteState.timestamp << sep;
#endif

// Initialization data
#if USE_LOGGER
    fileStream << currentState.loggerIsInitialized << sep;
#endif

#if USE_SOCKET_CLIENT
    fileStream << currentState.clientIsInitialized << sep;
    fileStream << currentState.lastActiveClientTimestamp << sep;
#endif

#if USE_SBG
    fileStream << currentState.sbgIsInitialized << sep;
#endif

#if USE_INPUT
    fileStream << currentState.inputIsInitialized << sep;
#endif

#if USE_RADIO
    fileStream << currentState.radioIsInitialized << sep;
#endif

#if USE_GPIO
    fileStream << currentState.gpioIsInitialized << sep;
#endif

#if USE_ARDUINO_PROXY
    fileStream << currentState.arduinoProxyIsInitialized << sep;
#endif

    fileStream << "\n";

    fileStream.flush();
}

bool SensorLogger::queueEmpty()
{
    return logQueue.empty();
}

void SensorLogger::restartLogger()
{
    restartingLogger = true;
}

#endif