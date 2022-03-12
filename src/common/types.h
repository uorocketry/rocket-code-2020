#pragma once
#include "common/pch.h"

using time_point = std::chrono::time_point<std::chrono::steady_clock>;
using duration_ns = std::chrono::duration<int64_t, std::nano>;
using duration_ms = std::chrono::duration<int64_t, std::milli>;

using eventType = long;