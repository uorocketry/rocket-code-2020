#pragma once

#include "common/pch.h"
#include "config.h"
#include "data/SensorsData.h"
#include <memory>
#include <string>

class Interface
{
  public:
    virtual void initialize() = 0;

    virtual void calibrateTelemetry() = 0;

    // to get the latest rocket state. return a pointer to latestState
    virtual std::shared_ptr<SensorsData> getLatest() = 0;

    // loop over each sensor and update the latestState
    virtual bool updateInputs() = 0;

    virtual bool updateOutputs(std::shared_ptr<SensorsData> data) = 0;

    virtual void createNewGpioOutput(std::string name, int pinNbr) = 0;

    virtual void createNewGpioPwmOutput(std::string name, int pinNbr, int safePosition, bool softpwm) = 0;

    virtual time_point getCurrentTime() = 0;
};
