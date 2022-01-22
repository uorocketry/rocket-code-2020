#pragma once
#include "config.h"
#if USE_GPIO == 1

#include <string>

class Output
{
  public:
    virtual bool setValue(int value) = 0;
    int getValue();

  protected:
    int currentState = -1;
};

#endif
