#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <spdlog/spdlog.h>
#include <i2c/smbus.h>
#include "SMBus.h"

// For more details on using I2C see:
// https://www.kernel.org/doc/html/latest/i2c/dev-interface.html
// https://www.kernel.org/doc/Documentation/i2c/smbus-protocol

SMBus::SMBus(int address) : address(address) {
	file = open("/dev/i2c-1", O_RDWR);
	if (file < 0) {
		SPDLOG_ERROR("Error getting file handle for I2C: {}", strerror(errno));
	}

	if (ioctl(file, I2C_SLAVE, address) < 0) {
		SPDLOG_ERROR("Error opening I2C for address {}: {}", address, strerror(errno));
	}
}

int32_t SMBus::readByte(uint8_t reg) const {
	__s32 data = i2c_smbus_read_byte_data(file, reg);
	if (data < 0) {
		SPDLOG_ERROR("I2C read on device {}, register {} failed: {}", address, reg, strerror(errno));
	}

	return data;
}

void SMBus::writeByte(uint8_t reg, uint8_t data) {
	__s32 err = i2c_smbus_write_byte_data(file, reg, data);
	if (err < 0) {
		SPDLOG_ERROR("I2C write on device {}, register {} failed: {}", address, reg, strerror(errno));
	}
}
