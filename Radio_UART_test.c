/*
	UART communication on Raspberry Pi using C (WiringPi Library)
	https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c
*/

/*
Now, enter the following command to transmit data from Raspberry Pi terminal.
echo �Hello� > /dev/ttyS0
*/

/*
This command will output �Hello� string on UART port i.e. Tx pin and will display it on terminal application of PC/Laptop.
By default, mini UART is mapped to the GPIO14 (TX) and GPIO15(RX). While PL011 i.e. ttyAMA0 is connected to the on-board Bluetooth module.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int serial_port ;
  char dat;
  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  while(1){

	if(serialDataAvail (serial_port) )
	{
		dat = serialGetchar (serial_port);		/* receive character serially*/
		printf ("%c", dat) ;
		fflush (stdout) ;
		serialPutchar(serial_port, dat);		/* transmit character serially on port */
		  }
	}

}