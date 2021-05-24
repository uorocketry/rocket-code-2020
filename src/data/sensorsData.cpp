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

    return result;
}
