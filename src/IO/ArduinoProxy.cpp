#include "ArduinoProxy.h"

#if USE_ARDUINO_PROXY == 1

#include "IO/ArduinoEncoder.h"
#include <spdlog/spdlog.h>
#include <sys/poll.h>

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

    if ((fd = serialOpen("/dev/ttyAMA0", 57600)) < 0)
    {
        SPDLOG_LOGGER_ERROR(logger, "Error while opening serial communication!");
        return;
    }

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

#endif