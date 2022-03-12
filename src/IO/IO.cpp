#include "IO.h"
#include <spdlog/spdlog.h>

void IO::initialize()
{
    if (createThread)
    {
        // create thread
        SPDLOG_DEBUG("Create Thread");

        thisThread = std::thread(&IO::run, this);
        thisThread.detach();
    }
}
