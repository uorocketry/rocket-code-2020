#include "config/config.h"
#if USE_GPIO

#include "IO/PwmOutput.h"
#include <iostream>
PwmOutput::PwmOutput(const std::string name, const int pin) : name(name), pinNbr(pin){
    std::cout << "created pwmOutput " << name << "\n";
}

bool PwmOutput::setValue(int value) {
    if(currentState != value) {
        currentState = value;
        std::cout << "PWM " << name << "changed to " << currentState << "\n";
    }
    return true;
};

#endif