#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include "HotFire.h"
#include <iostream>
#include "../data/sensorsData.h"

HotFire::HotFire() : StateMachine(ST_MAX_STATES)
{

	// There is no state entry function for the first state
	enterNewState(States(0));
}

// StartFilling external event
void HotFire::StartFillingEXT()
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
void HotFire::StopFillingEXT()
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
void HotFire::AbortFillingEXT()
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
void HotFire::IgnitionEXT()
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
void HotFire::AbortBurnEXT()
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
void HotFire::FinalVentingEXT()
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
void HotFire::DoneEXT(){
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

STATE_DEFINE(HotFire, Init, HotFireSMData)
{
	hotFireInterface.initializeSensors();

	InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(HotFire, ExitInit)
{
	std::cout << "HotFireSM::ExitInit\n";
}

ENTRY_DEFINE(HotFire, EnterWaitForInit, HotFireSMData)
{
	std::cout << "HotFireSM::EnterWaitForInit\n";
}

STATE_DEFINE(HotFire, WaitForInit, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	// if (hotFireInterface.sensorsInitialized())
	// 	InternalEvent(ST_FLIGHT);
	InternalEvent(ST_WAIT_FOR_FILLING);

	// showInfo(hotFireData);
}

EXIT_DEFINE(HotFire, ExitWaitForInit)
{
	std::cout << "HotFireSM::ExitWaitForInit\n";
}

ENTRY_DEFINE(HotFire, EnterWaitForFilling, HotFireSMData)
{
	std::cout << "HotFireSM::EnterWaitForFilling\n";
}

STATE_DEFINE(HotFire, WaitForFilling, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(HotFire, ExitWaitForFilling)
{
	std::cout << "HotFireSM::ExitWaitForFilling\n";
}

ENTRY_DEFINE(HotFire, EnterFilling, HotFireSMData)
{
	std::cout << "HotFireSM::EnterFilling\n";
}

STATE_DEFINE(HotFire, Filling, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(HotFire, ExitFilling)
{
	std::cout << "HotFireSM::ExitFilling\n";
}

ENTRY_DEFINE(HotFire, EnterWaitForIgnition, HotFireSMData)
{
	std::cout << "HotFireSM::WaitForIgnition\n";
}

STATE_DEFINE(HotFire, WaitForIgnition, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(HotFire, ExitWaitForIgnition)
{
	std::cout << "HotFireSM::ExitWaitForIgnition\n";
}

ENTRY_DEFINE(HotFire, EnterIgnition, HotFireSMData)
{
	std::cout << "HotFireSM::EnterIgnition\n";
}

STATE_DEFINE(HotFire, Ignition, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(HotFire, ExitIgnition)
{
	std::cout << "HotFireSM::ExitIgnition\n";
}

ENTRY_DEFINE(HotFire, EnterFullBurn, HotFireSMData)
{
	std::cout << "HotFireSM::EnterFullBurn\n";
}

STATE_DEFINE(HotFire, FullBurn, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(HotFire, ExitFullBurn)
{
	std::cout << "HotFireSM::ExitFullBurn\n";
}

ENTRY_DEFINE(HotFire, EnterFinalVenting, HotFireSMData)
{
	std::cout << "HotFireSM::EnterFinalVenting\n";
}

STATE_DEFINE(HotFire, FinalVenting, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

EXIT_DEFINE(HotFire, ExitFinalVenting)
{
	std::cout << "HotFireSM::ExitFinalVenting\n";
}

ENTRY_DEFINE(HotFire, EnterDone, HotFireSMData)
{
	std::cout << "HotFireSM::EnterDone\n";
}

STATE_DEFINE(HotFire, Done, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	std::cout << "Done.\n";
}

ENTRY_DEFINE(HotFire, EnterAbortFilling, HotFireSMData)
{
	std::cout << "HotFireSM::EnterAbortFilling\n";
}

STATE_DEFINE(HotFire, AbortFilling, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

ENTRY_DEFINE(HotFire, EnterAbortBurn, HotFireSMData)
{
	std::cout << "HotFireSM::EnterAbortBurn\n";
}

STATE_DEFINE(HotFire, AbortBurn, HotFireSMData)
{
	// hotFireInterface.update(data);
	// hotFireData = hotFireInterface.getLatest();

	detectExternEvent(hotFireData);
}

void HotFire::detectExternEvent(const hotFireState *data)
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

void HotFire::showInfo(const hotFireState *data)
{
}

void HotFire::updateHotFire(HotFireSMData *data)
{
	ExecuteCurrentState(data);
}

void HotFire::enterNewState(States state)
{
	entryTime = std::chrono::steady_clock::now();
}