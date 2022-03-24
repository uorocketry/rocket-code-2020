#pragma once

#include "cobs.h"
#include "helpers/Helper.h"
#include <memory>
#include <spdlog/spdlog.h>

class ArduinoEncoder
{
  public:
    template <typename T>
    static helper::SharedArray<char> encode(const T &dataOut);

    template <typename T>
    static T decode(const char *buffer, int length);
};

/**
 * Encode the Protobuf object to a byte array. The byte array will have COBS
 * applied to it, and INCLUDES the ending 0x0 byte, so it can be sent as is.
 */
template <typename T>
helper::SharedArray<char> ArduinoEncoder::encode(const T &dataOut)
{
    // Convert from Protobuf to byte array
    size_t protoSize = dataOut.ByteSizeLong();

    std::unique_ptr<char[]> protoData(new char[protoSize]);

    dataOut.SerializeToArray(&protoData[0], static_cast<int>(protoSize));

    // Apply COBS to byte array
    int cobsSize = static_cast<int>(protoSize) + 2;

    std::shared_ptr<char[]> cobsData(new char[cobsSize]);

    cobs_encode(&cobsData[0], cobsSize, &protoData[0], protoSize);
    cobsData[cobsSize - 1] = 0x0;

    return helper::SharedArray<char>{cobsData, static_cast<size_t>(cobsSize)};
}

/**
 * Decodes a byte array to a Protobuf object. DataIn should contain the ending
 * 0x0 byte.
 */
template <typename T>
T ArduinoEncoder::decode(const char *buffer, int length)
{
    if (length <= 2)
    {
        SPDLOG_WARN("Buffer length too small. Returning a default object");
        T protoObj;
        return protoObj;
    }

    // Remove COBS from data
    int dataLength = static_cast<int>(length) - 2;
    std::unique_ptr<char[]> data(new char[dataLength]);

    cobs_decode_result result = cobs_decode(&data[0], dataLength, buffer, length - 1);
    if (result.status != cobs_decode_status::COBS_DECODE_OK)
    {
        SPDLOG_WARN("Error decoding COBS: {}. Returning default object.", result.status);
        T protoObj;
        return protoObj;
    }

    // Parse Protobuf
    T protoObj;

    protoObj.ParseFromArray(&data[0], static_cast<int>(dataLength));

    return protoObj;
}
