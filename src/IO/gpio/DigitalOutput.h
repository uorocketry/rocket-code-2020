#pragma once
#include "IO/ArduinoProxy.h"
#include "Output.h"
#include "config.h"

class DigitalOutput : public Output
{
  public:
    DigitalOutput(const std::string &name, int pin);

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
