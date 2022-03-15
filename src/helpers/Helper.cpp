#include "Helper.h"

#include <boost/lexical_cast.hpp>
#include <cmath>

namespace helper
{
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