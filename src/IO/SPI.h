#ifndef SPI_H
#define SPI_H
#include <cstdint>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <stdexcept>

class SPIError : public std::runtime_error
{
  public:
    explicit SPIError(const std::string &str) : std::runtime_error(str)
    {
    }
};

class SPI
{
  private:
    int fd;
    const char *device;
    uint8_t bits;
    uint32_t speed;

  public:
    SPI(const char *device, uint8_t mode, uint8_t bitsPerWord, uint32_t speed, bool lsbFirst);
    ~SPI();

    void write(uint8_t *buffer, size_t len) const;
    void write_then_read(const uint8_t *write_buffer, size_t write_len, uint8_t *read_buffer, size_t read_len,
                         uint8_t sendvalue = 0xFF) const;
};

#endif