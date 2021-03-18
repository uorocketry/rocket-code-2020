#include "config/config.h"
#if USE_GPIO

#include "IO/PwmOutput.h"
#include <iostream>
PwmOutput::PwmOutput(const std::string name, const int pin) : name(name), pinNbr(pin){
    std::cout << "created pwmOutput " << name << "\n";
}

bool PwmOutput::setValue(int value) {
    this->value = value;
    std::cout << "Set value to " << value << "\n";
    return true;
};

#endif