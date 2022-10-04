#include "config.h"

#if USE_GPIO == 1

#include "LoadCell.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <utility>
#include <wiringSerial.h>

LoadCell::LoadCell()
{
    createThread = false;
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created LoadCell");

#if USE_ARDUINO_PROXY == 1
    arduinoProxy = ArduinoProxy::getInstance();
#endif
}

int LoadCell::getCurrentState()
{
#if USE_ARDUINO_PROXY == 1
    try
    {
        return arduinoProxy->getLoadCellState();
    }
    catch (std::out_of_range &error)
    {
        return -1;
    }
#else
    return -1;
#endif
}

void LoadCell::run()
{
}

bool LoadCell::isInitialized()
{
    return true;
}

#endif