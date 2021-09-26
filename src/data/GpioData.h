#pragma once
#include "config/config.h"
#include <map>
#include <string>
struct GpioData
{
    std::map<std::string, int> digitalOutputMap;
    std::map<std::string, int> pwmOutputMap;
};