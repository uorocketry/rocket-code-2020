#include <spdlog/spdlog.h>
#include "config/config.h"
#if USE_INPUT == 1

#include "Input.h"
#include "IO.h"
#include "iostream"

Input::Input(EventQueue &eventQueue) : eventQueue(eventQueue)
{

}

Input::~Input() 
= default;

void Input::initialize() {
    SPDLOG_LOGGER_DEBUG(logger, "init input thread");
    IO::initialize();
}

bool Input::isInitialized() {
    return true;
}

void Input::run() {
    SPDLOG_LOGGER_DEBUG(logger, "started input thread");
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