#pragma once
#include "common/pch.h"
#include <boost/lexical_cast.hpp>

namespace helper
{

template <typename T>
T getEnvOrDefault(const std::string &envName, T defaultValue)
{
    const char *value = std::getenv(envName.c_str());
    return value ? boost::lexical_cast<T>(value) : defaultValue;
}

template <class T>
struct SharedArray
{
    std::shared_ptr<T[]> data;
    size_t length;
};

} // namespace helper