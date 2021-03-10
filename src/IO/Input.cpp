#include "config/config.h"
#if USE_INPUT

#include "Input.h"
#include "IO.h"
#include "iostream"

Input::Input() {
	
}

Input::~Input() {
    
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
            eventNumber = strtol(line.c_str(), nullptr, 10);
        }
    }
}

int Input::getData() {
    // called by the interface
    std::lock_guard<std::mutex> lockGuard(mutex);
    int result = eventNumber;
    eventNumber = -1;
	return result;
}

bool Input::isNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

#endif