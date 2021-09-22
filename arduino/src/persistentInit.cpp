#include "persistentInit.h"
#include <EEPROM.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "utils.h"
#include "servoMessage.h"
#include "digitalMessage.h"


const uint16_t ID_BYTE = 0x0;
const uint8_t ID_VALUE = 0xa8;

// We are using two bytes to store the size
const uint16_t SIZE_BYTE = 0x1;

const uint16_t DATA_START_BYTE = 0x3;
const uint16_t DATA_MAX_SIZE = 512 - DATA_START_BYTE;

void handleInitDataMessage(const RocketryProto_InitData_Data &data);

void(* resetFunc2) (void) = 0;

void saveInitData(const uint8_t* buffer, size_t size) {
    if (size > DATA_MAX_SIZE) {
        serialError("Cannot store the init data. Max size is ", DATA_MAX_SIZE, ", while init size is ", size);
        return;
    }

    // Write the ID
    EEPROM.write(ID_BYTE, ID_VALUE);
    
    // Write the data length
    EEPROM.write(SIZE_BYTE, (size >> 4) & 0xff);
    EEPROM.write(SIZE_BYTE + 1, size & 0xff);

    // Write the actual data
    for (size_t i = 0; i < size; i++) {
        EEPROM.write(DATA_START_BYTE+i, buffer[i]);
    }

    serialInfo("Successfully wrote init data to the EEPROM. Now resseting...");

    resetFunc2();
}

bool readEEPROM(pb_istream_t *stream, uint8_t *buf, size_t count) {
    for (size_t i = 0; i < count; i++) {
        buf[i] = EEPROM.read(DATA_START_BYTE+i);
    }
    
    return true;
}

bool restoreCallback(pb_istream_t *stream, const pb_field_iter_t *field, void **arg) {
    RocketryProto_InitData_Data data = RocketryProto_InitData_Data_init_zero;
    if(pb_decode(stream, RocketryProto_InitData_Data_fields, &data) == false) {
        serialError("Error decoding field");
        return false;
    }

    handleInitDataMessage(data);
    return true;
}

void restoreInitData() {
    uint8_t id = EEPROM.read(ID_BYTE);
    if (id != ID_VALUE) {
        serialWarning("No existing init data is currently stored.");
        return;
    }

    uint8_t sizeHigh = EEPROM.read(SIZE_BYTE);
    uint8_t sizeLow = EEPROM.read(SIZE_BYTE+1);
    uint16_t size = (sizeHigh << 4) | sizeLow;
    serialInfo("Reading ", size, " bytes from the EEPROM...");

    RocketryProto_ArduinoIn arduinoIn = RocketryProto_ArduinoIn_init_zero;
    arduinoIn.data.initData.data.funcs.decode = restoreCallback;

    pb_istream_t eepromStream = {&readEEPROM, nullptr, size};

    if (!pb_decode(&eepromStream, RocketryProto_ArduinoIn_fields, &arduinoIn)) {
        serialPrintLn("Error decoding message: ", eepromStream.errmsg);
        return;
    }
}

void handleInitDataMessage(const RocketryProto_InitData_Data &data) {
    serialInfo("Handling message ", data.which_data, " from storage.");

    switch (data.which_data)
    {
    case RocketryProto_InitData_Data_digitalInit_tag:
        initDigital(data.data.digitalInit);
        break;
    case RocketryProto_InitData_Data_servoInit_tag:
        initServo(data.data.servoInit);
        break;
    default:
        serialWarning("Unkown message type ", data.which_data);
        break;
    }

}