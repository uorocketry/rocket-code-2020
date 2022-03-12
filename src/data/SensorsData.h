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

    // SBG
    sbgData sbg;
    bool sbgIsInitialized = false;

    // Gpio
    GpioData gpioData;
    GpioData gpioState;
    bool gpioIsInitialized = false;


    // Socket Client
    bool clientIsInitialized = false;
    uint64_t lastActiveClientTimestamp = 0;

    // Use input
    bool inputIsInitialized = false;

    // Radio
    bool radioIsInitialized = false;

    // Arduino Proxy
    bool arduinoProxyIsInitialized = false;

    // Testing
    bool outOfData = false;

    // Logger
    bool loggerWorking;
    bool loggerIsInitialized = false;
};
