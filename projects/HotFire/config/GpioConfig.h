#pragma once

// clang-format off

#include "config/config.h"

#if USE_GPIO == 1

    #define USE_SOLENOID 1

    #define USE_PWM_MANIFOLD 1

    #define USE_PWM_FILL 1

    #define USE_PWM_VENT 1

    #define EVENT_ENABLE_MASK 0b1

    #if USE_SOLENOID
        #define SOLENOID_NAME "SOLENOID"
        #define SOLENOID_PIN 7
        #define SOLENOID_OPEN 1
        #define SOLENOID_CLOSE 0
        #define SOLENOID_SAFE 1
        #define SOLENOID_EVENT_ENABLE_MASK 0b10
    #endif

    #if USE_PWM_MANIFOLD
        #define MANIFOLD_NAME "MANIFOLD"
        #define MANIFOLD_PIN 5
        #define MANIFOLD_OPEN 180
        #define MANIFOLD_IGNITION 54
        #define MANIFOLD_CLOSE 0
        #define MANIFOLD_SAFE 180
        #define MANIFOLD_EVENT_ENABLE_MASK 0b1000
        #define MANIFOLD_SOFTPWM true
    #endif

    #if USE_PWM_FILL
        #define FILL_NAME "FILL"
        #define FILL_PIN 5
        #define FILL_OPEN 180
        #define FILL_CLOSE 0
        #define FILL_SAFE 180
        #define FILL_EVENT_ENABLE_MASK 0b10000
        #define FILL_SOFTPWM true
    #endif

    #if USE_PWM_VENT
        #define VENT_NAME "VENT"
        #define VENT_PIN 11
        #define VENT_OPEN 180
        #define VENT_CLOSE 0
        #define VENT_SAFE 180
        #define VENT_EVENT_ENABLE_MASK 0b100000
        #define VENT_SOFTPWM true
    #endif
#endif

// clang-format on
