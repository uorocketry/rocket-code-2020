#pragma once

#include "config/config.h"


#if USE_GPIO

    #define USE_PWM1 1

    #define USE_PWM2 1

    #define USE_OUT1 1


    #if USE_PWM1
        #define PWM1_NAME "Valve404"
        #define PWM1_PIN 14
        #define PWM1_OPEN 180
        #define PWM1_CLOSE 0
    #endif

    #if USE_PWM2
        #define PWM2_NAME "Valve505"
        #define PWM2_PIN 14
        #define PWM2_OPEN 50
        #define PWM2_CLOSE 0
    #endif

    #if USE_OUT1
        #define OUT1_NAME "Valve606"
        #define OUT1_PIN 16
        #define OUT1_OPEN 1
        #define OUT1_CLOSE 0
    #endif

#endif
