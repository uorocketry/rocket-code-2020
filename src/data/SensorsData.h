#pragma once

#include "common/pch.h"
#include "data/GpioData.h"
#include "data/SBGData.h"
#include "data/UOSMData.h"
#include <unordered_map>

// All the information about the rocket that the state machine will need
struct SensorsData
{
    bool isInitialized() const;
    std::string convertToReducedString() const;

    uint64_t timeStamp = 0;
    uint16_t currentStateNo = 0;
    eventType eventNumber = -1;

#if USE_SBG == 1
    sbgData sbg;
    bool sbgIsInitialized = false;
#endif

#if USE_GPIO == 1
    GpioData gpioData;
    GpioData gpioState;
    bool gpioIsInitialized = false;
#endif

#if USE_LOGGER
    bool loggerIsInitialized = false;
#endif

#if USE_SOCKET_CLIENT
    bool clientIsInitialized = false;
    uint64_t lastActiveClientTimestamp = 0;
#endif

#if USE_INPUT
    bool inputIsInitialized = false;
#endif

#if USE_RADIO
    bool radioIsInitialized = false;
#endif

#if USE_ARDUINO_PROXY
    bool arduinoProxyIsInitialized = false;
#endif

#if TESTING == 1
    bool outOfData = false;
#endif

#if USE_LOGGER == 1
    bool loggerWorking;
#endif // USE_LOGGER
};
