#include "IO.h"
#include "iostream"
#include <spdlog/spdlog.h>

IO::IO()
{
    logger = spdlog::default_logger();
}

IO::~IO()
{
    // destroy thread
    SPDLOG_LOGGER_DEBUG("destroy thread");
    thisThread.~thread(); // thread not killed
    SPDLOG_LOGGER_DEBUG(logger, "Thread testSensorThread killed:");
}

void IO::initialize()
{
    if (createThread)
    {
        // create thread
        SPDLOG_LOGGER_DEBUG(logger, "Create Thread");

        thisThread = std::thread(&IO::run, this);
        thisThread.detach();
    }
}
