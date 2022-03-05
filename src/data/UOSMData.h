#pragma once

#include "../stateMachineLib/StateMachine.h"
#include "common/pch.h"

struct UOSMData : public EventData
{
    /** Keep in mind, this is NOT the time since unix epoch (1970), and not the
     * system time */
    time_point now;
};