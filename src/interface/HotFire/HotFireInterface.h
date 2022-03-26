#pragma once

#include "config.h"

#include "IO/ArduinoProxy.h"
#include "IO/Input.h"
#include "IO/Radio.h"
#include "IO/SBGSensor.h"
#include "IO/SensorLogger.h"
#include "IO/gpio/Gpio.h"
#include "IO/tcp/SocketServer.h"
#include <IO/Sensors.h>
#include <interface/Interface.h>
#include <memory>
#include <spdlog/logger.h>
#include <string>

class HotFireInterface : public Interface
{
  public:
    HotFireInterface();
    ~HotFireInterface();

    void initialize() override;

    // to get the latest rocket state. return a pointer to latestState
    std::shared_ptr<StateData> getLatest() override;

    // loop over each sensor and update the latestState
    bool updateInputs() override;
    bool updateOutputs(std::shared_ptr<StateData> data) override;

    void createNewGpioOutput(std::string name, int pinNbr) override;
    void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm) override;

    time_point getCurrentTime() override;

  private:
    void initializeInputs();
    void initializeOutputs();

    std::shared_ptr<spdlog::logger> logger;

    std::shared_ptr<StateData> latestState;
    EventQueue eventQueue;

    /**
     * IO instances
     */
    Input input;
    SocketServer client;
    SensorLogger sensorLogger;
    Gpio gpio;
    ArduinoProxy *arduinoProxy;
    Sensors sensors;
};
