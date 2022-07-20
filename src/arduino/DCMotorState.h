#pragma once

#include <chrono>

struct DCMotorState {
    int position;
    int direction;
    std::chrono::time_point<std::chrono::steady_clock> time;
};