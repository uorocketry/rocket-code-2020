#pragma once

#include "config/config.h"


#if USE_GPIO == 1

    #define USE_PWM1 1

    #define USE_PWM2 1

    #define USE_OUT1 1

    #define EVENT_ENABLE_MASK 1

    #if USE_PWM1
        #define PWM1_NAME "Valve404"
        #define PWM1_PIN 12
        #define PWM1_OPEN 150
        #define PWM1_CLOSE 60
        #define PWM1_EVENT_ENABLE_MASK 0b100
        #define PWM1_SOFTPWM false
    #endif

    #if USE_PWM2
        #define PWM2_NAME "Valve505"
        #define PWM2_PIN 13
        #define PWM2_OPEN 150
        #define PWM2_CLOSE 6
        #define PWM2_EVENT_ENABLE_MASK 0b1000
        #define PWM2_SOFTPWM false
    #endif

    #if USE_OUT1
        #define OUT1_NAME "Valve606"
        #define OUT1_PIN 16
        #define OUT1_OPEN 1
        #define OUT1_CLOSE 0
        #define OUT1_EVENT_ENABLE_MASK 0b10
    #endif

#endif
