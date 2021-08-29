#include "config/config.h"

#if USE_GPIO == 1

#include "PwmOutput.h"
#include <iostream>
#include <utility>
#include <spdlog/spdlog.h>
#include <wiringSerial.h>

#if USE_WIRING_Pi == 1

#include <wiringPi.h>
#include <softPwm.h>

#endif

PwmOutput::PwmOutput(std::string name, const int pin, bool softPWM) : name(std::move(name)), pinNbr(pin),
                                                                      softPWM(softPWM)
{
    logger = spdlog::default_logger();

    SPDLOG_LOGGER_DEBUG(logger, "Created PwmOutput {}", name);

    if (!softPWM) {
#if USE_WIRING_Pi == 1
        pinMode(pinNbr, PWM_OUTPUT);
        pwmSetMode(PWM_MODE_MS);
        pwmSetRange(256);
        pwmSetClock(192);
#endif
    } else {
#if USE_ARDUINO_PROXY == 1
    if ((fd = serialOpen("/dev/ttyAMA0", 57600)) < 0) {
        SPDLOG_LOGGER_ERROR(logger, "Error while opening serial communication!");
        return;
    }
#endif
    }

}

bool PwmOutput::setValue(int value)
{
    if (currentState != value) {
        currentState = value;
        SPDLOG_LOGGER_INFO(logger, "PWM {} changed to {} on pin {}", name, currentState, pinNbr);

        if (!softPWM) {
#if USE_WIRING_Pi == 1
            pwmWrite(pinNbr, value);
#endif
        } else {
#if USE_ARDUINO_PROXY == 1
            // Send serial to proxy
            serialPutchar(fd, 162); // Verify byte
            serialPutchar(fd, pinNbr << 2);
            serialPutchar(fd, value);
#endif
        }

    }
    return true;
}

#endif