#include "sensorsData.h"

bool sensorsData::isInitialized() const {
    bool result = true;

#if USE_LOGGER
    result &= loggerIsInitialized;
#endif

#if USE_SOCKET_CLIENT
    result &= clientIsInitialized;
#endif

#if USE_SBG
    result &= sbgIsInitialized;
#endif

#if USE_INPUT
    result &= inputIsInitialized;
#endif

#if USE_RADIO
    result &= radioIsInitialized;
#endif

#if USE_GPIO
    result &= gpioIsInitialized;
#endif

#if USE_ARDUINO_PROXY
    result &= arduinoProxyIsInitialized;
#endif

    return result;
}

/**
 * Convert a reduced set of sensorsData variables to a comma delimited string. There is NO newline character at the end
 * of the returned string.
 */
std::string sensorsData::convertToReducedString() const {
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
#endif

#if USE_LOGGER == 1
    data += std::to_string(loggerWorking);
    data += ",";
#endif // USE_LOGGER

    return data;
}
