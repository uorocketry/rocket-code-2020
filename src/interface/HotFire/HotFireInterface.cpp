#include "config.h"

#include "HotFireInterface.h"
#include "common/pch.h"
#include <chrono>
#include <spdlog/spdlog.h>
#include <string>

HotFireInterface::HotFireInterface()
    : eventQueue(), input(eventQueue), client(eventQueue), arduinoProxy(ArduinoProxy::getInstance())
{
    logger = spdlog::default_logger();
}

HotFireInterface::~HotFireInterface() = default;

void HotFireInterface::initialize()
{
    initializeInputs();
    initializeOutputs();
}

void HotFireInterface::initializeInputs()
{
    SPDLOG_LOGGER_INFO(logger, "Initializing INPUT...");
    input.initialize();
    SPDLOG_LOGGER_INFO(logger, "Initializing SOCKET_CLIENT...");
    client.initialize();
    SPDLOG_LOGGER_INFO(logger, "Initializing SENSORS...");
    sensors.initialize();
}

void HotFireInterface::initializeOutputs()
{
    SPDLOG_LOGGER_INFO(logger, "Initializing SENSOR_LOGGER...");
    sensorLogger.initialize();
    SPDLOG_LOGGER_INFO(logger, "Initializing GPIO...");
    gpio.initialize();
    SPDLOG_LOGGER_INFO(logger, "Initializing Arduino Proxy...");
    arduinoProxy->initialize();
}

bool HotFireInterface::updateInputs()
{
    latestState = std::make_shared<StateData>();

    latestState->timeStamp =
        std::chrono::duration_cast<time_point::duration>(std::chrono::steady_clock::now().time_since_epoch()).count();

    // EventQueue
    latestState->eventNumber = eventQueue.pop();
    // Logger
    latestState->loggerIsInitialized = sensorLogger.isInitialized();
    // Socket Client
    latestState->clientIsInitialized = client.isInitialized();
    latestState->lastActiveClientTimestamp = client.getLastConnectionTimestamp();
    // Input
    latestState->inputIsInitialized = input.isInitialized();
    // GPIO
    latestState->gpioIsInitialized = gpio.isInitialized();
    latestState->gpioState = gpio.getCurrentState();
    // Arduino Proxy
    latestState->arduinoProxyIsInitialized = arduinoProxy->isInitialized();
    // Sensors
    latestState->sensorState = sensors.getCurrentState();

    return true;
}

bool HotFireInterface::updateOutputs(std::shared_ptr<StateData> data)
{

    data->gpioData = gpio.setOutputs(data->gpioData);
    sensorLogger.enqueueSensorData(*data);
    client.enqueueSensorData(*data);

    return true;
}

void HotFireInterface::createNewGpioOutput(std::string name, int pinNbr)
{
    gpio.createNewGpioOutput(name, pinNbr);
}

void HotFireInterface::createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm)
{
    gpio.createNewGpioPwmOutput(name, pinNbr, safePosition, softpwm);
}

std::shared_ptr<StateData> HotFireInterface::getLatest()
{

    latestState->loggerWorking = SensorLogger::working;

    return latestState;
}

time_point HotFireInterface::getCurrentTime()
{
    return std::chrono::steady_clock::now();
}