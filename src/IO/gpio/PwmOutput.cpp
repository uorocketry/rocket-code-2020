#include "config/config.h"

#if USE_GPIO == 1

#include "PwmOutput.h"
#include <iostream>
#include <utility>
#include <spdlog/spdlog.h>

#if USE_WIRING_Pi == 1

#include <wiringPi.h>
#include <softPwm.h>

#endif

PwmOutput::PwmOutput(std::string name, const int pin, bool softPWM) : name(std::move(name)), pinNbr(pin),
                                                                      softPWM(softPWM)
{
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created PwmOutput {}", name);

#if USE_WIRING_Pi == 1
    if (!softPWM) {
        pinMode(pinNbr, PWM_OUTPUT);
        pwmSetMode(PWM_MODE_MS);
        pwmSetRange(256);
        pwmSetClock(192);
    } else {
        int status = softPwmCreate(pinNbr, 0, 100);
        if (status == 0) {
            SPDLOG_LOGGER_ERROR(logger, "Error while creating software PWM output: {}", errno);
        }
    }
#endif
}

bool PwmOutput::setValue(int value)
{
    if (currentState != value) {
        currentState = value;
        SPDLOG_LOGGER_DEBUG(logger, "PWM {} changed to {}", name, currentState);

#if USE_WIRING_Pi == 1
        if (!softPWM) {
            pwmWrite(pinNbr, value);
        } else {
            softPwmWrite(pinNbr, value);
        }
#endif
    }
    return true;
}

#endif