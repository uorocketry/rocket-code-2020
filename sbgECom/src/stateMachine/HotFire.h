#pragma once

#include "../stateMachineLib/StateMachine.h"
#include "../IO/Interface.h"
#include "../helpers/Types.h"
#include "../data/HotFireSMData.h"
#include "../data/hotFireState.h"

#ifndef USE_SBG
#define USE_SBG 0
#endif

#ifndef USE_SOCKET_CLIENT
#define USE_SOCKET_CLIENT 1
#endif

#ifndef USE_LOGGER
#define USE_LOGGER 1
#endif

#ifndef USE_INPUT
#define USE_INPUT 1
#endif

#ifndef USE_TESTING_SENSORS
#define USE_TESTING_SENSORS 0
#endif

class HotFire : public StateMachine
{
public:
	HotFire();

	// External events taken by this state machine
	void StartFillingEXT();
	void StopFillingEXT();
	void AbortFillingEXT();
	void IgnitionEXT();
	void AbortBurnEXT();
	void FinalVentingEXT();
	void DoneEXT();

	void updateHotFire(HotFireSMData *data);

private:
	void detectExternEvent(const hotFireState *data);
	void showInfo(const hotFireState *data);

	Interface hotFireInterface;
	hotFireState *hotFireData;

	time_point entryTime;

	// State enumeration order must match the order of state method entries
	// in the state map.
	enum States
	{
		ST_INIT,
		ST_WAIT_FOR_INIT,
		ST_WAIT_FOR_FILLING,
		ST_FILLING,
		ST_WAIT_FOR_IGNITION,
		ST_IGNITION,
		ST_FULL_BURN,
		ST_FINAL_VENTING,
		ST_DONE,
		ST_ABORT_FILLING,
		ST_ABORT_BURN,
		ST_MAX_STATES
	};

	// Define the state machine state functions with event data type
	// Init
	STATE_DECLARE(HotFire, Init, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitInit)
	// WaitForInit
	ENTRY_DECLARE(HotFire, EnterWaitForInit, HotFireSMData)
	STATE_DECLARE(HotFire, WaitForInit, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitWaitForInit)
	// WaitForFilling
	ENTRY_DECLARE(HotFire, EnterWaitForFilling, HotFireSMData)
	STATE_DECLARE(HotFire, WaitForFilling, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitWaitForFilling)
	// Filling
	ENTRY_DECLARE(HotFire, EnterFilling, HotFireSMData)
	STATE_DECLARE(HotFire, Filling, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitFilling)
	// WaitForIgnition
	ENTRY_DECLARE(HotFire, EnterWaitForIgnition, HotFireSMData)
	STATE_DECLARE(HotFire, WaitForIgnition, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitWaitForIgnition)
	// Ignition
	ENTRY_DECLARE(HotFire, EnterIgnition, HotFireSMData)
	STATE_DECLARE(HotFire, Ignition, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitIgnition)
	// FullBurn
	ENTRY_DECLARE(HotFire, EnterFullBurn, HotFireSMData)
	STATE_DECLARE(HotFire, FullBurn, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitFullBurn)
	// FinalVenting
	ENTRY_DECLARE(HotFire, EnterFinalVenting, HotFireSMData)
	STATE_DECLARE(HotFire, FinalVenting, HotFireSMData)
	EXIT_DECLARE(HotFire, ExitFinalVenting)
	// Done
	ENTRY_DECLARE(HotFire, EnterDone, HotFireSMData)
	STATE_DECLARE(HotFire, Done, HotFireSMData)
	// AbortFilling
	ENTRY_DECLARE(HotFire, EnterAbortFilling, HotFireSMData)
	STATE_DECLARE(HotFire, AbortFilling, HotFireSMData)
	// AbortBurn
	ENTRY_DECLARE(HotFire, EnterAbortBurn, HotFireSMData)
	STATE_DECLARE(HotFire, AbortBurn, HotFireSMData)

	BEGIN_STATE_MAP_EX
	STATE_MAP_ENTRY_ALL_EX(&Init, 0, 0, &ExitInit)
	STATE_MAP_ENTRY_ALL_EX(&WaitForInit, 0, &EnterWaitForInit, &ExitWaitForInit)
	STATE_MAP_ENTRY_ALL_EX(&WaitForFilling, 0, &EnterWaitForFilling, &ExitWaitForFilling)
	STATE_MAP_ENTRY_ALL_EX(&Filling, 0, &EnterFilling, &ExitFilling)
	STATE_MAP_ENTRY_ALL_EX(&WaitForIgnition, 0, &EnterWaitForIgnition, &ExitWaitForIgnition)
	STATE_MAP_ENTRY_ALL_EX(&Ignition, 0, &EnterIgnition, &ExitIgnition)
	STATE_MAP_ENTRY_ALL_EX(&FullBurn, 0, &EnterFullBurn, &ExitFullBurn)
	STATE_MAP_ENTRY_ALL_EX(&FinalVenting, 0, &EnterFinalVenting, &ExitFinalVenting)
	STATE_MAP_ENTRY_ALL_EX(&Done, 0, &EnterDone, 0)
	STATE_MAP_ENTRY_ALL_EX(&AbortFilling, 0, &EnterAbortFilling, 0)
	STATE_MAP_ENTRY_ALL_EX(&AbortBurn, 0, &EnterAbortBurn, 0)
	END_STATE_MAP_EX

	void enterNewState(States state);
};