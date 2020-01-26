#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
  	printf ("Raspberry Pi wiringPi test program\n");
	wiringPiSetupGpio();
  	pinMode (12, PWM_OUTPUT) ;
   	pwmSetMode (PWM_MODE_MS);
   	pwmSetRange (2000);
   	pwmSetClock (192);

		for (int i = 1; i < 1000; i++)
		{
   			pwmWrite(12,i);
		}

		for (int j = 1000; j > 1; j--)
		{
			pwmWrite(12, j);
		}

	return 0;
}
