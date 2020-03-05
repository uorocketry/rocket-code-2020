//Orignal Author: Nathan Seidle
//Port to Raspberry pi 4: jonl40
/*
 MPL3115A2 Barometric Pressure Sensor Library
 SparkFun Electronics
 Date: September 22nd, 2013

 If you have feature suggestions or need support please use the github support page: https://github.com/sparkfun/MPL3115A2_Breakout
 Hardware Setup: The MPL3115A2 lives on the I2C bus. Attach the SDA pin to A4, SCL to A5. Use inline 10k resistors
 if you have a 5V board. If you are using the SparkFun breakout board you *do not* need 4.7k pull-up resistors
 on the bus (they are built-in).

 Software:
 .begin() Gets sensor on the I2C bus.
 .readAltitude() Returns float with meters above sealevel. Ex: 1638.94
 .readTemp() Returns float with current temperature in Celsius. Ex: 23.37
  Updated by PaulZC: October 19th, 2019
  */

//Porting Code to Raspberry pi 4 with WiringPi
//I'll learn to fork later

/*TODO translate IIC_Read, IIC_Write, toggleOneShot, readAltitude, readTemp from arduino to wiringpi*/
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>

#include "SparkFunMPL3115A2.h"

MPL3115A2::MPL3115A2()
{
  //Set initial values for private vars
}

void MPL3115A2::begin(uint8_t deviceAddress)
{
  wiringPiSetupGpio (void) ; //use the Broadcom GPIO pin numbers
  val = int wiringPiI2CSetup (int deviceAddress);
  // if return value of wiringPiI2CSetup() is negative an error has occured
  if (val < 0)
  {
      printf("wiringPiI2CSetup Error!!\n");
      return -1;
  }
  _I2Caddress = deviceAddress;
}

// These I2C function in this sketch.
byte MPL3115A2::IIC_Read(byte regAddr)
{
  // This function reads one byte over IIC
  _i2cPort->beginTransmission(_I2Caddress);
  _i2cPort->write(regAddr);  // Address of CTRL_REG1
  _i2cPort->endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
  _i2cPort->requestFrom(_I2Caddress, 1); // Request the data...
  return _i2cPort->read();
}

// These I2C function in this sketch.
void MPL3115A2::IIC_Write(byte regAddr, byte value)
{
  // This function writes one byto over IIC
  _i2cPort->beginTransmission(_I2Caddress);
  _i2cPort->write(regAddr);
  _i2cPort->write(value);
  _i2cPort->endTransmission(true);
}

//Clears then sets the OST bit which causes the sensor to immediately take another reading
//Needed to sample faster than 1Hz
void MPL3115A2::toggleOneShot(void)
{
  byte tempSetting = IIC_Read(CTRL_REG1); //Read current settings
  tempSetting &= ~(1<<1); //Clear OST bit
  IIC_Write(CTRL_REG1, tempSetting);

  tempSetting = IIC_Read(CTRL_REG1); //Read current settings to be safe
  tempSetting |= (1<<1); //Set OST bit
  IIC_Write(CTRL_REG1, tempSetting);
}

//Returns the number of meters above sea level
//Returns -1 if no new data is available
float MPL3115A2::readAltitude()
{
	toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

	//Wait for PDR bit, indicates we have new pressure data
	int counter = 0;
	while( (IIC_Read(STATUS) & (1<<1)) == 0)
	{
		if(++counter > 600) return(-999); //Error out after max of 512ms for a read
		delay(1);
	}

	// Read pressure registers
	_i2cPort->beginTransmission(_I2Caddress);
	_i2cPort->write(OUT_P_MSB);  // Address of data to get
	_i2cPort->endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
	if (_i2cPort->requestFrom(_I2Caddress, 3) != 3) { // Request three bytes
		return -999;
	}

	byte msb, csb, lsb;
	msb = _i2cPort->read();
	csb = _i2cPort->read();
	lsb = _i2cPort->read();

	// The least significant bytes l_altitude and l_temp are 4-bit,
	// fractional values, so you must cast the calulation in (float),
	// shift the value over 4 spots to the right and divide by 16 (since
	// there are 16 values in 4-bits).
	float tempcsb = (lsb>>4)/16.0;

	float altitude = (float)( (msb << 8) | csb) + tempcsb;

	return(altitude);
}

float MPL3115A2::readTemp()
{
	if(IIC_Read(STATUS) & (1<<1) == 0) toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

	//Wait for TDR bit, indicates we have new temp data
	int counter = 0;
	while( (IIC_Read(STATUS) & (1<<1)) == 0)
	{
		if(++counter > 600) return(-999); //Error out after max of 512ms for a read
		delay(1);
	}

	// Read temperature registers
	_i2cPort->beginTransmission(_I2Caddress);
	_i2cPort->write(OUT_T_MSB);  // Address of data to get
	_i2cPort->endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
	if (_i2cPort->requestFrom(_I2Caddress, 2) != 2) { // Request two bytes
		return -999;
	}

	byte msb, lsb;
	msb = _i2cPort->read();
	lsb = _i2cPort->read();

	toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading

    //Negative temperature fix by D.D.G.
	uint16_t foo = 0;
    bool negSign = false;

    //Check for 2s compliment
	if(msb > 0x7F)
	{
        foo = ~((msb << 8) + lsb) + 1;  //2’s complement
        msb = foo >> 8;
        lsb = foo & 0x00F0;
        negSign = true;
	}

	// The least significant bytes l_altitude and l_temp are 4-bit,
	// fractional values, so you must cast the calulation in (float),
	// shift the value over 4 spots to the right and divide by 16 (since
	// there are 16 values in 4-bits).
	float templsb = (lsb>>4)/16.0; //temp, fraction of a degree

	float temperature = (float)(msb + templsb);

	if (negSign) temperature = 0 - temperature;

	return(temperature);
}


