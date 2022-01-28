#include "config.h"
#if USE_GPIO == 1

#include "./Output.h"

int Output::getValue()
{
    return currentState;
};

#endif