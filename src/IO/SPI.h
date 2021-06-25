#ifndef SPI_H
#define SPI_H
#include <stdint.h>

static void pabort(const char* s);

class SPI
{
  private:
    int fd;
    const char* device;
    uint8_t mode;
    uint8_t bits;
    uint32_t speed;
    uint16_t delay;

  public:
    SPI(const char* device, uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay);
    void transfer(uint8_t tx[], uint8_t rx[], unsigned int len);
    void close_SPI();
    static void printBytesBuffer(uint8_t buffer[], int len);
};

#endif