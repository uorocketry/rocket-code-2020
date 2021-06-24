#pragma once

#include <cstdint>

class SMBus {
public:
	explicit SMBus(int address);

	int32_t readByte(uint8_t reg) const;

	void writeByte(uint8_t reg, uint8_t data);

private:
	const int address;

	int file;
};