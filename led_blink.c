#include <wiringPi.h>
#include <stdio.h>
int LED = 26;			/* GPIO26 as per wiringPi, GPIO12 as per BCM, pin no.32 */
int main(){
	wiringPiSetup();	/* initialize wiringPi setup */
	pinMode(LED,OUTPUT);	/* set GPIO as output */
	printf("wiringPiSetup\n");

	while (1){
		printf("digitalWrite\n");
		digitalWrite(LED,HIGH);		/* write high on GPIO */
		delay(1000);
		digitalWrite(LED, LOW);		/* write low on GPIO */
		delay(1000);
		}
	return 0;
}
