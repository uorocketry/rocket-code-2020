#pragma once
#include "config.h"
#include <map>
#include <string>
struct GpioData
{
    std::map<std::string, int> digitalOutputMap;
    std::map<std::string, int> pwmOutputMap;
};

struct GpioState
{
    std::map<std::string, int> digitalStateMap;
    std::map<std::string, int> pwmStateMap;
};
