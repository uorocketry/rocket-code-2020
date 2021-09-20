#include "ArduinoProxy.h"

#if USE_ARDUINO_PROXY == 1

#include <spdlog/spdlog.h>
#include "IO/GroundStationEncoder.h"

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

void ArduinoProxy::send(RocketryProto::ArduinoIn data) {
    if (inititialized) {
        std::lock_guard<std::mutex> lockGuard(serialMutex);

        helper::SharedArray<char> encodedData = GroundStationEncoder::encode(data);

        serialPutchar(fd, 0);
        for (int i = 0; i < encodedData.length; i++) {
            serialPutchar(fd, encodedData.data[i]);
        }
    }
}

#endif