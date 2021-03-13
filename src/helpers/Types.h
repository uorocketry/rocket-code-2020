#pragma once

#include <chrono>

#define minimum(a,b) ((a)<(b)?(a):(b))
#define maximum(a,b) ((a)>(b)?(a):(b))

typedef std::chrono::time_point<std::chrono::steady_clock> time_point;
typedef std::chrono::duration<int64_t, std::nano> duration_ns;
typedef std::chrono::duration<int64_t, std::milli> duration_ms;

typedef long int eventType;
