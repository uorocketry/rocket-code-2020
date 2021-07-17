#pragma once

#include <cstdint>
#include <utility>
#include <string>
#include <stdexcept>

class SMBusError : public std::runtime_error
{
public:
    explicit SMBusError(const std::string &str) : std::runtime_error(str) {}
};

class SMBus
{
public:
    explicit SMBus(int address);
    ~SMBus();

    int32_t readByte(uint8_t reg) const;
    int32_t readByte() const;

    void writeByte(uint8_t reg, uint8_t data) const;
    void writeByte(uint8_t data) const;

private:
    const int address;

    int file;
};