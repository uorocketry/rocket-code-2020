#pragma once
#include "config/config.h"

#if USE_ARDUINO_PROXY == 1

#include "IO.h"
#include <ArduinoComm.pb.h>
#include <wiringSerial.h>

class ArduinoProxy : IO
{
  public:
    static ArduinoProxy *getInstance();

    ArduinoProxy();
    ~ArduinoProxy();

    void initialize();
    void run();
    bool isInitialized();

    void send(RocketryProto::ArduinoIn c);

    ArduinoProxy(ArduinoProxy const &) = delete;
    void operator=(ArduinoProxy const &) = delete;

  private:
    int fd = 0;
    bool inititialized = false;

    std::mutex serialMutex;

    void handleArduinoMessage(const RocketryProto::ArduinoOut &arduinoOut);
};

#endif