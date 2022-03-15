#pragma once

#include "EventQueue.h"
#include "IO.h"
#include <mutex>

class Input : IO
{
  public:
    Input(EventQueue &eventQueue);
    ~Input();

    void initialize();
    void run();
    bool isInitialized();

  protected:
    std::mutex mutex;

  private:
    EventQueue &eventQueue;

    static bool isNumber(const std::string &s);
};
