#pragma once

// clang-format off

#include "config.h"

#if USE_GPIO == 1

    #define USE_VENT 1

    #define USE_IGNITER 1

    #define USE_PWM_MAIN 1

    #define USE_PWM_PINHOLE 1

    #define USE_PWM_FILL 1

    #define USE_HEATER 1

    #define EVENT_ENABLE_MASK 0b1

    #if USE_VENT
        #define VENT_NAME "VENT"
        #define VENT_PIN 13
        #define VENT_OPEN 1
        #define VENT_CLOSE 0
        #define VENT_SAFE 1
        #define VENT_EVENT_ENABLE_MASK 0b10
    #endif

    #if USE_IGNITER
        #define IGNITER_NAME "IGNITER"
        #define IGNITER_PIN 12
        #define IGNITER_ON 1
        #define IGNITER_OFF 0
        #define IGNITER_EVENT_ENABLE_MASK 0b100
    #endif

    #if USE_PWM_MAIN
        #define MAIN_NAME "MAIN"
        #define MAIN_PIN 3
        #define MAIN_OPEN 180
        #define MAIN_IGNITION 0
        #define MAIN_IGNITION_BURN 50 // TODO: Correct value?
        #define MAIN_CLOSE 0
        #define MAIN_SAFE 180
        #define MAIN_EVENT_ENABLE_MASK 0b1000
        #define MAIN_SOFTPWM true
    #endif

    #if USE_PWM_PINHOLE
        #define PINHOLE_NAME "PINHOLE"
        #define PINHOLE_PIN 5
        #define PINHOLE_OPEN 180
        #define PINHOLE_CLOSE 0
        #define PINHOLE_SAFE 180
        #define PINHOLE_EVENT_ENABLE_MASK 0b10000
        #define PINHOLE_SOFTPWM true
    #endif

    #if USE_PWM_FILL
        #define FILL_NAME "FILL"
        #define FILL_PIN 6
        #define FILL_OPEN 180
        #define FILL_CLOSE 0
        #define FILL_SAFE 180
        #define FILL_EVENT_ENABLE_MASK 0b100000
        #define FILL_SOFTPWM true
    #endif

    #if USE_HEATER
        #define HEATER_NAME "HEATER"
        #define HEATER_PIN 7
        #define HEATER_ON 1
        #define HEATER_OFF 0
        #define HEATER_SAFE 0
    #endif
#endif

// clang-format on
