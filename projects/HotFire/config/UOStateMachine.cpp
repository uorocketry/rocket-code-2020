#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include <wiringPi.h>
#include "config/config.h"
#include "config/GpioConfig.h"
#include "UOStateMachine.h"
#include <iostream>
#include "data/sensorsData.h"
#include "helpers/Types.h"
#include "data/GpioData.h"

UOStateMachine::UOStateMachine() : 
	InterfacingStateMachine(ST_MAX_STATES), interfaceImpl()
{

	// There is no state entry function for the first state
	enterNewState(States(0));

	interface = &interfaceImpl;
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
	interface->initialize();
	#if USE_GPIO
	
	#if USE_PWM1
	interface->createNewGpioPwmOutput(PWM1_NAME, PWM1_PIN);
	#endif

	#if USE_PWM2
	interface->createNewGpioPwmOutput(PWM2_NAME, PWM2_PIN);
	#endif

	#if USE_OUT1
	interface->createNewGpioOutput(OUT1_NAME, OUT1_PIN);
	#endif
	
	#endif

	InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(UOStateMachine, ExitInit)
{
	std::cout << "HotFireSM::ExitInit\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
	std::cout << "HotFireSM::EnterWaitForInit\n";
	enterNewState(ST_WAIT_FOR_INIT);
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
	interfaceData = updateInterface(data, ST_WAIT_FOR_INIT);
	#if USE_GPIO
		GpioData& gpioData = interfaceData->gpioData;

		#if USE_PWM1
		gpioData.pwmOutputMap.insert({PWM1_NAME, PWM1_OPEN});
		#endif

		#if USE_PWM2
		gpioData.pwmOutputMap.insert({PWM2_NAME, PWM2_OPEN});
		#endif

		#if USE_OUT1
		gpioData.outputMap.insert({OUT1_NAME, OUT1_OPEN});
		#endif
		
	#endif
	
	// Must add logic to determine if the interface is ready based on interface data

	// if (interface->isInitialized())
	// {
	// 	InternalEvent(ST_WAIT_FOR_FILLING);
	// }

	// showInfo(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
	std::cout << "HotFireSM::ExitWaitForInit\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForFilling, UOSMData)
{
	std::cout << "HotFireSM::EnterWaitForFilling\n";
	enterNewState(ST_WAIT_FOR_FILLING);
}

STATE_DEFINE(UOStateMachine, WaitForFilling, UOSMData)
{
	interfaceData = updateInterface(data, ST_WAIT_FOR_FILLING);

	#if USE_GPIO
		GpioData& gpioData = interfaceData->gpioData;

		#if USE_PWM1
		gpioData.pwmOutputMap.insert({PWM1_NAME, PWM1_OPEN});
		#endif

		#if USE_PWM2
		gpioData.pwmOutputMap.insert({PWM2_NAME, PWM2_OPEN});
		#endif

		#if USE_OUT1
		gpioData.outputMap.insert({OUT1_NAME, OUT1_OPEN});
		#endif
		
	#endif

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForFilling)
{
	std::cout << "HotFireSM::ExitWaitForFilling\n";
}

ENTRY_DEFINE(UOStateMachine, EnterFilling, UOSMData)
{
	std::cout << "HotFireSM::EnterFilling\n";
	enterNewState(ST_FILLING);
}
	
STATE_DEFINE(UOStateMachine, Filling, UOSMData)
{
	interfaceData = updateInterface(data, ST_FILLING);
	
	#if USE_GPIO
		GpioData& gpioData = interfaceData->gpioData;

		#if USE_PWM1
		gpioData.pwmOutputMap.insert({PWM1_NAME, PWM1_CLOSE});
		#endif

		#if USE_PWM2
		gpioData.pwmOutputMap.insert({PWM2_NAME, PWM2_CLOSE});
		#endif

		#if USE_OUT1
		gpioData.outputMap.insert({OUT1_NAME, OUT1_CLOSE});
		#endif
		
	#endif
	
	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitFilling)
{
	std::cout << "HotFireSM::ExitFilling\n";
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForIgnition, UOSMData)
{
	std::cout << "HotFireSM::WaitForIgnition\n";
	enterNewState(ST_WAIT_FOR_IGNITION);
}

STATE_DEFINE(UOStateMachine, WaitForIgnition, UOSMData)
{
	interfaceData = updateInterface(data, ST_WAIT_FOR_IGNITION);

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForIgnition)
{
	std::cout << "HotFireSM::ExitWaitForIgnition\n";
}

ENTRY_DEFINE(UOStateMachine, EnterIgnition, UOSMData)
{
	std::cout << "HotFireSM::EnterIgnition\n";
	enterNewState(ST_IGNITION);
}

STATE_DEFINE(UOStateMachine, Ignition, UOSMData)
{
	interfaceData = updateInterface(data, ST_IGNITION);

	detectExternEvent(interfaceData);
	switchStatesAfterTime((ST_FULL_BURN), duration_ms(5000));

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitIgnition)
{
	std::cout << "HotFireSM::ExitIgnition\n";
}

ENTRY_DEFINE(UOStateMachine, EnterFullBurn, UOSMData)
{
	std::cout << "HotFireSM::EnterFullBurn\n";
	enterNewState(ST_FULL_BURN);
}

STATE_DEFINE(UOStateMachine, FullBurn, UOSMData)
{
	interfaceData = updateInterface(data, ST_FULL_BURN);

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitFullBurn)
{
	std::cout << "HotFireSM::ExitFullBurn\n";
}

ENTRY_DEFINE(UOStateMachine, EnterFinalVenting, UOSMData)
{
	std::cout << "HotFireSM::EnterFinalVenting\n";
	enterNewState(ST_FINAL_VENTING);
}

STATE_DEFINE(UOStateMachine, FinalVenting, UOSMData)
{
	interfaceData = updateInterface(data, ST_FINAL_VENTING);

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitFinalVenting)
{
	std::cout << "HotFireSM::ExitFinalVenting\n";
}

ENTRY_DEFINE(UOStateMachine, EnterDone, UOSMData)
{
	std::cout << "HotFireSM::EnterDone\n";
	std::cout << "Done.\n";
	enterNewState(ST_DONE);
}

STATE_DEFINE(UOStateMachine, Done, UOSMData)
{
	interfaceData = updateInterface(data, ST_DONE);

	interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(UOStateMachine, EnterAbortFilling, UOSMData)
{
	std::cout << "HotFireSM::EnterAbortFilling\n";
	enterNewState(ST_ABORT_FILLING);
}

STATE_DEFINE(UOStateMachine, AbortFilling, UOSMData)
{
	interfaceData = updateInterface(data, ST_ABORT_FILLING);

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(UOStateMachine, EnterAbortBurn, UOSMData)
{
	std::cout << "HotFireSM::EnterAbortBurn\n";
	enterNewState(ST_ABORT_BURN);
}

STATE_DEFINE(UOStateMachine, AbortBurn, UOSMData)
{
	interfaceData = updateInterface(data, ST_ABORT_BURN);

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

void UOStateMachine::detectExternEvent(std::shared_ptr<sensorsData> data)
{
	eventType eventNbr = data->eventNumber;

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
}

void UOStateMachine::showInfo(std::shared_ptr<sensorsData> data)
{
}

void UOStateMachine::updateHotFire(UOSMData *data)
{
	ExecuteCurrentState(data);
}

std::shared_ptr<sensorsData> UOStateMachine::updateInterface(const UOSMData *smdata, States state)
{
	interface->updateInputs();
	std::shared_ptr<sensorsData> data = interface->getLatest();

	// If statement to prevent overwiring data from TESTING
	if (data->timeStamp == -1) data->timeStamp = smdata->now.time_since_epoch().count();
	
	data->currentStateNo = state;

	return data;
}
