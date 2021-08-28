#include <Servo.h>

#define SERVO 0
#define DIGITAL 1
#define TESTING 1

//int servoCount = 3;
//int servoPins[] = {1, 2, 3};
//Servo servos[3];
int servoCount = 1;
int servoPins[] = {5};
Servo servos[1];

int digitalPinCount = 1;
int digitalPins[] = {13};

void setup() {
  Serial.begin(57600);

  for (int i = 0; i < servoCount; i++) {
     servos[i].attach(servoPins[i]);
  }

  for (int i = 0; i < digitalPinCount; i++) {
     pinMode(digitalPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() == 0) return;
  int input = getInt();

  if (input != -1) {
    unsigned int command = input & 0b11;
    unsigned int index = (input >> 0b10) & 0b11;
  
    Serial.println("Input " + String(input));
    Serial.println("Command " + String(command));
    Serial.println("Index " + String(index));
  
    switch(command) {
      case SERVO:
        if (index < servoCount) {
//          unsigned int angle = input & 0b111111110000;
          while (Serial.available() == 0);
          int angle = getInt();

          Serial.println("Angle " + String(angle));
          if (angle < 0 || angle > 180) return;
          
          Servo currentServo = servos[index];
          currentServo.write(angle);
        }
        break;
        
      case DIGITAL:
        // TODO: Digital is untested
        if (index < digitalPinCount) {
          unsigned int enabled = (input >> 0b1000) & 0b1;
          if (enabled == 1) {
            digitalWrite(digitalPins[index], HIGH);
          } else {
            digitalWrite(digitalPins[index], LOW);
          }
          
        }
    }
  }
}

int getInt() {
# if TESTING == 0
  return Serial.read();
#else
  return Serial.parseInt();
#endif
}
