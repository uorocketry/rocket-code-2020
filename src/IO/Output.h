#pragma once
#include "config/config.h"
#if USE_GPIO

#include <string>

class Output
{
public:
    Output(const std::string name, const int pin);

    
    bool setValue(int value);

private:
    std::string name;
    int value;
    const int pinNbr;
};

#endif