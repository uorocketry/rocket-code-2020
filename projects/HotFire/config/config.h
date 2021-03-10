#pragma once

#ifndef USE_SBG
    #define USE_SBG 1
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
    #if TESTING
        #define USE_RADIO 0
    #else
        #define USE_RADIO 1
    #endif
#endif

#ifndef SKIP_INIT
    #define SKIP_INIT 0
#endif

#ifndef USE_GPIO
    #define USE_GPIO 1
#endif

#if USE_GPIO
    #ifndef PWMVALVE1
        #define PWMVALVE1 1
    #endif

#endif

#if PWMVALVE1
    #define PWMVALVE1PIN 6
    #define PWMVALVE1OPEN 0
    #define PWMVALVE1CLOSE 150
#endif

// because we can't use inputs if it is manual testing
#if TESTING
    #define USE_SOCKET_CLIENT 0
#endif