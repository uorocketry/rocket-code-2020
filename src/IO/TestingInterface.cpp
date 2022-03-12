#include "TestingInterface.h"
#include "config.h"
#include <spdlog/spdlog.h>

TestingInterface::TestingInterface()
    : eventQueue(2048)
#if USE_RADIO == 1
      ,
      radio(eventQueue)
#endif
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
#if USE_LOGGER == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing LOGGER...");
    sensorLogger.initialize();
#endif
#if USE_RADIO == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing RADIO...");
    radio.initialize();
#endif
}

bool TestingInterface::updateInputs()
{
    latestState = std::make_shared<SensorsData>(testingSensors.getLatest());

    return true;
}

bool TestingInterface::updateOutputs(std::shared_ptr<SensorsData> data)
{
#if USE_LOGGER == 1 && TESTING == 1
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
#endif

#if USE_RADIO == 1
    radio.enqueueSensorData(*data);
#endif

    return true;
}

void TestingInterface::createNewGpioOutput(std::string name, int pinNbr)
{
    return; // don't do anything for now
}
void TestingInterface::createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm)
{
    return; // don't do anything for now
}

void TestingInterface::calibrateTelemetry()
{
}

std::shared_ptr<SensorsData> TestingInterface::getLatest()
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
