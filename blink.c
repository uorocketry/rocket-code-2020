#include <stdio.h>
#include <wiringPi.h>
int main (void)
{
 printf("Hello world!\n");
 wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  for (;;)
  {
    printf("digitalWrite\n");
    digitalWrite (19, HIGH) ; delay (500) ;
    digitalWrite (19,  LOW) ; delay (500) ;
  }
  return 0 ;
}
