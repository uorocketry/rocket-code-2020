#pragma once

#include <memory>
#include "cobs.h"
#include "helpers/Helper.h"

class ArduinoEncoder {
public:
	template<typename T>
	static helper::SharedArray<char> encode(const T &dataOut);

	template<typename T>
	static T decode(const helper::SharedArray<char> &dataIn);
};


/**
 * Encode the Protobuf object to a byte array. The byte array will have COBS applied to it, and INCLUDES the ending
 * 0x0 byte, so it can be sent as is.
 */
template<typename T>
helper::SharedArray<char> ArduinoEncoder::encode(const T &dataOut) {
	// Convert from Protobuf to byte array
	size_t protoSize = dataOut.ByteSizeLong();

	std::unique_ptr<char[]> protoData(new char[protoSize]);

	dataOut.SerializeToArray(&protoData[0], static_cast<int>(protoSize));

	// Apply COBS to byte array
	int cobsSize = static_cast<int>(protoSize) + 2;

	std::shared_ptr<char[]> cobsData(new char[cobsSize]);

	cobs_encode(&cobsData[0], cobsSize, &protoData[0], protoSize);
	cobsData[cobsSize-1] = 0x0;

	return helper::SharedArray<char>{cobsData, static_cast<size_t>(cobsSize)};
}

/**
 * Decodes a byte array to a Protobuf object. DataIn should contain the ending 0x0 byte.
 */
template<typename T>
T ArduinoEncoder::decode(const helper::SharedArray<char> &dataIn) {
	// Remove COBS from data
	int dataLength = static_cast<int>(dataIn.length) - 2;
	std::unique_ptr<char[]> data(new char[dataLength]);

	cobs_decode_result cobsLength = cobs_decode(&data[0], dataLength, &dataIn.data[0], dataIn.length - 1);

	// Parse Protobuf
	T protoObj;

	protoObj.ParseFromArray(&data[0], static_cast<int>(dataLength));

	return protoObj;
}
