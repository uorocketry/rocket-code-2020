#include "config/config.h"
#if USE_GPIO == 1

#include "IO/Output.h"
#include <iostream>

#if USE_WIRING_Pi == 1
#include <wiringPi.h>
#endif

Output::Output(const std::string& name, const int pin) : name(name), pinNbr(pin){
    std::cout << "created Output " << name << "\n";
    
    #if USE_WIRING_Pi == 1
    pinMode (pinNbr, OUTPUT);
    #endif

}

bool Output::setValue(int value) {
    if(currentState != value) {
        currentState = value;
        std::cout << "OUT " << name << "changed to " << currentState << "\n";

        #if USE_WIRING_Pi == 1
        digitalWrite(pinNbr, value);
        #endif
    }
    return true;
}

#endif