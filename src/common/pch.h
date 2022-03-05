#pragma once

// Standard Library
#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>

// Logging
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

// Boost Assert
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>

// UoRocketry
#include "common/types.h"