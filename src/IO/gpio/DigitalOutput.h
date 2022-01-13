#pragma once
#include "config.h"
#if USE_GPIO == 1

#include "Output.h"

#if USE_ARDUINO_PROXY == 1
#include "IO/ArduinoProxy.h"
#endif

#include <spdlog/logger.h>
#include <string>

class DigitalOutput : public Output
{
  public:
    DigitalOutput(const std::string &name, const int pin);

    bool setValue(int value);

    int getCurrentState();

  private:
    std::shared_ptr<spdlog::logger> logger;
    std::string name;
    const int pinNbr;

#if USE_ARDUINO_PROXY == 1
    ArduinoProxy *arduinoProxy;
#endif
};

#endif