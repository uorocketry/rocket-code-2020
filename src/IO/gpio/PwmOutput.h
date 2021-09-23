#pragma once

#include "config/config.h"

#if USE_GPIO == 1

#include "Output.h"

#if USE_ARDUINO_PROXY
#include "IO/ArduinoProxy.h"
#endif

#include <spdlog/logger.h>
#include <string>

class PwmOutput : public Output
{
  public:
    PwmOutput(std::string name, int pin, const int safePosition, bool softPWM = false);

    bool setValue(int value) override;

  private:
    std::shared_ptr<spdlog::logger> logger;
    const std::string name;
    const int pinNbr;
    const int safePosition;
    const bool softPWM;

#if USE_ARDUINO_PROXY == 1
    ArduinoProxy *arduinoProxy;

//     struct InitFlags
// 	{
// 		InitStatus wiringPiStatus = INIT;
// 	} status;
#endif
};

#endif