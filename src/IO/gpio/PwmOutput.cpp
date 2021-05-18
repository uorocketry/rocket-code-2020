#include "config/config.h"
#if USE_GPIO == 1

#include "PwmOutput.h"
#include <iostream>
#include <spdlog/spdlog.h>

#if USE_WIRING_Pi == 1
#include <wiringPi.h>
#endif

PwmOutput::PwmOutput(const std::string& name, const int pin) : name(name), pinNbr(pin){
    logger = spdlog::default_logger();

    logger->debug("Created PwmOutput {}", name);

    #if USE_WIRING_Pi == 1
    pinMode (pinNbr, PWM_OUTPUT) ;
	pwmSetMode (PWM_MODE_MS);
	pwmSetRange (256);
	pwmSetClock (192);
    #endif
}

bool PwmOutput::setValue(int value) {
    if(currentState != value) {
        currentState = value;
        logger->debug("PWM {} changed to {}", name, currentState);

        #if USE_WIRING_Pi == 1
        pwmWrite(pinNbr, value);
        #endif
    }
    return true;
}

#endif