#pragma once
#include "config.h"

#include <string>

class Output
{
  public:
    virtual bool setValue(int value) = 0;
    int getValue();

  protected:
    int currentState = -1;
};
