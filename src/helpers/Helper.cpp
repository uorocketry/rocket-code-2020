#include "Helper.h"

#include <boost/lexical_cast.hpp>
#include <cmath>

namespace helper
{

std::vector<std::string> stringSplit(const std::string &text, char delimiter)
{
    std::stringstream lineStream(text);
    std::string cell;
    std::vector<std::string> result;

    while (std::getline(lineStream, cell, delimiter))
    {
        result.push_back(cell);
    }

    return result;
}

const char *getEnvOrDefault(const char *envName, const char *defaultValue)
{
    const char *value = std::getenv(envName);
    return value ? value : defaultValue;
}

uint64_t getEnvOrDefault(const char *envName, uint64_t defaultValue)
{
    const char *value = std::getenv(envName);
    return value ? boost::lexical_cast<uint64_t>(value) : defaultValue;
}

} // namespace helper