//Orignal Author: Nathan Seidle
/*
 MPL3115A2 Barometric Pressure Sensor Library
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 24th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 Get pressure, altitude and temperature from the MPL3115A2 sensor.

 Updated by PaulZC: October 19th, 2019
 */

//Porting Code to Raspberry pi 4 with WiringPi
//I'll learn to fork later

#ifndef _SPARKFUN_MPL3115A2_H_
#define _SPARKFUN_MPL3115A2_H_

#define MPL3115A2_ADDRESS 0x60 // Unshifted 7-bit I2C address for sensor

// Define MPL3115A2 registers
enum mpl3115a2_regs
{
	STATUS     = 0x00,
	OUT_P_MSB  = 0x01,
	OUT_P_CSB  = 0x02,
	OUT_P_LSB  = 0x03,
	OUT_T_MSB  = 0x04,
	OUT_T_LSB  = 0x05,
	DR_STATUS  = 0x06,
	OUT_P_DELTA_MSB  = 0x07,
	OUT_P_DELTA_CSB  = 0x08,
	OUT_P_DELTA_LSB  = 0x09,
	OUT_T_DELTA_MSB  = 0x0A,
	OUT_T_DELTA_LSB  = 0x0B,
	WHO_AM_I   = 0x0C,
	F_STATUS   = 0x0D,
	F_DATA     = 0x0E,
	F_SETUP    = 0x0F,
	TIME_DLY   = 0x10,
	SYSMOD     = 0x11,
	INT_SOURCE = 0x12,
	PT_DATA_CFG = 0x13,
	BAR_IN_MSB = 0x14,
	BAR_IN_LSB = 0x15,
	P_TGT_MSB  = 0x16,
	P_TGT_LSB  = 0x17,
	T_TGT      = 0x18,
	P_WND_MSB  = 0x19,
	P_WND_LSB  = 0x1A,
	T_WND      = 0x1B,
	P_MIN_MSB  = 0x1C,
	P_MIN_CSB  = 0x1D,
	P_MIN_LSB  = 0x1E,
	T_MIN_MSB  = 0x1F,
	T_MIN_LSB  = 0x20,
	P_MAX_MSB  = 0x21,
	P_MAX_CSB  = 0x22,
	P_MAX_LSB  = 0x23,
	T_MAX_MSB  = 0x24,
	T_MAX_LSB  = 0x25,
	CTRL_REG1  = 0x26,
	CTRL_REG2  = 0x27,
	CTRL_REG3  = 0x28,
	CTRL_REG4  = 0x29,
	CTRL_REG5  = 0x2A,
	OFF_P      = 0x2B,
	OFF_T      = 0x2C,
	OFF_H      = 0x2D
};

class MPL3115A2 {

public:
  MPL3115A2();

  //Public Functions
  float readAltitude(); // Returns float with meters above sealevel. Ex: 1638.94
  float readTemp(); // Returns float with current temperature in Celsius. Ex: 23.37

  private:
  //Private Functions
  void toggleOneShot();

  //Private Variables
  uint8_t _I2Caddress = MPL3115A2_ADDRESS;  //Default 7-bit unshifted address of the MPL3115A2

};

#endif // End include guard
