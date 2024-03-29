#pragma once
#include "arduino/DCMotorState.h"
#include "config.h"
#include <map>
#include <string>

struct GpioData
{
    std::map<std::string, int> digitalOutputMap;
    std::map<std::string, int> pwmOutputMap;
    std::map<std::string, int> dcOutputMap;
};

struct GpioState
{
    std::map<std::string, int> digitalStateMap;
    std::map<std::string, int> pwmStateMap;
    std::map<std::string, DCMotorState> dcMotorStateMap;
};
