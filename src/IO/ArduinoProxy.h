#pragma once
#include "config.h"

#if USE_ARDUINO_PROXY == 1

#include "IO.h"
#include "arduino/DCMotorState.h"
#include <ArduinoComm.pb.h>
#include <wiringSerial.h>

class ArduinoProxy : IO
{
  public:
    static ArduinoProxy *getInstance();

    ArduinoProxy();
    ~ArduinoProxy();

    void initialize() override;
    void run() override;
    bool isInitialized() override;

    void send(const RocketryProto::ArduinoIn &c);

    bool getDigitalState(int pin);
    int getServoState(int pin);
    DCMotorState getDCMotorState(int forwardPin, int reversePin);

    ArduinoProxy(ArduinoProxy const &) = delete;
    void operator=(ArduinoProxy const &) = delete;

  private:
    std::map<unsigned int, std::pair<bool, std::chrono::time_point<std::chrono::steady_clock>>> digitalStates;
    std::map<unsigned int, std::pair<int, std::chrono::time_point<std::chrono::steady_clock>>> servoStates;
    std::map<std::pair<unsigned int, unsigned int>, DCMotorState> dcMotorStates;
    std::mutex stateMutex;

    int fd = 0;
    bool inititialized = false;

    std::mutex serialMutex;

    void handleArduinoMessage(const RocketryProto::ArduinoOut &arduinoOut);
};

#endif