#include <stdio.h>
#include <wiringPi.h>
int main (void)
{
 wiringPiSetup() ;
 printf("wiringPi setup\n");
 pinMode(2, OUTPUT) ;
  for (;;)
  {
    printf("digitalWrite\n");
    digitalWrite(2, HIGH);
    delay (500);
    digitalWrite(2, LOW);
    delay (500) ;
  }
  return 0 ;
}
