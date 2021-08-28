#pragma once

#include "config/config.h"

#if USE_GPIO == 1

#include "Output.h"

#include <string>
#include <spdlog/logger.h>

class PwmOutput : public Output
{
public:
    PwmOutput(std::string name, int pin, bool softPWM = false);

    bool setValue(int value) override;

private:
    std::shared_ptr<spdlog::logger> logger;
    const std::string name;
    const int pinNbr;
    const bool softPWM;

#if USE_ARDUINO_PROXY == 1
    int fd = 0;
    
//     struct InitFlags
// 	{
// 		InitStatus wiringPiStatus = INIT;
// 	} status;
#endif

};

#endif