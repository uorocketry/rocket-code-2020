#include <Arduino.h>
#include <Servo.h>
#include <ArduinoComm.pb.h>

#define SERVO 0
#define DIGITAL 1
#define TESTING 0

int servoCount = 3;
int servoPins[] = {5, 2, 3};
Servo servos[3];
//int servoCount = 1;
//int servoPins[] = {5};
//Servo servos[1];

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
  byte buffer[3];
  Serial.readBytes(buffer, 3);
//  byte data[] = getData();
  byte input = buffer[1];

  // verify byte
  if (buffer[0] != 162) return;

  if (input != -1) {
    byte command = input & 0b11;
    byte index = (input >> 0b10) & 0b11;
  
    Serial.println("Input " + String(input));
    Serial.println("Command " + String(command));
    Serial.println("Index " + String(index));
  
    switch(command) {
      case SERVO:
        if (index < servoCount) {
//          unsigned int angle = (input >> 5) & 0b11111111;
           byte angle = buffer[2];
//          while (Serial.available() == 0);
//          int angle = getInt();

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

//byte* getData() {
////# if TESTING == 0
//  byte buffer[2];
//  Serial.readBytes(buffer, 2);
//  return buffer;
////#else
////  return Serial.parseInt();
////#endif
//}
