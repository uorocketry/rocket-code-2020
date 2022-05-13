#pragma once

#include "SensorState.h"
#include "common/pch.h"
#include "data/GpioData.h"
#include "data/SBGData.h"
#include "data/UOSMData.h"
#include <unordered_map>
#include <uorocketry/mavlink.h>

// all the informations about the rocket that the state machine will need
struct StateData
{
    bool isInitialized() const;
    std::string convertToReducedString() const;

    /**
     * Convert the state to a MAVLink message.
     *
     * @param mavlinkChan the MAVLink channel that the message will be sent over.
     * @return the MAVLink message.
     */
    mavlink_message_t convertToMAVLink() const;

    uint64_t timeStamp = 0;
    uint16_t currentStateNo = 0;
    eventType eventNumber = -1;

#if USE_SBG == 1
    sbgData sbg;
    bool sbgIsInitialized = 0;
#endif

#if USE_GPIO == 1
    GpioData gpioData;
    GpioState gpioState;
    bool gpioIsInitialized = 0;
#endif

#if USE_LOGGER
    bool loggerIsInitialized = 0;
#endif

#if USE_SOCKET_CLIENT
    bool clientIsInitialized = 0;
    uint64_t lastActiveClientTimestamp = 0;
#endif

#if USE_INPUT
    bool inputIsInitialized = 0;
#endif

#if USE_RADIO
    bool radioIsInitialized = 0;
#endif

#if USE_ARDUINO_PROXY
    bool arduinoProxyIsInitialized = 0;
#endif

#if USE_SENSORS
    SensorState sensorState;
#endif

#if TESTING == 1
    bool outOfData = false;
#endif

#if USE_LOGGER == 1
    bool loggerWorking = false;
#endif // USE_LOGGER
};
