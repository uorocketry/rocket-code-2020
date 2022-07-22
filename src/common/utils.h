#pragma once
#include "common/pch.h"
#include <boost/lexical_cast.hpp>

namespace utils
{

uint64_t getMonotonicTimeStamp();

template <typename T>
T getEnvOrDefault(const std::string &envName, T defaultValue)
{
    const char *value = std::getenv(envName.c_str());
    return value ? boost::lexical_cast<T>(value) : defaultValue;
}

} // namespace utils
