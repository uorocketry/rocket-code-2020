#include "config/config.h"
#if USE_GPIO == 1

#include "./DigitalOutput.h"
#include <iostream>
#include <spdlog/spdlog.h>

#if USE_WIRING_Pi == 1
#include <wiringPi.h>
#endif

DigitalOutput::DigitalOutput(const std::string& name, const int pin) : name(name), pinNbr(pin){
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created Output {}", name);

    #if USE_WIRING_Pi == 1
    pinMode (pinNbr, OUTPUT);
    #endif
}

bool DigitalOutput::setValue(int value) {
    if(currentState != value) {
        currentState = value;
        SPDLOG_LOGGER_DEBUG(logger, "OUT {} changed to {}", name, currentState);

        #if USE_WIRING_Pi == 1
        digitalWrite(pinNbr, value);
        #endif
    }
    return true;
}

#endif