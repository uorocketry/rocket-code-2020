#include "config/config.h"
#if USE_GPIO

#include "IO/Output.h"
#include <iostream>

Output::Output(const std::string name, const int pin) : name(name), pinNbr(pin){
    std::cout << "created Output " << name << "\n";
}

bool Output::setValue(int value) {
    if(currentState != value) {
        currentState = value;
        std::cout << "OUT " << name << "changed to " << currentState << "\n";
    }
    return true;
};

#endif