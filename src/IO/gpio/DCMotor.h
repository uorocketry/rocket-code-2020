#pragma once

#include "config.h"

#if USE_GPIO == 1

#include "Output.h"
#include "arduino/DCMotorState.h"

#if USE_ARDUINO_PROXY
#include "IO/ArduinoProxy.h"
#endif

#include <spdlog/logger.h>
#include <string>

class DCMotorOutput : public Output
{
  public:
    DCMotorOutput(std::string name, int pinForward, int pinReverse, int motorPower, int limitSwitchMinPin,
                  int limitSwitchMaxPin, int potentiometerPin);

    bool setValue(int value) override;

    DCMotorState getCurrentState();

  private:
    std::shared_ptr<spdlog::logger> logger;
    const std::string name;
    const int pinNbrForward;
    const int pinNbrReverse;
    const int motorPower;
    const int limitSwitchMinPin;
    const int limitSwitchMaxPin;
    const int potentiometerPin;

#if USE_ARDUINO_PROXY == 1
    ArduinoProxy *arduinoProxy;
#endif
};

#endif