#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include "HotFireStateMachine.h"
#include "HotFireGpioConfig.h"
#include "common/pch.h"
#include "config.h"
#include "data/GpioData.h"
#include "data/StateData.h"
#include <iostream>
#include <spdlog/spdlog.h>

const uint64_t nm = 1000000000;
const uint64_t connectionFailsafeTimeout = 1 * 60 * 60 * nm;

HotFireStateMachine::HotFireStateMachine(Interface *anInterface) : InterfacingStateMachine(anInterface, ST_MAX_STATES)
{

    // There is no state entry function for the first state
    enterNewState(States(0));

    logger = spdlog::default_logger();
}

// StartFilling external event
void HotFireStateMachine::ReadyEXT()
{
    BEGIN_TRANSITION_MAP                          // - Current State -
    TRANSITION_MAP_ENTRY(EVENT_IGNORED)           // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(ST_WAIT_FOR_FILLING) // ST_WAIT_FOR_READY
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_DONE
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)       // ST_SERVO_CONTROL
        END_TRANSITION_MAP
}

// StartFilling external event
void HotFireStateMachine::StartFillingEXT()
{
    BEGIN_TRANSITION_MAP                    // - Current State -
    TRANSITION_MAP_ENTRY(EVENT_IGNORED)     // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_READY
        TRANSITION_MAP_ENTRY(ST_FILLING)    // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
        TRANSITION_MAP_ENTRY(ST_FILLING)    // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_SERVO_CONTROL
        END_TRANSITION_MAP
}

// Abort external event
void HotFireStateMachine::AbortEXT()
{
    BEGIN_TRANSITION_MAP                       // - Current State -
    TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_READY
        TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_FILLING
        TRANSITION_MAP_ENTRY(ST_ABORT_FILLING) // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(ST_ABORT_BURN)    // ST_IGNITION
        TRANSITION_MAP_ENTRY(ST_ABORT_BURN)    // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_DONE
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_SERVO_CONTROL
        END_TRANSITION_MAP
}

// StopFilling external event
void HotFireStateMachine::StopFillingEXT()
{
    BEGIN_TRANSITION_MAP                           // - Current State -
    TRANSITION_MAP_ENTRY(EVENT_IGNORED)            // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_WAIT_FOR_READY
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(ST_WAIT_FOR_IGNITION) // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_DONE
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_SERVO_CONTROL
        END_TRANSITION_MAP
}

// Ignition external event
void HotFireStateMachine::IgnitionEXT()
{
    BEGIN_TRANSITION_MAP                    // - Current State -
    TRANSITION_MAP_ENTRY(EVENT_IGNORED)     // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_READY
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
        TRANSITION_MAP_ENTRY(ST_IGNITION)   // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
        TRANSITION_MAP_ENTRY(ST_IGNITION)   // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_SERVO_CONTROL
        END_TRANSITION_MAP
}

// FinalVenting external event
void HotFireStateMachine::FinalVentingEXT()
{
    BEGIN_TRANSITION_MAP                       // - Current State -
    TRANSITION_MAP_ENTRY(EVENT_IGNORED)        // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_READY
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_IGNITION
        TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_DONE
        TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(ST_FINAL_VENTING) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)    // ST_SERVO_CONTROL
        END_TRANSITION_MAP
}

// Done external event
void HotFireStateMachine::DoneEXT()
{
    BEGIN_TRANSITION_MAP                    // - Current State -
    TRANSITION_MAP_ENTRY(EVENT_IGNORED)     // ST_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_INIT
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_READY
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_WAIT_FOR_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_IGNITION
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_FULL_BURN
        TRANSITION_MAP_ENTRY(ST_DONE)       // ST_FINAL_VENTING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_DONE
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_FILLING
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_ABORT_BURN
        TRANSITION_MAP_ENTRY(EVENT_IGNORED) // ST_SERVO_CONTROL
        END_TRANSITION_MAP
}

// Done external event
// clang-format off
void HotFireStateMachine::ServoControlEXT() {
    BEGIN_TRANSITION_MAP                       // - Current State -
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_INIT
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_WAIT_FOR_INIT
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_WAIT_FOR_READY
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_WAIT_FOR_FILLING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_FILLING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_WAIT_FOR_IGNITION
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_IGNITION
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_FULL_BURN
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_FINAL_VENTING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_DONE
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_ABORT_FILLING
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_ABORT_BURN
    TRANSITION_MAP_ENTRY(ST_SERVO_CONTROL)     // ST_SERVO_CONTROL
    END_TRANSITION_MAP
} // clang-format on

// Code for each state. Do not put while in them. The right function according
// to the current state will be call in the main loop.

STATE_DEFINE(HotFireStateMachine, Init, UOSMData)
{
    interface->initialize();
#if USE_GPIO == 1

#if USE_VENT
    interface->createNewGpioOutput(VENT_NAME, VENT_PIN);
#endif

#if USE_HEATER
    interface->createNewGpioOutput(HEATER_NAME, HEATER_PIN);
#endif

#if USE_PWM_MAIN
    interface->createNewGpioPwmOutput(MAIN_NAME, MAIN_PIN, MAIN_SAFE, MAIN_SOFTPWM);
#endif

#if USE_PWM_PINHOLE
    interface->createNewGpioPwmOutput(PINHOLE_NAME, PINHOLE_PIN, PINHOLE_SAFE, PINHOLE_SOFTPWM);
#endif

#if USE_PWM_FILL
    interface->createNewGpioPwmOutput(FILL_NAME, FILL_PIN, FILL_SAFE, FILL_SOFTPWM);
#endif

#endif
    NoEventData eventData;
    InternalEvent(ST_WAIT_FOR_INIT, eventData);
}

EXIT_DEFINE(HotFireStateMachine, ExitInit)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitInit");
}

ENTRY_DEFINE(HotFireStateMachine, EnterWaitForInit, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterWaitForInit");
    enterNewState(ST_WAIT_FOR_INIT);
}

STATE_DEFINE(HotFireStateMachine, WaitForInit, UOSMData)
{
    interfaceData = updateInterface(&data, ST_WAIT_FOR_INIT);
    NoEventData eventData;
    if (interfaceData->isInitialized())
    {
        InternalEvent(ST_WAIT_FOR_READY, eventData);
    }

    // showInfo(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitWaitForInit)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForInit");
}

ENTRY_DEFINE(HotFireStateMachine, EnterWaitForReady, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterWaitForReady");
    enterNewState(ST_WAIT_FOR_READY);
}

STATE_DEFINE(HotFireStateMachine, WaitForReady, UOSMData)
{
    interfaceData = updateInterface(&data, ST_WAIT_FOR_READY);

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitWaitForReady)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForReady");
}

ENTRY_DEFINE(HotFireStateMachine, EnterWaitForFilling, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterWaitForFilling");
    enterNewState(ST_WAIT_FOR_FILLING);
}

STATE_DEFINE(HotFireStateMachine, WaitForFilling, UOSMData)
{
    interfaceData = updateInterface(&data, ST_WAIT_FOR_FILLING);

#if USE_GPIO == 1
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_CLOSE});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_CLOSE});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitWaitForFilling)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForFilling");
}

ENTRY_DEFINE(HotFireStateMachine, EnterFilling, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFilling");
    enterNewState(ST_FILLING);
}

STATE_DEFINE(HotFireStateMachine, Filling, UOSMData)
{
    interfaceData = updateInterface(&data, ST_FILLING);

#if USE_GPIO == 1
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_CLOSE});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_OPEN});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_OPEN});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitFilling)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFilling");
}

ENTRY_DEFINE(HotFireStateMachine, EnterWaitForIgnition, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::WaitForIgnition");
    enterNewState(ST_WAIT_FOR_IGNITION);
}

STATE_DEFINE(HotFireStateMachine, WaitForIgnition, UOSMData)
{
    interfaceData = updateInterface(&data, ST_WAIT_FOR_IGNITION);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_CLOSE});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_CLOSE});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitWaitForIgnition)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitWaitForIgnition");
}

ENTRY_DEFINE(HotFireStateMachine, EnterIgnition, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterIgnition");
    enterNewState(ST_IGNITION);
}

STATE_DEFINE(HotFireStateMachine, Ignition, UOSMData)
{
    interfaceData = updateInterface(&data, ST_IGNITION);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_IGNITION});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_CLOSE});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif
    EventData eventData;
    detectExternEvent(interfaceData);
    switchStatesAfterTime((ST_FULL_BURN), duration_ms(5000), eventData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitIgnition)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitIgnition");
}

ENTRY_DEFINE(HotFireStateMachine, EnterFullBurn, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFullBurn");
    enterNewState(ST_FULL_BURN);
}

STATE_DEFINE(HotFireStateMachine, FullBurn, UOSMData)
{
    interfaceData = updateInterface(&data, ST_FULL_BURN);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_OPEN});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_CLOSE});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitFullBurn)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFullBurn");
}

ENTRY_DEFINE(HotFireStateMachine, EnterFinalVenting, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterFinalVenting");
    enterNewState(ST_FINAL_VENTING);
}

STATE_DEFINE(HotFireStateMachine, FinalVenting, UOSMData)
{
    interfaceData = updateInterface(&data, ST_FINAL_VENTING);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_OPEN});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_CLOSE});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_OPEN});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(HotFireStateMachine, ExitFinalVenting)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::ExitFinalVenting");
}

ENTRY_DEFINE(HotFireStateMachine, EnterDone, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterDone");
    SPDLOG_LOGGER_INFO(logger, "Done.");
    enterNewState(ST_DONE);
}

STATE_DEFINE(HotFireStateMachine, Done, UOSMData)
{
    interfaceData = updateInterface(&data, ST_DONE);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_OPEN});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_OPEN});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(HotFireStateMachine, EnterAbortFilling, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterAbortFilling");
    enterNewState(ST_ABORT_FILLING);
}

STATE_DEFINE(HotFireStateMachine, AbortFilling, UOSMData)
{
    interfaceData = updateInterface(&data, ST_ABORT_FILLING);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_CLOSE});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_CLOSE});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(HotFireStateMachine, EnterAbortBurn, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterAbortBurn");
    enterNewState(ST_ABORT_BURN);
}

STATE_DEFINE(HotFireStateMachine, AbortBurn, UOSMData)
{
    interfaceData = updateInterface(&data, ST_ABORT_BURN);

#if USE_GPIO
    GpioData &gpioData = interfaceData->gpioData;

#if USE_VENT
    gpioData.digitalOutputMap.insert({VENT_NAME, VENT_CLOSE});
#endif

#if USE_PWM_MAIN
    gpioData.pwmOutputMap.insert({MAIN_NAME, MAIN_CLOSE});
#endif

#if USE_PWM_PINHOLE
    gpioData.pwmOutputMap.insert({PINHOLE_NAME, PINHOLE_CLOSE});
#endif

#if USE_PWM_FILL
    gpioData.pwmOutputMap.insert({FILL_NAME, FILL_CLOSE});
#endif

#endif

    detectExternEvent(interfaceData);

    interface->updateOutputs(interfaceData);
}

ENTRY_DEFINE(HotFireStateMachine, EnterServoControl, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "HotFireSM::EnterServoControl");
    enterNewState(ST_SERVO_CONTROL);
}

STATE_DEFINE(HotFireStateMachine, ServoControl, UOSMData)
{
    interfaceData = updateInterface(&data, ST_SERVO_CONTROL);

    detectConnectionTimeout(interfaceData);

    eventType eventNbr = interfaceData->eventNumber;
    bool dataRecieved = eventNbr > -1;

    if (dataRecieved)
    {
#if USE_GPIO == 1
        GpioData &gpioData = interfaceData->gpioData;

        /*
         * GPIO event number, a 6 bit binary number where the
         * 1st bit is the enable bit and the last 5 control
         * whether the valves are open/closed.
         * A '1' means to open the valve and a '0' to close it.
         *
         * 0 0 0 0 0 0
         * | | | | | ^--------- Enable bit
         * | | | | ^----------- USE_VENT
         * | | | ^------------- USE_SV02
         * | | ^--------------- USE_PWM_MAIN
         * | ^----------------- USE_PWM_PINHOLE
         * ^------------------- USE_PWM_FILL
         */

        bool enabled = eventNbr > 0 && (eventNbr & EVENT_ENABLE_MASK);
        if (enabled)
        {

#if USE_VENT == 1
            {
                bool open = (eventNbr & VENT_EVENT_ENABLE_MASK) > 0;

                gpioData.digitalOutputMap.insert({VENT_NAME, open ? VENT_OPEN : VENT_CLOSE});

                logValveStatus(VENT_NAME, open);
            }
#endif

#if USE_PWM_MAIN == 1
            {
                bool open = (eventNbr & MAIN_EVENT_ENABLE_MASK) > 0;

                gpioData.pwmOutputMap.insert({MAIN_NAME, open ? MAIN_OPEN : MAIN_CLOSE});

                logValveStatus(MAIN_NAME, open);
            }
#endif

#if USE_PWM_PINHOLE == 1
            {
                bool open = (eventNbr & PINHOLE_EVENT_ENABLE_MASK) > 0;

                gpioData.pwmOutputMap.insert({PINHOLE_NAME, open ? PINHOLE_OPEN : PINHOLE_CLOSE});

                logValveStatus(PINHOLE_NAME, open);
            }
#endif

#if USE_PWM_FILL == 1
            {
                bool open = (eventNbr & FILL_EVENT_ENABLE_MASK) > 0;

                gpioData.pwmOutputMap.insert({FILL_NAME, open ? FILL_OPEN : FILL_CLOSE});

                logValveStatus(FILL_NAME, open);
            }
#endif
        }
        else
        {
            // Switch back to specified state
            InternalEvent(eventNbr >> 1, data);
        }
#endif
    }

    interface->updateOutputs(interfaceData);
}

void HotFireStateMachine::logValveStatus(std::string valveName, bool status)
{
    if (status)
    {
        SPDLOG_LOGGER_INFO(logger, "ServoControlSM::Control " + valveName + " OPEN");
    }
    else
    {
        SPDLOG_LOGGER_INFO(logger, "ServoControlSM::Control " + valveName + " CLOSE");
    }
}

void HotFireStateMachine::detectConnectionTimeout(const std::shared_ptr<StateData> &data)
{
#if USE_SOCKET_CLIENT
    uint64_t timestamp =
        std::chrono::duration_cast<time_point::duration>(std::chrono::steady_clock::now().time_since_epoch()).count();
    static bool connectionAborted = false;
    if (!connectionAborted && data->lastActiveClientTimestamp != 0 &&
        timestamp - data->lastActiveClientTimestamp > connectionFailsafeTimeout)
    {
        connectionAborted = true;
        SPDLOG_ERROR("TCP Client has been disconnected for too long. Aborting!");
        EventData eventData;
        InternalEvent(ST_FINAL_VENTING, eventData);
    }
#endif
}

void HotFireStateMachine::detectExternEvent(const std::shared_ptr<StateData> &data)
{
    detectConnectionTimeout(data);

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
    case 6:
        ServoControlEXT();
        break;
    case 7:
        ReadyEXT();
        break;
    case 8:
        heaterOn = true;
        break;
    case 9:
        heaterOn = false;
        break;
    default:
        break;
    }
}

void HotFireStateMachine::updateHotFire(UOSMData &data)
{
    ExecuteCurrentState(data);
}

std::shared_ptr<StateData> HotFireStateMachine::updateInterface(const UOSMData *smdata, States state)
{
    interface->updateInputs();
    std::shared_ptr<StateData> data = interface->getLatest();

    data->currentStateNo = state;

    updateHeater(data);

    return data;
}

void HotFireStateMachine::updateHeater(const std::shared_ptr<StateData> &interfaceData)
{
#if USE_GPIO == 1 && USE_HEATER
    GpioData &gpioData = interfaceData->gpioData;

    if (heaterOn)
    {
        gpioData.digitalOutputMap.insert({HEATER_NAME, HEATER_ON});
    }
    else
    {
        gpioData.digitalOutputMap.insert({HEATER_NAME, HEATER_OFF});
    }
#endif
}