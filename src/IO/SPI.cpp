#include "SPI.h"
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

/**
 *
 * @param device Path to the SPI device
 * @param mode SPI mode. Use the constants SPI_MODE_0..SPI_MODE_3
 * @param bitsPerWord Number of bits contained per spi word. Usually set to 8
 * @param speed SPI speed in Hz
 * @param lsbFirst Whether the LSB should be first or the MSB
 */
SPI::SPI(const char *device, uint8_t mode, uint8_t bitsPerWord, uint32_t speed, bool lsbFirst)
    : device(device), bits(bitsPerWord), speed(speed)
{
#if DESKTOP_COMPAT != 1
    int ret = 0;

    fd = open(device, O_RDWR);
    if (fd < 0)
    {
        throw SPIError("Can't open device" + std::string(device));
    }

    /*
     * spi mode
     */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
    {
        throw SPIError("Can't set spi write mode to " + std::to_string(mode));
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
    {
        throw SPIError("Can't set spi read mode to " + std::to_string(mode));
    }

    /*
     * lsb
     */
    ret = ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsbFirst);
    if (ret == -1)
    {
        throw SPIError("Can't set spi write lsb to " + std::to_string(lsbFirst));
    }

    ret = ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsbFirst);
    if (ret == -1)
    {
        throw SPIError("Can't set spi write lsb to " + std::to_string(lsbFirst));
    }

    /*
     * bits per word
     */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord);
    if (ret == -1)
    {
        throw SPIError("Can't set read bits per word tp " + std::to_string(bitsPerWord));
    }

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bitsPerWord);
    if (ret == -1)
    {
        throw SPIError("Can't set write bits per word tp " + std::to_string(bitsPerWord));
    }

    /*
     * max speed hz
     */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {
        throw SPIError("Can't set max write speed hz to " + std::to_string(speed));
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {
        throw SPIError("Can't set max read speed hz to " + std::to_string(speed));
    }
#endif
}

SPI::~SPI()
{
#if DESKTOP_COMPAT != 1
    close(fd);
#endif
}

/*!
 *    @brief  Write a buffer or two to the SPI device.
 *    @param  buffer Pointer to buffer of data to write
 *    @param  len Number of bytes from buffer to write
 *    @param  prefix_buffer Pointer to optional array of data to write before
 * buffer.
 *    @param  prefix_len Number of bytes from prefix buffer to write
 *    @return
 */
void SPI::write(uint8_t *buffer, size_t len) const
{
#if DESKTOP_COMPAT != 1
    auto status = ::write(fd, buffer, len);
    if (status < 0)
    {
        throw SPIError("Error writing to SPI device");
    }
#endif
}

/*!
 *    @brief  Write some data, then read some data from SPI into another buffer.
 * The buffers can point to same/overlapping locations. This does not
 * transmit-receive at the same time!
 *    @param  write_buffer Pointer to buffer of data to write from
 *    @param  write_len Number of bytes from buffer to write.
 *    @param  read_buffer Pointer to buffer of data to read into.
 *    @param  read_len Number of bytes from buffer to read.
 *    @param  sendvalue The 8-bits of data to write when doing the data read,
 * defaults to 0xFF
 *    @return Always returns true because there's no way to test success of SPI
 * writes
 */
void SPI::write_then_read(const uint8_t *write_buffer, size_t write_len, uint8_t *read_buffer, size_t read_len,
                          uint8_t sendvalue) const
{
#if DESKTOP_COMPAT != 1
    struct spi_ioc_transfer xfer[2];

    memset(xfer, 0, sizeof xfer);
    memset(read_buffer, 0, read_len);

    xfer[0].tx_buf = (unsigned long)write_buffer;
    xfer[0].len = write_len;

    xfer[1].rx_buf = (unsigned long)read_buffer;
    xfer[1].len = read_len;

    int status = ioctl(fd, SPI_IOC_MESSAGE(2), xfer);
    if (status < 0)
    {
        throw SPIError("Error reading to SPI device");
    }
#endif
}
