#include "config/config.h"
#if USE_GPIO

#include "IO/Output.h"
#include <iostream>

#if USE_WIRING_Pi
#include <wiringPi.h>
#endif

Output::Output(const std::string name, const int pin) : name(name), pinNbr(pin){
    std::cout << "created Output " << name << "\n";
    
    #if USE_WIRING_Pi
    pinMode (pinNbr, OUTPUT);
    #endif

}

bool Output::setValue(int value) {
    if(currentState != value) {
        currentState = value;
        std::cout << "OUT " << name << "changed to " << currentState << "\n";

        #if USE_WIRING_Pi
        digitalWrite(pinNbr, value);
        #endif
    };
    return true;
};

#endif