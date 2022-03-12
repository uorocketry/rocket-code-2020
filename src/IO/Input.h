#pragma once
#include "IO.h"
#include "common/pch.h"

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