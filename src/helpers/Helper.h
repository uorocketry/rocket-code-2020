#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace helper
{

std::vector<std::string> stringSplit(const std::string &text, char delimiter);

const char *getEnvOrDefault(const char *envName, const char *defaultValue);

uint64_t getEnvOrDefault(const char *envName, uint64_t defaultValue);

template <class T>
struct SharedArray
{
    std::shared_ptr<T[]> data;
    size_t length;
};
} // namespace helper