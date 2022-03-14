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

    virtual void calibrateTelemetry(){};

    // to get the latest rocket state. return a pointer to latestState
    virtual std::shared_ptr<StateData> getLatest() = 0;

    // loop over each sensor and update the latestState
    virtual bool updateInputs() = 0;

    virtual bool updateOutputs(std::shared_ptr<StateData> data) = 0;

    virtual void createNewGpioOutput(std::string name, int pinNbr){};

    virtual void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm){};

    virtual time_point getCurrentTime() = 0;
};
