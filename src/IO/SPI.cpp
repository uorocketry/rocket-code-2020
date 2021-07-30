#include "SPI.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

SPI::SPI(const char* device, uint8_t mode, uint8_t bits, uint32_t speed, uint16_t delay) : bits(bits), speed(speed), delay(delay)
{
	int ret = 0;
	
	fd = open(device, O_RDWR);
	if (fd < 0) {
        throw SPIError("Can't open device" + std::string(device));
    }

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1) {
		throw SPIError("Can't set spi write mode to " + std::to_string(mode));
	}

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1) {
        throw SPIError("Can't set spi read mode to " + std::to_string(mode));
    }

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1) {
        throw SPIError("Can't set read bits per word tp " + std::to_string(bits));
    }

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1) {
        throw SPIError("Can't set write bits per word tp " + std::to_string(bits));
    }

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1) {
        throw SPIError("Can't set max write speed hz to " + std::to_string(speed));
    }

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
        throw SPIError("Can't set max read speed hz to " + std::to_string(speed));
    }
}

SPI::~SPI()
{
    close(fd);
}

void SPI::transfer(uint8_t tx[], uint8_t rx[], unsigned int len)
{
	int ret;
	
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = len,
		.speed_hz = speed,
		.delay_usecs = delay,
		.bits_per_word = bits,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1) {
        throw SPIError("can't send spi message");
    }
}
