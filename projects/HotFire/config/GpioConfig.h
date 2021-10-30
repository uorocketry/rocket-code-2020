#pragma once

// clang-format off

#include "config/config.h"

#if USE_GPIO == 1

    #define USE_SV01 1

    #define USE_SV02 1

    #define USE_PWM_SBV01 1

    #define USE_PWM_SBV02 1

    #define USE_PWM_SBV03 1

    #define EVENT_ENABLE_MASK 0b1

    #if USE_SV01
        #define SV01_NAME "SV-01"
        #define SV01_PIN 7
        #define SV01_OPEN 1
        #define SV01_CLOSE 0
        #define SV01_SAFE 1
        #define SV01_EVENT_ENABLE_MASK 0b10
    #endif

    #if USE_SV02
        #define SV02_NAME "SV-02"
        #define SV02_PIN 8
        #define SV02_OPEN 1
        #define SV02_CLOSE 0
        #define SV02_SAFE 1
        #define SV02_EVENT_ENABLE_MASK 0b100
    #endif

    #if USE_PWM_SBV01
        #define SBV01_NAME "SBV01"
        #define SBV01_PIN 9
        #define SBV01_OPEN 180
        #define SBV01_IGNITION 54
        #define SBV01_CLOSE 0
        #define SBV01_SAFE 180
        #define SBV01_EVENT_ENABLE_MASK 0b1000
        #define SBV01_SOFTPWM true
    #endif

    #if USE_PWM_SBV02
        #define SBV02_NAME "SBV02"
        #define SBV02_PIN 5
        #define SBV02_OPEN 0
        #define SBV02_CLOSE 180
        #define SBV02_SAFE 0
        #define SBV02_EVENT_ENABLE_MASK 0b10000
        #define SBV02_SOFTPWM true
    #endif

    #if USE_PWM_SBV03
        #define SBV03_NAME "SBV03"
        #define SBV03_PIN 11
        #define SBV03_OPEN 180
        #define SBV03_CLOSE 0
        #define SBV03_SAFE 180
        #define SBV03_EVENT_ENABLE_MASK 0b100000
        #define SBV03_SOFTPWM true
    #endif
#endif

// clang-format on
