#pragma once
#include "config.h"

#include "Output.h"

#include "IO/ArduinoProxy.h"
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

    ArduinoProxy *arduinoProxy;
};
