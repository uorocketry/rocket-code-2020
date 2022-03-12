#include "Radio.h"
#include "common/pch.h"
#include "config.h"

#include "SensorLogger.h"
#include "data/SensorsData.h"

Radio::Radio(EventQueue &eventQueue) : eventQueue(eventQueue)
{
    logger = spdlog::default_logger();
}

Radio::~Radio() = default;

void Radio::initialize()
{
    if ((fd = serialOpen("/dev/ttyAMA0", 57600)) < 0)
    {
        SPDLOG_LOGGER_ERROR(logger, "Error while opening serial communication!");
        status.wiringPiStatus = INIT;
    }
    else
    {
        status.wiringPiStatus = READY;
    }

    wiringPiSetup();

    IO::initialize();
}

bool Radio::isInitialized()
{
    return (status.wiringPiStatus == READY);
}

void Radio::run()
{
    writingLock = std::unique_lock<std::mutex>(writingMutex);

    while (true)
    {
        if (serialDataAvail(fd) > 0)
        {
            eventQueue.push(serialGetchar(fd));
        }

        if (!logQueue.empty())
        {
            dequeueToRadio();
        }
        else
        {
            writingCondition.wait_for(writingLock, ONE_SECOND);
        }
    }
}

void Radio::enqueueSensorData(const SensorsData &curSensorData)
{
    std::lock_guard<std::mutex> lockGuard(mutex);
    logQueue.push(curSensorData);

    writingCondition.notify_one();
}

void Radio::dequeueToRadio()
{
    SensorsData currentState;
    {
        std::lock_guard<std::mutex> lockGuard(mutex);
        currentState = logQueue.front();
        logQueue.pop();
    }

    sendData(currentState);
}

void Radio::sendData(const SensorsData &currentState) const
{
    auto data = currentState.convertToReducedString();
    data += "\r\n";

    serialPrintf(fd, data.c_str());
}
