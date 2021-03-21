#pragma once
#include "config/config.h"
#include <unordered_map>
#include <string>
struct GpioData {
    std::unordered_map<std::string, int> outputMap;
    std::unordered_map<std::string, int> pwmOutputMap;
};