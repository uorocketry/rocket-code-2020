#pragma once

#include "config.h"

#if USE_GPIO == 1

#include "IO/IO.h"
#include "Output.h"
#include "arduino/DCMotorState.h"

#if USE_ARDUINO_PROXY
#include "IO/ArduinoProxy.h"
#endif

#include <spdlog/logger.h>
#include <string>

class LoadCell : public IO
{
  public:
    LoadCell();

    uint32_t getCurrentState();
    void run() override;
    bool isInitialized() override;

  private:
    std::shared_ptr<spdlog::logger> logger;

#if USE_ARDUINO_PROXY == 1
    ArduinoProxy *arduinoProxy;
#endif
};

#endif