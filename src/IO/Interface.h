#pragma once

#include "common/pch.h"
#include "config.h"
#include "data/StateData.h"
#include <memory>
#include <string>

class Interface
{
  public:
    virtual void initialize() = 0;

    virtual void calibrateTelemetry() = 0;

    // to get the latest rocket state. return a pointer to latestState
    virtual std::shared_ptr<StateData> getLatest() = 0;

    // loop over each sensor and update the latestState
    virtual bool updateInputs() = 0;

    virtual bool updateOutputs(std::shared_ptr<StateData> data) = 0;

#if USE_GPIO == 1

    virtual void createNewGpioOutput(std::string name, int pinNbr) = 0;

    virtual void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm) = 0;

    virtual void createNewGpioDCMotorOutput(std::string name, int pinForward, int pinReverse, int motorPower,
                                            int limitSwitchMinPin, int limitSwitchMaxPin, int potentiometerPin) = 0;

#endif

#if USE_LOGGER == 1
    virtual void restartLogger() = 0;
#endif

    virtual time_point getCurrentTime() = 0;
};
