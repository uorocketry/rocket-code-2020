#include "config/config.h"
#if USE_GPIO

#include "IO/Output.h"
#include <iostream>

Output::Output(const std::string name, const int pin) : name(name), pinNbr(pin){
    std::cout << "created Output " << name << "\n";
}

bool Output::setValue(int value) {
    this->value = value;
    std::cout << "Set value OUT to " << value << "\n";
    return true;
};

#endif