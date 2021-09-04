#include "ArduinoProxy.h"

#if USE_ARDUINO_PROXY == 1

#include <spdlog/spdlog.h>

ArduinoProxy::ArduinoProxy() {
    createThread = false;
}

ArduinoProxy::~ArduinoProxy() { 

}

ArduinoProxy* ArduinoProxy::getInstance() {
    static ArduinoProxy instance;
    return &instance;
}

void ArduinoProxy::initialize() {
    SPDLOG_LOGGER_INFO(logger, "Initializing Arduino Proxy...");
    IO::initialize();

    std::lock_guard<std::mutex> lockGuard(serialMutex);

    if ((fd = serialOpen("/dev/ttyAMA0", 57600)) < 0) {
        SPDLOG_LOGGER_ERROR(logger, "Error while opening serial communication!");
        return;
    }

    inititialized = true;
}

bool ArduinoProxy::isInitialized() {
    return inititialized;
}

void ArduinoProxy::run() {

}

void ArduinoProxy::send(unsigned char c) {
    if (inititialized) {
        std::lock_guard<std::mutex> lockGuard(serialMutex);
        serialPutchar(fd, c);
    }
}

#endif