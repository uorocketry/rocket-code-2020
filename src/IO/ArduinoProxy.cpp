#include "ArduinoProxy.h"
#include "IO/ArduinoEncoder.h"
#include "common/pch.h"

#include <sys/poll.h>

// If we haven't received a pin update in that duration, remove it from the map
const auto pinStateTimeout = std::chrono::seconds(5);

ArduinoProxy::ArduinoProxy() = default;

ArduinoProxy::~ArduinoProxy() = default;

ArduinoProxy *ArduinoProxy::getInstance()
{
    static ArduinoProxy instance;
    return &instance;
}

void ArduinoProxy::initialize()
{
    std::lock_guard<std::mutex> lockGuard(serialMutex);

    // Get the arduino serial port
    auto device = environment::getEnvOrDefault<std::string>("arduino-serial-device", "dev/ttyAMA0");
    if ((fd = serialOpen(device.c_str(), 57600)) < 0)
    {
        SPDLOG_ERROR("Error while opening serial communication!");
        return;
    }

    initialized = true;

    IO::initialize();
}

bool ArduinoProxy::isInitialized()
{
    return initialized;
}

void ArduinoProxy::run()
{
    std::vector<char> buffer;
    while (true)
    {
        struct pollfd pfds[1] = {fd, POLLIN};
        poll(pfds, 1, -1);

        while (serialDataAvail(fd) > 0)
        {
            char value = serialGetchar(fd);
            buffer.push_back(value);

            if (value == 0x0)
            {
                auto msg = ArduinoEncoder::decode<RocketryProto::ArduinoOut>(buffer.data(), buffer.size());

                handleArduinoMessage(msg);

                buffer.clear();
            }
        }
    }
}

void ArduinoProxy::handleArduinoMessage(const RocketryProto::ArduinoOut &arduinoOut)
{
    auto event = arduinoOut.eventmessage().type();
    auto eventData = arduinoOut.eventmessage().data();

    auto error = arduinoOut.errormessage().type();
    auto errorData = arduinoOut.errormessage().data();

    switch (arduinoOut.data_case())
    {
    case RocketryProto::ArduinoOut::kEventMessage:
        if (eventData != 0)
        {
            SPDLOG_INFO("Arduino Event: {} {}", RocketryProto::EventTypes_Name(event), eventData);
        }
        else
        {
            SPDLOG_INFO("Arduino Event: {}", RocketryProto::EventTypes_Name(event));
        }
        break;
    case RocketryProto::ArduinoOut::kErrorMessage:
        if (eventData != 0)
        {
            SPDLOG_WARN("Arduino Error: {} {}", RocketryProto::ErrorTypes_Name(error), errorData);
        }
        else
        {
            SPDLOG_WARN("Arduino Error: {}", RocketryProto::ErrorTypes_Name(error));
        }
        break;
    case RocketryProto::ArduinoOut::kServoState: {
        std::lock_guard<std::mutex> lockGuard(stateMutex);

        const auto &servoState = arduinoOut.servostate();
        servoStates[servoState.pin()] = {servoState.position(), std::chrono::steady_clock::now()};
    }
    break;
    case RocketryProto::ArduinoOut::kDigitalState: {
        std::lock_guard<std::mutex> lockGuard(stateMutex);

        const auto &digitalState = arduinoOut.digitalstate();
        digitalStates[digitalState.pin()] = {digitalState.activated(), std::chrono::steady_clock::now()};
    }
    break;
    case RocketryProto::ArduinoOut::DATA_NOT_SET:
        SPDLOG_WARN("Data field not set in Arduino message. ");
        break;
    }
}

void ArduinoProxy::send(const RocketryProto::ArduinoIn &data)
{
    if (initialized)
    {
        std::lock_guard<std::mutex> lockGuard(serialMutex);

        std::shared_ptr<std::vector<char>> encodedData = ArduinoEncoder::encode(data);

        serialPutchar(fd, 0);
        for (int i = 0; i < encodedData->size(); i++)
        {
            serialPutchar(fd, encodedData->at(i));
        }
    }
}

/**
 * Returns the state of the pin. If we don't know the state, throws a std::out_of_range.
 */
bool ArduinoProxy::getDigitalState(int pin)
{
    std::lock_guard<std::mutex> lockGuard(stateMutex);

    auto state = digitalStates.at(pin);
    auto now = std::chrono::steady_clock::now();

    if (now - state.second >= pinStateTimeout)
    {
        digitalStates.erase(pin);
        SPDLOG_ERROR("Arduino stopped reporting digital pin {}", pin);
        throw std::out_of_range("Pin has been removed");
    }
    else
    {
        return state.first;
    }
}

/**
 * Returns the state of the pin. If we don't know the state, throws a std::out_of_range.
 */
int ArduinoProxy::getServoState(int pin)
{
    std::lock_guard<std::mutex> lockGuard(stateMutex);

    auto state = servoStates.at(pin);
    auto now = std::chrono::steady_clock::now();

    if (now - state.second >= pinStateTimeout)
    {
        servoStates.erase(pin);
        SPDLOG_ERROR("Arduino stopped reporting servo pin {}", pin);
        throw std::out_of_range("Pin has been removed");
    }
    else
    {
        return state.first;
    }
}