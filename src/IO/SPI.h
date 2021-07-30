#ifndef SPI_H
#define SPI_H
#include <stdint.h>
#include <stdexcept>

class SPIError : public std::runtime_error
{
public:
    explicit SPIError(const std::string &str) : std::runtime_error(str) {}
};

class SPI
{
  private:
    int fd;
    const char* device;
    uint8_t bits;
    uint32_t speed;
    uint16_t delay;

  public:
    SPI(const char* device, uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay);
    ~SPI();
    void transfer(uint8_t tx[], uint8_t rx[], unsigned int len);
};

#endif