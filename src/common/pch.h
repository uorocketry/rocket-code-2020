#pragma once

// Standard Library
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// Logging
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

// Boost libraries
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>

// UoRocketry
#include "common/types.h"