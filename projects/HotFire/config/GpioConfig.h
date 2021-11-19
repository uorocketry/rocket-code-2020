#pragma once

// clang-format off

#include "config/config.h"

#if USE_GPIO == 1

    #define USE_VENT 1

    #define USE_PWM_MAIN 1

    #define USE_PWM_PINHOLE 1

    #define USE_PWM_FILL 1

    #define EVENT_ENABLE_MASK 0b1

    #if USE_VENT
        #define VENT_NAME "VENT"
        #define VENT_PIN 7
        #define VENT_OPEN 1
        #define VENT_CLOSE 0
        #define VENT_SAFE 1
        #define VENT_EVENT_ENABLE_MASK 0b10
    #endif

    #if USE_PWM_MAIN
        #define MAIN_NAME "MAIN"
        #define MAIN_PIN 9
        #define MAIN_OPEN 180
        #define MAIN_IGNITION 54
        #define MAIN_CLOSE 0
        #define MAIN_SAFE 180
        #define MAIN_EVENT_ENABLE_MASK 0b1000
        #define MAIN_SOFTPWM true
    #endif

    #if USE_PWM_PINHOLE
        #define PINHOLE_NAME "PINHOLE"
        #define PINHOLE_PIN 5
        #define PINHOLE_OPEN 0
        #define PINHOLE_CLOSE 180
        #define PINHOLE_SAFE 0
        #define PINHOLE_EVENT_ENABLE_MASK 0b10000
        #define PINHOLE_SOFTPWM true
    #endif

    #if USE_PWM_FILL
        #define FILL_NAME "FILL"
        #define FILL_PIN 11
        #define FILL_OPEN 180
        #define FILL_CLOSE 0
        #define FILL_SAFE 180
        #define FILL_EVENT_ENABLE_MASK 0b100000
        #define FILL_SOFTPWM true
    #endif
#endif

// clang-format on
