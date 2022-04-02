#pragma once

// Adapted from https://github.com/adafruit/Adafruit_MAX31865

/***************************************************
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865
  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328
  This sensor uses SPI to communicate, 4 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <IO/SPI.h>
#include <cstdint>

/*! Interface class for the MAX31865 RTD Sensor reader */
class MAX31865
{
  public:
    enum class NumWires
    {
        _2WIRE = 0,
        _3WIRE = 1,
        _4WIRE = 0
    };

    MAX31865(const char *str);

    bool begin(NumWires = NumWires::_2WIRE);

    uint8_t readFault(void);
    void clearFault(void);
    uint16_t readRTD();

    void setWires(NumWires wires);
    void autoConvert(bool b);
    void enable50Hz(bool b);
    void enableBias(bool b);

    float temperature(float RTDnominal, float refResistor);

  private:
    enum Config
    {
        Config_Bias = 0x80,
        Config_ModeAuto = 0x40,
        Config_ModeOff = 0x00,
        Config_1Shot = 0x20,
        Config_3Wire = 0x10,
        Config_24Wire = 0x00,
        Config_FaultStat = 0x02,
        Config_Filt50HZ = 0x01,
        Config_Filt60HZ = 0x00
    };

    enum Register
    {
        Register_Config = 0x00,
        Register_RtdMSB = 0x01,
        Register_RtdLSB = 0x02,
        Register_HFaultMSB = 0x03,
        Register_HFaultLSB = 0x04,
        Register_LFaultMSB = 0x05,
        Register_LFaultLSB = 0x06,
        Register_FaultStat = 0x07
    };

    enum Fault
    {
        Fault_HighThresh = 0x80,
        Fault_LowThresh = 0x40,
        Fault_RefInLow = 0x20,
        Fault_RefInHigh = 0x10,
        Fault_RtdInLow = 0x08,
        Fault_Ovuv = 0x04,
    };

    SPI spi_dev;

    void readRegisterN(uint8_t addr, uint8_t buffer[], uint8_t n);

    uint8_t readRegister8(uint8_t addr);
    uint16_t readRegister16(uint8_t addr);

    void writeRegister8(uint8_t addr, uint8_t reg);

    const float RTD_A = 3.9083e-3;
    const float RTD_B = -5.775e-7;
};
