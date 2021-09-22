#include <Arduino.h>
#include <main.h>
#include <PacketSerial.h>
#include <ArduinoComm.pb.h>
#include <pb_decode.h>
#include "servoMessage.h"
#include "utils.h"
#include "digitalMessage.h"
#include "persistentInit.h"

COBSPacketSerial cobsPacketSerial;

void setup() {
  cobsPacketSerial.begin(57600);

  cobsPacketSerial.setPacketHandler(&onPacketReceived);

  restoreInitData();
}

void loop() {
  cobsPacketSerial.update();
}

void(* resetFunc) (void) = 0;

void onPacketReceived(const uint8_t* buffer, size_t size) {
  if (size == 0) return;

  RocketryProto_ArduinoIn message = RocketryProto_ArduinoIn_init_zero;

  pb_istream_t stream = pb_istream_from_buffer(buffer, size);

  if (!pb_decode(&stream, RocketryProto_ArduinoIn_fields, &message)) {
    serialPrintLn("Error decoding message: ", stream.errmsg);
    return;
  }

  switch(message.which_data) {
    case RocketryProto_ArduinoIn_servoInit_tag:
      initServo(message.data.servoInit);
    break;
    case RocketryProto_ArduinoIn_servoControl_tag:
      controlServo(message.data.servoControl);
    break;
    case RocketryProto_ArduinoIn_digitalInit_tag:
      initDigital(message.data.digitalInit);
    break;
    case RocketryProto_ArduinoIn_digitalControl_tag:
      controlDigital(message.data.digitalControl);
    break;
    case RocketryProto_ArduinoIn_reset_tag:
      resetFunc();
      break;
    case RocketryProto_ArduinoIn_initData_tag:
      saveInitData(buffer, size);
    break;
    default:
      serialPrintLn("Unknown message type. Ignoring request.");
  }
}