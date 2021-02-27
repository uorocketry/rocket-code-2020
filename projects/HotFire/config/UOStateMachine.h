#pragma once

#include "config/config.h"
#include "stateMachineLib/StateMachine.h"
#include "IO/Interface.h"
#include "IO/InterfaceImpl.h"
#include "helpers/Types.h"
#include "data/UOSMData.h"
#include "data/sensorsData.h"

class UOStateMachine : public StateMachine
{
public:
	UOStateMachine();

	// External events taken by this state machine
	void StartFillingEXT();
	void StopFillingEXT();
	void AbortFillingEXT();
	void IgnitionEXT();
	void AbortBurnEXT();
	void FinalVentingEXT();
	void DoneEXT();

	void updateHotFire(UOSMData *data);
	
private:
	void detectExternEvent(std::shared_ptr<sensorsData> data);
	void showInfo(std::shared_ptr<sensorsData> data);

	InterfaceImpl interfaceImpl;
	Interface *interface = &(interfaceImpl);

	std::shared_ptr<sensorsData> hotFireData;

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
	STATE_DECLARE(UOStateMachine, Init, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitInit)
	// WaitForInit
	ENTRY_DECLARE(UOStateMachine, EnterWaitForInit, UOSMData)
	STATE_DECLARE(UOStateMachine, WaitForInit, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitWaitForInit)
	// WaitForFilling
	ENTRY_DECLARE(UOStateMachine, EnterWaitForFilling, UOSMData)
	STATE_DECLARE(UOStateMachine, WaitForFilling, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitWaitForFilling)
	// Filling
	ENTRY_DECLARE(UOStateMachine, EnterFilling, UOSMData)
	STATE_DECLARE(UOStateMachine, Filling, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitFilling)
	// WaitForIgnition
	ENTRY_DECLARE(UOStateMachine, EnterWaitForIgnition, UOSMData)
	STATE_DECLARE(UOStateMachine, WaitForIgnition, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitWaitForIgnition)
	// Ignition
	ENTRY_DECLARE(UOStateMachine, EnterIgnition, UOSMData)
	STATE_DECLARE(UOStateMachine, Ignition, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitIgnition)
	// FullBurn
	ENTRY_DECLARE(UOStateMachine, EnterFullBurn, UOSMData)
	STATE_DECLARE(UOStateMachine, FullBurn, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitFullBurn)
	// FinalVenting
	ENTRY_DECLARE(UOStateMachine, EnterFinalVenting, UOSMData)
	STATE_DECLARE(UOStateMachine, FinalVenting, UOSMData)
	EXIT_DECLARE(UOStateMachine, ExitFinalVenting)
	// Done
	ENTRY_DECLARE(UOStateMachine, EnterDone, UOSMData)
	STATE_DECLARE(UOStateMachine, Done, UOSMData)
	// AbortFilling
	ENTRY_DECLARE(UOStateMachine, EnterAbortFilling, UOSMData)
	STATE_DECLARE(UOStateMachine, AbortFilling, UOSMData)
	// AbortBurn
	ENTRY_DECLARE(UOStateMachine, EnterAbortBurn, UOSMData)
	STATE_DECLARE(UOStateMachine, AbortBurn, UOSMData)

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
	
	std::shared_ptr<sensorsData> updateInterface(const UOSMData *smdata, States state);
};