#pragma once
#include "config/config.h"
#if USE_GPIO == 1

#include "Output.h"

#include <string>
#include <spdlog/logger.h>

class PwmOutput: public Output
{
public:
    PwmOutput(const std::string& name, int pin);

    
    bool setValue(int value);

private:
    std::shared_ptr<spdlog::logger> logger;
    std::string name;
    const int pinNbr;
};

#endif