#pragma once

#include "helpers/Types.h"

#include "stateMachine/StateMachine.h"

struct RocketSMData : public EventData {
    /** Keep in mind, this is NOT the time since unix epoch (1970), and not the system time */
	time_point now;
};