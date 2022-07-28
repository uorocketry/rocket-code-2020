#include "ArduinoProxy.h"

#if USE_ARDUINO_PROXY == 1

#include "IO/ArduinoEncoder.h"
#include <spdlog/spdlog.h>
#include <sys/poll.h>
#include <thread>

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

    #if DESKTOP_COMPAT == 1
    if ((fd = serialOpen("/dev/ttyACM0", 57600)) < 0)
    #else
    if ((fd = serialOpen("/dev/ttyAMA0", 57600)) < 0)
    #endif
    {
        SPDLOG_LOGGER_ERROR(logger, "Error while opening serial communication!");
        return;
    }

    #if DESKTOP_COMPAT == 1
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    #endif

    inititialized = true;

    IO::initialize();
}

bool ArduinoProxy::isInitialized()
{
    return inititialized;
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
            SPDLOG_LOGGER_INFO(logger, "Arduino Event: {} {}", RocketryProto::EventTypes_Name(event), eventData);
        }
        else
        {
            SPDLOG_LOGGER_INFO(logger, "Arduino Event: {}", RocketryProto::EventTypes_Name(event));
        }
        break;
    case RocketryProto::ArduinoOut::kErrorMessage:
        if (eventData != 0)
        {
            SPDLOG_LOGGER_WARN(logger, "Arduino Error: {} {}", RocketryProto::ErrorTypes_Name(error), errorData);
        }
        else
        {
            SPDLOG_LOGGER_WARN(logger, "Arduino Error: {}", RocketryProto::ErrorTypes_Name(error));
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
    case RocketryProto::ArduinoOut::kDcMotorState: {
        std::lock_guard<std::mutex> lockGuard(stateMutex);

        const auto &dcMotorState = arduinoOut.dcmotorstate();
        dcMotorStates[{dcMotorState.motorforwardpin(), dcMotorState.motorreversepin()}] = {dcMotorState.position(), dcMotorState.direction(), dcMotorState.minlimitswitch(), dcMotorState.maxlimitswitch(), std::chrono::steady_clock::now()};
    }
    break;
    case RocketryProto::ArduinoOut::DATA_NOT_SET:
        SPDLOG_LOGGER_WARN(logger, "Data field not set in Arduino message. ");
        break;
    }
}

void ArduinoProxy::send(const RocketryProto::ArduinoIn &data)
{
    if (inititialized)
    {
        std::lock_guard<std::mutex> lockGuard(serialMutex);

        helper::SharedArray<char> encodedData = ArduinoEncoder::encode(data);

        serialPutchar(fd, 0);
        for (int i = 0; i < encodedData.length; i++)
        {
            serialPutchar(fd, encodedData.data[i]);
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

DCMotorState ArduinoProxy::getDCMotorState(int forwardPin, int reversePin)
{
    std::lock_guard<std::mutex> lockGuard(stateMutex);

    auto state = dcMotorStates.at({forwardPin, reversePin});
    auto now = std::chrono::steady_clock::now();

    if (now - state.time >= pinStateTimeout)
    {
        dcMotorStates.erase({forwardPin, reversePin});
        SPDLOG_ERROR("Arduino stopped reporting DC motor pin {} and {}", forwardPin, reversePin);
        throw std::out_of_range("Pin has been removed");
    }
    else
    {
        return state;
    }
}

#endif