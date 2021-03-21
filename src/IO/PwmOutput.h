#pragma once
#include "config/config.h"
#if USE_GPIO

#include <string>

class PwmOutput
{
public:
    PwmOutput(const std::string name, const int pin);

    
    bool setValue(int value);

private:
    std::string name;
    int currentState;
    const int pinNbr;
};

#endif