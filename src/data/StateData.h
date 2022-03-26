#pragma once

#include "SensorState.h"
#include "common/pch.h"
#include "data/GpioData.h"
#include "data/SBGData.h"
#include "data/UOSMData.h"
#include <unordered_map>

// all the informations about the rocket that the state machine will need
struct StateData
{
    bool isInitialized() const;
    std::string convertToReducedString() const;

    uint64_t timeStamp = 0;
    uint16_t currentStateNo = 0;
    eventType eventNumber = -1;

    /**
     * SBG
     */
    sbgData sbg;
    bool sbgIsInitialized = false;

    /**
     * GPIO
     */
    GpioData gpioData;
    GpioState gpioState;
    bool gpioIsInitialized = false;

    /**
     * Logger
     */
    bool loggerIsInitialized = false;
    bool loggerWorking = false;

    /**
     * Socket Client
     */
    bool clientIsInitialized = false;
    uint64_t lastActiveClientTimestamp = 0;

    /**
     * Input
     */
    bool inputIsInitialized = false;

    /**
     * Radio
     */
    bool radioIsInitialized = false;

    /**
     * Arduino Proxy
     */
    bool arduinoProxyIsInitialized = false;

    /**
     * Sensor
     */
    SensorState sensorState;

    bool outOfData = false;
};
