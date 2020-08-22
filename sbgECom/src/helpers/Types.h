#pragma once

#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> time_point;
typedef std::chrono::duration<int64_t, std::nano> duration_ns;
typedef std::chrono::duration<int64_t, std::milli> duration_ms;

