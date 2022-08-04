#pragma once

#include <chrono>

struct StepperMotorState
{
    int stepPin;
    int directionPin;
    bool minLimitSwitch;
    bool maxLimitSwitch;
    int speed;
    std::chrono::time_point<std::chrono::steady_clock> time;
};