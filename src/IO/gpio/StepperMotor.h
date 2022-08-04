#pragma once

#include "config.h"

#if USE_GPIO == 1

#include "Output.h"
#include "arduino/StepperMotorState.h"

#if USE_ARDUINO_PROXY
#include "IO/ArduinoProxy.h"
#endif

#include <spdlog/logger.h>
#include <string>

class StepperMotor : public Output
{
  public:
    StepperMotor();

    bool setValue(int value) override;

    StepperMotorState getCurrentState();

  private:
    std::shared_ptr<spdlog::logger> logger;

#if USE_ARDUINO_PROXY == 1
    ArduinoProxy *arduinoProxy;
#endif
};

#endif