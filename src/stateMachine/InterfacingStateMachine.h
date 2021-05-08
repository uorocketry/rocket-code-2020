#pragma once
#include "IO/Interface.h"
#include "IO/InterfaceImpl.h"
#include "IO/TestingInterface.h"
#include "data/sensorsData.h"
#include "stateMachineLib/StateMachine.h"
#include <memory>

class InterfacingStateMachine : public StateMachine
{

public:
    explicit InterfacingStateMachine(BYTE maxStates, BYTE initialState = 0);

    void enterNewState(BYTE state);
	double getValueForTime(double minimum, double maximum, duration_ms targetTime);
	bool switchStatesAfterTime(BYTE state, duration_ms targetTime);
	bool isDelayElapsed(duration_ms targetTime);

protected:

#if TESTING != 1
	InterfaceImpl interfaceImpl;
#else
	TestingInterface interfaceImpl;
#endif
	Interface *interface;

	std::shared_ptr<sensorsData> interfaceData;
};