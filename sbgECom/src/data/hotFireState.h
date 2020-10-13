#pragma once

#include "HotFireSMData.h"

//all the informations about the rocket that the state machine will need
struct hotFireState
{
	HotFireSMData hotFireSMData;
	int inputEventNumber = -1;
#ifndef NO_SOCKET_CONTROL
	int clientEventNumber = -1;
#endif
};