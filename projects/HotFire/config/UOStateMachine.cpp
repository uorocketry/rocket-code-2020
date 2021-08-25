#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include "config/config.h"
#include "config/GpioConfig.h"
#include "UOStateMachine.h"
#include <iostream>
#include "data/sensorsData.h"
#include "helpers/Types.h"
#include "data/GpioData.h"
#include <spdlog/spdlog.h>

UOStateMachine::UOStateMachine(Interface* anInterface) :
        InterfacingStateMachine(anInterface, ST_MAX_STATES)
{

	// There is no state entry function for the first state
	enterNewState(States(0));

	logger = spdlog::default_logger();
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
		END_TRANSITION_MAP(nullptr)
}

// Abort external event
void UOStateMachine::AbortEXT()
{
	BEGIN_TRANSITION_MAP					   // - Current State -
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_INIT
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_WAIT_FOR_INIT
		TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_FILLING
		TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_FILLING
		TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_IGNITION
		TRANSITION_MAP_ENTRY(ST_ABORT_BURN)	   // ST_IGNITION
		TRANSITION_MAP_ENTRY(ST_ABORT_BURN)	   // ST_FULL_BURN
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_FINAL_VENTING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_DONE
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_ABORT_FILLING
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)	   // ST_ABORT_BURN
		END_TRANSITION_MAP(nullptr)
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
		END_TRANSITION_MAP(nullptr)
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
		END_TRANSITION_MAP(nullptr)
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
		END_TRANSITION_MAP(nullptr)
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
	END_TRANSITION_MAP(nullptr)}

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop.

STATE_DEFINE(UOStateMachine, Init, UOSMData)
{
	interface->initialize();
	#if USE_GPIO == 1
	
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
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterWaitForInit");
	enterNewState(ST_WAIT_FOR_INIT);
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
	interfaceData = updateInterface(data, ST_WAIT_FOR_INIT);
	#if USE_GPIO == 1
		GpioData& gpioData = interfaceData->gpioData;

		#if USE_PWM1
		gpioData.pwmOutputMap.insert({PWM1_NAME, PWM1_OPEN});
		#endif

		#if USE_PWM2
		gpioData.pwmOutputMap.insert({PWM2_NAME, PWM2_OPEN});
		#endif

		#if USE_OUT1
		gpioData.digitalOutputMap.insert({OUT1_NAME, OUT1_OPEN});
		#endif
		
	#endif
	
	if (interfaceData->isInitialized())
	{
		InternalEvent(ST_WAIT_FOR_FILLING);
	}

	// showInfo(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForFilling, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterWaitForFilling");
	enterNewState(ST_WAIT_FOR_FILLING);
}

STATE_DEFINE(UOStateMachine, WaitForFilling, UOSMData)
{
	interfaceData = updateInterface(data, ST_WAIT_FOR_FILLING);

	#if USE_GPIO == 1
		GpioData& gpioData = interfaceData->gpioData;

		#if USE_PWM1
		gpioData.pwmOutputMap.insert({PWM1_NAME, PWM1_OPEN});
		#endif

		#if USE_PWM2
		gpioData.pwmOutputMap.insert({PWM2_NAME, PWM2_OPEN});
		#endif

		#if USE_OUT1
		gpioData.digitalOutputMap.insert({OUT1_NAME, OUT1_OPEN});
		#endif
		
	#endif

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForFilling)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForFilling");
}

ENTRY_DEFINE(UOStateMachine, EnterFilling, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFilling");
	enterNewState(ST_FILLING);
}
	
STATE_DEFINE(UOStateMachine, Filling, UOSMData)
{
	interfaceData = updateInterface(data, ST_FILLING);
	
	#if USE_GPIO == 1
		GpioData& gpioData = interfaceData->gpioData;

		#if USE_PWM1
		gpioData.pwmOutputMap.insert({PWM1_NAME, PWM1_CLOSE});
		#endif

		#if USE_PWM2
		gpioData.pwmOutputMap.insert({PWM2_NAME, PWM2_CLOSE});
		#endif

		#if USE_OUT1
		gpioData.digitalOutputMap.insert({OUT1_NAME, OUT1_CLOSE});
		#endif
		
	#endif
	
	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitFilling)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFilling");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForIgnition, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::WaitForIgnition");
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
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForIgnition");
}

ENTRY_DEFINE(UOStateMachine, EnterIgnition, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterIgnition");
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
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitIgnition");
}

ENTRY_DEFINE(UOStateMachine, EnterFullBurn, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFullBurn");
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
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFullBurn");
}

ENTRY_DEFINE(UOStateMachine, EnterFinalVenting, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFinalVenting");
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
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFinalVenting");
}

ENTRY_DEFINE(UOStateMachine, EnterDone, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterDone");
	SPDLOG_LOGGER_INFO(logger, "Done.");
	enterNewState(ST_DONE);
}

STATE_DEFINE(UOStateMachine, Done, UOSMData)
{
	interfaceData = updateInterface(data, ST_DONE);

	interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(UOStateMachine, EnterAbortFilling, UOSMData)
{
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterAbortFilling");
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
	SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterAbortBurn");
	enterNewState(ST_ABORT_BURN);
}

STATE_DEFINE(UOStateMachine, AbortBurn, UOSMData)
{
	interfaceData = updateInterface(data, ST_ABORT_BURN);

	detectExternEvent(interfaceData);

	interface->updateOutputs(interfaceData);
}

void UOStateMachine::detectExternEvent(const std::shared_ptr<sensorsData>& data)
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
			AbortEXT();
			break;
		default:
			break;
	}
}

void UOStateMachine::showInfo(const std::shared_ptr<sensorsData>& data)
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
