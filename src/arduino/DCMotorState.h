#pragma once

#include <chrono>

struct DCMotorState
{
    int position;
    int direction;
    bool minLimitSwitch;
    bool maxLimitSwitch;
    std::chrono::time_point<std::chrono::steady_clock> time;
};