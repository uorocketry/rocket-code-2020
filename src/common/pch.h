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
#include <spdlog/spdlog.h>

// sbgECom library
#include <sbgCommon.h>
#include <sbgEComLib.h>

// WiringPi
#include "wiringPi.h"
#include "wiringSerial.h"

// Boost Library
#include <boost/algorithm/string/classification.hpp> // String Algorithms
#include <boost/algorithm/string/split.hpp>          // Split string
#include <boost/algorithm/string/trim.hpp>           // Trim string
#include <boost/assert.hpp>                          // Assertions
#include <boost/lexical_cast.hpp>                    // Converting between types
#include <boost/lockfree/queue.hpp>                  // Lock free queue
#include <boost/static_assert.hpp>                   // Static assertions

// UoRocketry
#include "common/environment.h"
#include "common/types.h"