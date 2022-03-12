#pragma once
#include "common/pch.h"
#include "config.h"

#include "IO/ArduinoProxy.h"
#include "Output.h"

class PwmOutput : public Output
{
  public:
    PwmOutput(std::string name, int pin, const int safePosition, bool softPWM = false);

    bool setValue(int value) override;

    int getCurrentState();

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
