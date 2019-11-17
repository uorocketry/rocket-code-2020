#include <stdio.h>
#include <wiringPi.h>
int main (void)
{
 wiringPiSetupGpio() ;
 printf("wiringPi setup\n");
 pinMode(0, OUTPUT) ;
  for (;;)
  {
    printf("digitalWrite\n");
    digitalWrite(3, HIGH);
    delay (500);
    digitalWrite(3, LOW);
    delay (500) ;
  }
  return 0 ;
}
