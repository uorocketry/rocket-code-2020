#include "StateData.h"

bool StateData::isInitialized() const
{
    bool result = true;

#if SKIP_INIT != 1

#if USE_LOGGER == 1
    result &= loggerIsInitialized;
#endif

#if USE_SOCKET_CLIENT == 1
    result &= clientIsInitialized;
#endif

#if USE_SBG == 1
    result &= sbgIsInitialized;
#endif

#if USE_INPUT == 1
    result &= inputIsInitialized;
#endif

#if USE_RADIO == 1
    result &= radioIsInitialized;
#endif

#if USE_GPIO == 1
    result &= gpioIsInitialized;
#endif

#if USE_ARDUINO_PROXY == 1
    result &= arduinoProxyIsInitialized;
#endif

#endif

    return result;
}

/**
 * Convert a reduced set of sensorsData variables to a comma delimited string.
 * There is NO newline character at the end of the returned string.
 */
std::string StateData::convertToReducedString() const
{
    std::string data;

    data += std::to_string(timeStamp);
    data += ",";
    data += std::to_string(currentStateNo);
    data += ",";

#if USE_SBG == 1
    data += std::to_string(sbg.roll);
    data += ",";
    data += std::to_string(sbg.pitch);
    data += ",";
    data += std::to_string(sbg.yaw);
    data += ",";
    data += std::to_string(sbg.rollAccuracy);
    data += ",";
    data += std::to_string(sbg.pitchAccuracy);
    data += ",";
    data += std::to_string(sbg.yawAccuracy);
    data += ",";
    data += std::to_string(sbg.gpsLatitude);
    data += ",";
    data += std::to_string(sbg.gpsLongitude);
    data += ",";
    data += std::to_string(sbg.gpsAltitude);
    data += ",";
    data += std::to_string(sbg.relativeBarometricAltitude);
    data += ",";
    data += std::to_string(sbg.velocityN);
    data += ",";
    data += std::to_string(sbg.velocityE);
    data += ",";
    data += std::to_string(sbg.velocityD);
    data += ",";
    data += std::to_string(sbg.filteredXaccelerometer);
    data += ",";
    data += std::to_string(sbg.filteredYaccelerometer);
    data += ",";
    data += std::to_string(sbg.filteredZaccelerometer);
    data += ",";
    data += std::to_string(sbg.solutionStatus);
    data += ",";
#endif // USE_SBG

#if USE_GPIO == 1
    for (std::pair<std::string, int> output : gpioData.digitalOutputMap)
    {
        data += std::to_string(output.second);
        data += ",";
    }
    for (std::pair<std::string, int> output : gpioData.pwmOutputMap)
    {
        data += std::to_string(output.second);
        data += ",";
    }
    for (std::pair<std::string, int> output : gpioState.digitalStateMap)
    {
        data += std::to_string(output.second);
        data += ",";
    }
    for (std::pair<std::string, int> output : gpioState.pwmStateMap)
    {
        data += std::to_string(output.second);
        data += ",";
    }
#endif

#if USE_LOGGER == 1
    data += std::to_string(loggerWorking);
    data += ",";
#endif // USE_LOGGER

#if USE_SENSOR_MAX_31865
    data += std::to_string(sensorState.temperature);
    data += ",";
#endif

    return data;
}
