#pragma once

#ifndef USE_SBG
    #define USE_SBG 0
#endif

#ifndef USE_SOCKET_CLIENT
    #define USE_SOCKET_CLIENT 0
#endif

#ifndef USE_LOGGER
    #define USE_LOGGER 1
#endif

#ifndef USE_INPUT
    #define USE_INPUT 1
#endif

#ifndef TESTING
    #define TESTING 0
#endif

#ifndef USE_RADIO
    #if TESTING == 1
        #define USE_RADIO 0
    #else
        #define USE_RADIO 0
    #endif
#endif

#ifndef SKIP_INIT
    #define SKIP_INIT 0
#endif

#ifndef USE_GPIO
    #define USE_GPIO 1
#endif

#if USE_GPIO == 1
    #ifndef USE_WIRING_Pi
        #define USE_WIRING_Pi 1
    #endif
#endif