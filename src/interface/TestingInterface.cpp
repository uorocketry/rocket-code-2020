#include "config.h"
#include <spdlog/spdlog.h>

#include "TestingInterface.h"

TestingInterface::TestingInterface()
{
    logger = spdlog::default_logger();
}

TestingInterface::~TestingInterface() = default;

void TestingInterface::initialize()
{
    SPDLOG_LOGGER_INFO(logger, "Initializing TESTING...");
    testingSensors.initialize();

    initializeOutputs();
}

void TestingInterface::initializeOutputs()
{
    SPDLOG_LOGGER_INFO(logger, "Initializing LOGGER...");
    sensorLogger.initialize();
}

bool TestingInterface::updateInputs()
{
    latestState = std::make_shared<StateData>(testingSensors.getLatest());

    return true;
}

bool TestingInterface::updateOutputs(std::shared_ptr<StateData> data)
{
    if (latestState->outOfData)
    {
        if (!sensorLogger.queueEmpty())
        {
            // Wait for logger to finish
            return false;
        }

        exit(EXIT_SUCCESS);
    }

    sensorLogger.enqueueSensorData(*data);

    return true;
}

void TestingInterface::calibrateTelemetry()
{
}

std::shared_ptr<StateData> TestingInterface::getLatest()
{
    return latestState;
}

time_point TestingInterface::getCurrentTime()
{
    if (latestState != nullptr)
    {
        return time_point(std::chrono::duration_cast<time_point::duration>(duration_ns(latestState->timeStamp)));
    }
    else
    {
        return time_point(std::chrono::duration_cast<time_point::duration>(duration_ns(0)));
    }
}
