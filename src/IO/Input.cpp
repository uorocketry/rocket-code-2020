#include "config/config.h"
#if USE_INPUT == 1

#include "Input.h"
#include "IO.h"
#include "iostream"

Input::Input(EventQueue &eventQueue) : eventQueue(eventQueue)
{

}

Input::~Input() 
{
    
}

void Input::initialize() {
    std::cout << "init input thread" << "\n";
    IO::initialize();
}

bool Input::isInitialized() {
    return true;
}

void Input::run() {
    std::cout << "started input thread" << "\n";
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        if (isNumber(line)) {
            eventQueue.push(strtol(line.c_str(), nullptr, 10));
        }
    }
}

bool Input::isNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

#endif