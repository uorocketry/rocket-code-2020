#pragma once

#include <cstdint>
#include <utility>

class SMBusError : public std::runtime_error
{
public:
    explicit SMBusError(const std::string &str) : std::runtime_error(str)
    {}
};

class SMBus
{
public:
    explicit SMBus(int address);

    int32_t readByte(uint8_t reg) const;

    void writeByte(uint8_t reg, uint8_t data);

private:
    const int address;

    int file;
};