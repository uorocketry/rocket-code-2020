#pragma once

struct GpioData
{
    std::map<std::string, int> digitalMap;
    std::map<std::string, int> pwmMap;
};
