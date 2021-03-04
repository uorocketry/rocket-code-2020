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
    #ifndef VALVE1
        #define VALVE1 1
    #endif

    #ifndef VALVE2
        #define VALVE2 1
    #endif

    #ifndef VALVE3
        #define VALVE3 1
    #endif
#endif

#if VALVE1
    #define VALVE1PIN 6
    #define VALVE1OPEN 0
    #define VALVE1CLOSE 150
#endif

#if VALVE2
    #define VALVE1PIN 4
    #define VALVE1OPEN 0
    #define VALVE1CLOSE 150
#endif
// because we can't use inputs if it is manual testing
#if TESTING
    #define USE_SOCKET_CLIENT 0
#endif