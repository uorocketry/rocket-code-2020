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

int processInt(const std::string &data);

uint64_t processUInt64(const std::string &data);

uint32_t processUInt32(const std::string &data);

float processFloat(const std::string &data);

double processDouble(const std::string &data);

template <class T>
struct SharedArray
{
    std::shared_ptr<T[]> data;
    size_t length;
};
} // namespace helper