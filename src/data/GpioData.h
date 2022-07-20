#pragma once
#include "config.h"
#include <map>
#include <string>
#include "arduino/DCMotorState.h"

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
