#include "config.h"
#if TESTING != 1

#include "IO/IO.h"
#include "IO/TestingSensors.h"
#include "InterfaceImpl.h"
#include "common/pch.h"
#include "common/utils.h"
#include "data/UOSMData.h"
#include <chrono>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

InterfaceImpl::InterfaceImpl()
    : eventQueue()
#if USE_INPUT == 1
      ,
      input(eventQueue)
#endif
#if USE_SOCKET_CLIENT == 1
      ,
      client(eventQueue)
#endif
#if USE_RADIO == 1
      ,
      radio(eventQueue)
#endif
{
    logger = spdlog::default_logger();
}

InterfaceImpl::~InterfaceImpl() = default;

void InterfaceImpl::initialize()
{
    initializeInputs();
    initializeOutputs();
}

void InterfaceImpl::initializeInputs()
{
#if USE_SBG == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing SBG...");
    mySbgSensor.initialize();
#endif
#if USE_INPUT == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing INPUT...");
    input.initialize();
#endif
#if USE_SOCKET_CLIENT == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing SOCKET_CLIENT...");
    client.initialize();
#endif
#if USE_ARDUINO_PROXY == 1
    arduinoProxy = ArduinoProxy::getInstance();
#endif
#if USE_SENSORS
    sensors.initialize();
#endif
}

void InterfaceImpl::initializeOutputs()
{
#if USE_LOGGER == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing SENSOR_LOGGER...");
    sensorLogger.initialize();
#endif
#if USE_RADIO == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing RADIO...");
    radio.initialize();
#endif
#if USE_GPIO == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing GPIO...");
    gpio.initialize();
#endif
#if USE_ARDUINO_PROXY == 1
    SPDLOG_LOGGER_INFO(logger, "Initializing Arduino Proxy...");
    arduinoProxy->initialize();
#endif

#if USE_SENSOR_SUITE
    SPDLOG_LOGGER_INFO(logger, "Initializing Sensor Suite...");
    sensorSuite.initialize();
#endif
}

bool InterfaceImpl::updateInputs()
{
    latestState = std::make_shared<StateData>();

    latestState->timeStamp = utils::getMonotonicTimeStamp();

#if USE_SBG == 1
    latestState->sbg = mySbgSensor.getData();
#endif

    latestState->eventNumber = eventQueue.pop();

#if USE_LOGGER == 1
    latestState->loggerIsInitialized = sensorLogger.isInitialized();
#endif

#if USE_SOCKET_CLIENT == 1
    latestState->clientIsInitialized = client.isInitialized();
    latestState->lastActiveClientTimestamp = client.getLastConnectionTimestamp();
#endif

#if USE_SBG == 1
    latestState->sbgIsInitialized = mySbgSensor.isInitialized();
#endif

#if USE_INPUT == 1
    latestState->inputIsInitialized = input.isInitialized();
#endif

#if USE_RADIO == 1
    latestState->radioIsInitialized = radio.isInitialized();
#endif

#if USE_GPIO == 1
    latestState->gpioIsInitialized = gpio.isInitialized();
    latestState->gpioState = gpio.getCurrentState();
#endif

#if USE_ARDUINO_PROXY == 1
    latestState->arduinoProxyIsInitialized = arduinoProxy->isInitialized();
#endif

#if USE_SENSORS == 1
    latestState->sensorState = sensors.getCurrentState();
#endif

#if USE_SENSOR_SUITE == 1
    latestState->sensorSuiteState = sensorSuite.getCurrentData();
#endif

    return true;
}

bool InterfaceImpl::updateOutputs(std::shared_ptr<StateData> data)
{

#if USE_GPIO == 1
    data->gpioData = gpio.setOutputs(data->gpioData);
#endif

#if USE_LOGGER == 1
    sensorLogger.enqueueSensorData(*data);
#endif

#if USE_RADIO == 1
    radio.enqueueSensorData(*data);
#endif

#if USE_SOCKET_CLIENT == 1
    client.enqueueSensorData(*data);
#endif

    return true;
}

#if USE_GPIO == 1
void InterfaceImpl::createNewGpioOutput(std::string name, int pinNbr, int safeState)
{
    gpio.createNewGpioOutput(name, pinNbr, safeState);
}

void InterfaceImpl::createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm)
{
    gpio.createNewGpioPwmOutput(name, pinNbr, safePosition, softpwm);
}
#endif

void InterfaceImpl::calibrateTelemetry()
{
#if USE_SBG == 1
    mySbgSensor.setZeroBarometricAltitude();
#endif
}

std::shared_ptr<StateData> InterfaceImpl::getLatest()
{

#if USE_LOGGER == 1
    latestState->loggerWorking = SensorLogger::working;
#endif // USE_LOGGER

    return latestState;
}

time_point InterfaceImpl::getCurrentTime()
{
    return std::chrono::steady_clock::now();
}

#if USE_LOGGER == 1
void InterfaceImpl::restartLogger()
{
    sensorLogger.restartLogger();
}
#endif

#endif