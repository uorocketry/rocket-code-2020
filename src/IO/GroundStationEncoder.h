#pragma once

#include "cobs.h"
#include "helpers/Helper.h"
#include <memory>

namespace GroundStationEncoder
{

/**
 * Encode the Protobuf object to a byte array.
 */
template <typename T>
helper::SharedArray<char> encode(const T &dataOut)
{
    // Convert from Protobuf to byte array
    size_t protoSize = dataOut.ByteSizeLong();

    std::shared_ptr<char[]> protoData(new char[protoSize]);

    dataOut.SerializeToArray(&protoData[0], static_cast<int>(protoSize));

    return helper::SharedArray<char>{protoData, static_cast<size_t>(protoSize)};
}

/**
 * Decodes a byte array to a Protobuf object.
 */
template <typename T>
T decode(const void *buffer, size_t length)
{
    // Parse Protobuf
    T protoObj;

    protoObj.ParseFromArray(buffer, length);

    return std::move(protoObj);
}

} // namespace GroundStationEncoder