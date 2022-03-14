#include "config.h"
#if TESTING != 1

#include "OctoberSkyInterface.h"
#include "common/pch.h"
#include <chrono>
#include <spdlog/spdlog.h>

OctoberSkyInterface::OctoberSkyInterface() : eventQueue(), radio(eventQueue)
{
    logger = spdlog::default_logger();
}

OctoberSkyInterface::~OctoberSkyInterface() = default;

void OctoberSkyInterface::initialize()
{
    initializeInputs();
    initializeOutputs();
}

void OctoberSkyInterface::initializeInputs()
{
    SPDLOG_LOGGER_INFO(logger, "Initializing SBG...");
    sbgSensor.initialize();
}

void OctoberSkyInterface::initializeOutputs()
{
    SPDLOG_LOGGER_INFO(logger, "Initializing SENSOR_LOGGER...");
    sensorLogger.initialize();

    SPDLOG_LOGGER_INFO(logger, "Initializing RADIO...");
    radio.initialize();
}

bool OctoberSkyInterface::updateInputs()
{
    latestState = std::make_shared<StateData>();

    latestState->timeStamp =
        std::chrono::duration_cast<time_point::duration>(std::chrono::steady_clock::now().time_since_epoch()).count();

    latestState->sbg = sbgSensor.getData();
    latestState->sbgIsInitialized = sbgSensor.isInitialized();

    latestState->eventNumber = eventQueue.pop();

    latestState->loggerIsInitialized = sensorLogger.isInitialized();

    latestState->radioIsInitialized = radio.isInitialized();

    return true;
}

bool OctoberSkyInterface::updateOutputs(std::shared_ptr<StateData> data)
{
    sensorLogger.enqueueSensorData(*data);

    radio.enqueueSensorData(*data);

    return true;
}

void OctoberSkyInterface::calibrateTelemetry()
{
    sbgSensor.setZeroBarometricAltitude();
}

std::shared_ptr<StateData> OctoberSkyInterface::getLatest()
{

    latestState->loggerWorking = SensorLogger::working;

    return latestState;
}

time_point OctoberSkyInterface::getCurrentTime()
{
    return std::chrono::steady_clock::now();
}

#endif