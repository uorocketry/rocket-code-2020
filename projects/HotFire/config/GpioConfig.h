#pragma once

#include "config/config.h"


#ifdef USE_GPIO

    #define USE_PWM1 1

    #define USE_PWM2 1


    #ifdef USE_PWM1
        #define PWM1_PIN 14
        #define PWM1_OPEN 180
        #define PWM1_CLOSE 0
    #endif

    #ifdef USE_PWM2
        #define PWM2_PIN 14
        #define PWM2_OPEN 180
        #define PWM2_CLOSE 0
    #endif

#endif
