#pragma once
#include "config/config.h"
#if USE_GPIO == 1

#include <string>

class Output
{
public:
    Output(const std::string& name, int pin);

    
    bool setValue(int value);

private:
    std::string name;
    int currentState{};
    const int pinNbr;
};

#endif