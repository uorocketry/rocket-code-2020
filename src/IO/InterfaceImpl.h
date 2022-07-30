#pragma once

#include "config.h"
#if TESTING != 1

#include "EventQueue.h"
#include "IO/ArduinoProxy.h"
#include "IO/Input.h"
#include "IO/Interface.h"
#include "IO/Radio.h"
#include "IO/SBGSensor.h"
#include "IO/SensorLogger.h"
#include "IO/SensorSuite.h"
#include "IO/gpio/Gpio.h"
#include "IO/tcp/SocketServer.h"
#include "Sensors.h"
#include <memory>
#include <spdlog/logger.h>
#include <string>

class InterfaceImpl : public Interface
{
  public:
    InterfaceImpl();
    ~InterfaceImpl();

    void initialize() override;

    void calibrateTelemetry();

    // to get the latest rocket state. return a pointer to latestState
    std::shared_ptr<StateData> getLatest() override;

    // loop over each sensor and update the latestState
    bool updateInputs() override;
    bool updateOutputs(std::shared_ptr<StateData> data) override;

#if USE_GPIO == 1
    void createNewGpioOutput(std::string name, int pinNbr, int safeState = 0) override;
    void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm) override;
    void createNewGpioDCMotorOutput(std::string name, int pinForward, int pinReverse, int motorPower,
                                    int limitSwitchMinPin, int limitSwitchMaxPin, int potentiometerPin) override;
#endif

#if USE_LOGGER == 1
    virtual void restartLogger() override;
#endif

    time_point getCurrentTime() override;

  private:
    void initializeInputs();
    void initializeOutputs();

    std::shared_ptr<spdlog::logger> logger;

    std::shared_ptr<StateData> latestState;
    EventQueue eventQueue;

#if USE_SBG == 1
    SBGSensor mySbgSensor;
#endif

#if USE_INPUT == 1
    Input input;
#endif

#if USE_SOCKET_CLIENT == 1
    SocketServer client;
#endif

#if USE_RADIO == 1
    Radio radio;
#endif

#if USE_LOGGER == 1
    SensorLogger sensorLogger;
#endif

#if USE_GPIO == 1
    Gpio gpio;
#endif

#if USE_ARDUINO_PROXY == 1
    ArduinoProxy *arduinoProxy;
#endif

#if USE_SENSORS == 1
    Sensors sensors;
#endif

#if USE_SENSOR_SUITE == 1
    SensorSuite sensorSuite;
#endif
};

#endif