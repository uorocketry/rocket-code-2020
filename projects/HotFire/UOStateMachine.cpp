#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include "UOStateMachine.h"
#include <iostream>
#include "data/sensorsData.h"

UOStateMachine::UOStateMachine() : StateMachine(ST_MAX_STATES)
{

	// There is no state entry function for the first state
	enterNewState(States(0));
}

// StartFilling external event
void UOStateMachine::StartFillingEXT()
{
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(ST_FILLING)	// ST_WAIT_FOR_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FINAL_VENTING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
		END_TRANSITION_MAP(NULL)
}

// StopFilling external event
void UOStateMachine::StopFillingEXT()
{
	BEGIN_TRANSITION_MAP						   // - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_WAIT_FOR_FILLING
		TRANSITION_MAP_ENTRY(ST_WAIT_FOR_IGNITION) // ST_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_WAIT_FOR_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_FULL_BURN
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_FINAL_VENTING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_DONE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_ABORT_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		   // ST_ABORT_BURN
		END_TRANSITION_MAP(NULL)
}

// AbortFilling external event
void UOStateMachine::AbortFillingEXT()
{
	BEGIN_TRANSITION_MAP					   // - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_FILLING
		TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_FILLING
		TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_FULL_BURN
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_FINAL_VENTING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_DONE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_ABORT_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_ABORT_BURN
		END_TRANSITION_MAP(NULL)
}

// Ignition external event
void UOStateMachine::IgnitionEXT()
{
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
		TRANSITION_MAP_ENTRY(ST_IGNITION)	// ST_WAIT_FOR_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FINAL_VENTING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
		END_TRANSITION_MAP(NULL)
}

// AbortBurn external event
void UOStateMachine::AbortBurnEXT()
{
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_IGNITION
		TRANSITION_MAP_ENTRY(ST_ABORT_BURN) // ST_IGNITION
		TRANSITION_MAP_ENTRY(ST_ABORT_BURN) // ST_FULL_BURN
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FINAL_VENTING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
		END_TRANSITION_MAP(NULL)
}

// FinalVenting external event
void UOStateMachine::FinalVentingEXT()
{
	BEGIN_TRANSITION_MAP					   // - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_WAIT_FOR_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_WAIT_FOR_IGNITION
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_IGNITION
		TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_FULL_BURN
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_FINAL_VENTING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_DONE
		TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_ABORT_FILLING
		TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_ABORT_BURN
		END_TRANSITION_MAP(NULL)
}

// Done external event
void UOStateMachine::DoneEXT(){
	BEGIN_TRANSITION_MAP					// - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_INIT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_INIT
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_FILLING
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_FILLING
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_WAIT_FOR_IGNITION
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_IGNITION
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_FULL_BURN
	TRANSITION_MAP_ENTRY(ST_DONE)			// ST_FINAL_VENTING
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_DONE
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_ABORT_FILLING
	TRANSITION_MAP_ENTRY(EVENT_IGNORED)		// ST_ABORT_BURN
	END_TRANSITION_MAP(NULL)}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop.

STATE_DEFINE(UOStateMachine, Init, UOSMData)
{
	hotFireInterface.initializeSensors();

	InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(UOStateMachine, ExitInit)
{
	std::cout << "HotFireSM::ExitInit\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
	std::cout << "HotFireSM::EnterWaitForInit\n";
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	// if (hotFireInterface.sensorsInitialized())
	// 	InternalEvent(ST_FLIGHT);
	InternalEvent(ST_WAIT_FOR_FILLING);

	// showInfo(hotFireData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
	std::cout << "HotFireSM::ExitWaitForInit\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForFilling, UOSMData)
{
	std::cout << "HotFireSM::EnterWaitForFilling\n";
}

STATE_DEFINE(UOStateMachine, WaitForFilling, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForFilling)
{
	std::cout << "HotFireSM::ExitWaitForFilling\n";
}

ENTRY_DEFINE(UOStateMachine, EnterFilling, UOSMData)
{
	std::cout << "HotFireSM::EnterFilling\n";
}

STATE_DEFINE(UOStateMachine, Filling, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(UOStateMachine, ExitFilling)
{
	std::cout << "HotFireSM::ExitFilling\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForIgnition, UOSMData)
{
	std::cout << "HotFireSM::WaitForIgnition\n";
}

STATE_DEFINE(UOStateMachine, WaitForIgnition, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForIgnition)
{
	std::cout << "HotFireSM::ExitWaitForIgnition\n";
}

ENTRY_DEFINE(UOStateMachine, EnterIgnition, UOSMData)
{
	std::cout << "HotFireSM::EnterIgnition\n";
}

STATE_DEFINE(UOStateMachine, Ignition, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(UOStateMachine, ExitIgnition)
{
	std::cout << "HotFireSM::ExitIgnition\n";
}

ENTRY_DEFINE(UOStateMachine, EnterFullBurn, UOSMData)
{
	std::cout << "HotFireSM::EnterFullBurn\n";
}

STATE_DEFINE(UOStateMachine, FullBurn, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(UOStateMachine, ExitFullBurn)
{
	std::cout << "HotFireSM::ExitFullBurn\n";
}

ENTRY_DEFINE(UOStateMachine, EnterFinalVenting, UOSMData)
{
	std::cout << "HotFireSM::EnterFinalVenting\n";
}

STATE_DEFINE(UOStateMachine, FinalVenting, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(UOStateMachine, ExitFinalVenting)
{
	std::cout << "HotFireSM::ExitFinalVenting\n";
}

ENTRY_DEFINE(UOStateMachine, EnterDone, UOSMData)
{
	std::cout << "HotFireSM::EnterDone\n";
}

STATE_DEFINE(UOStateMachine, Done, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	std::cout << "Done.\n";
}

ENTRY_DEFINE(UOStateMachine, EnterAbortFilling, UOSMData)
{
	std::cout << "HotFireSM::EnterAbortFilling\n";
}

STATE_DEFINE(UOStateMachine, AbortFilling, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

ENTRY_DEFINE(UOStateMachine, EnterAbortBurn, UOSMData)
{
	std::cout << "HotFireSM::EnterAbortBurn\n";
}

STATE_DEFINE(UOStateMachine, AbortBurn, UOSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

void UOStateMachine::detectExternEvent(const sensorsData *data)
{
	int eventNbr = data->inputEventNumber;

	switch (eventNbr)
	{
	case 0:
		StartFillingEXT();
		break;
	case 1:
		StopFillingEXT();
		break;
	case 2:
		IgnitionEXT();
		break;
	case 3:
		FinalVentingEXT();
		break;
	case 4:
		DoneEXT();
		break;
	case 5:
		AbortFillingEXT();
		break;
	case 6:
		AbortBurnEXT();
	default:
		break;
	}

#if USE_SOCKET_CONTROL
	eventNbr = data->clientEventNumber;

	switch (eventNbr)
	{
	case 0:
		StartFillingEXT();
		break;
	case 1:
		StopFillingEXT();
		break;
	case 2:
		IgnitionEXT();
		break;
	case 3:
		FinalVentingEXT();
		break;
	case 4:
		DoneEXT();
		break;
	case 5:
		AbortFillingEXT();
		break;
	case 6:
		AbortBurnEXT();
	default:
		break;
	}
#endif
}

void UOStateMachine::showInfo(const sensorsData *data)
{
}

void UOStateMachine::updateHotFire(UOSMData *data)
{
	ExecuteCurrentState(data);
}

void UOStateMachine::enterNewState(States state)
{
	entryTime = std::chrono::steady_clock::now();
}