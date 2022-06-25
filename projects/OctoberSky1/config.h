#pragma once

#include <uorocketry/mavlink.h>

// clang-format off

#define STATEMACHINE OctoberSkyStateMachine

constexpr mavlink_system_t MAVLINK_SYSTEM = {1, 1};

#ifndef TESTING
    #define TESTING 0
#endif

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
    #define USE_INPUT 0
#endif

#ifndef USE_RADIO
    #if TESTING == 1
        #define USE_RADIO 0
    #else
        #define USE_RADIO 1
    #endif
#endif

#ifndef SKIP_INIT
    #define SKIP_INIT 0
#endif

#ifndef USE_GPIO
    #define USE_GPIO 0
#endif

// because we can't use inputs if it is manual testing
#if TESTING == 1
    #define USE_SOCKET_CLIENT 0
#endif

// clang-format on