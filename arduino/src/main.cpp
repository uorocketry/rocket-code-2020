#include <Arduino.h>
#include <main.h>
#include <PacketSerial.h>
#include <ArduinoComm.pb.h>
#include <pb_decode.h>
#include "servoMessage.h"
#include "utils.h"

COBSPacketSerial cobsPacketSerial;

RocketryProto_ArduinoIn message = RocketryProto_ArduinoIn_init_zero;

void setup() {
  cobsPacketSerial.begin(115200);

  cobsPacketSerial.setPacketHandler(&onPacketReceived);
}

void loop() {
  cobsPacketSerial.update();
}

void onPacketReceived(const uint8_t* buffer, size_t size) {
  pb_istream_t stream = pb_istream_from_buffer(buffer, size);

  if (!pb_decode(&stream, RocketryProto_ArduinoIn_fields, &message)) {
    serialPrintLn("Error decoding message: ", stream.errmsg);
    return;
  }

  switch(message.which_data) {
    case RocketryProto_ArduinoIn_servoInit_tag:
      initServo(message);
    break;
    case RocketryProto_ArduinoIn_servoControl_tag:
      controlServo(message);
    break;
    default:
      serialPrintLn("Unknown message type. Ignoring request.");
  }
}
