#include "config/config.h"
#if USE_GPIO

#include "IO/PwmOutput.h"
#include <iostream>

#if USE_WIRING_Pi
#include <wiringPi.h>
#endif

PwmOutput::PwmOutput(const std::string name, const int pin) : name(name), pinNbr(pin){
    std::cout << "created pwmOutput " << name << "\n";
    
    #if USE_WIRING_Pi
    pinMode (pinNbr, PWM_OUTPUT) ;
	pwmSetMode (PWM_MODE_MS);
	pwmSetRange (256);
	pwmSetClock (192);
    #endif
}

bool PwmOutput::setValue(int value) {
    if(currentState != value) {
        currentState = value;
        std::cout << "PWM " << name << "changed to " << currentState << "\n";

        #if USE_WIRING_Pi
        pwmWrite(pinNbr, value);
        #endif
    }
    return true;
};

#endif