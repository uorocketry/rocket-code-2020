#define NOMINMAX // Fix issues on Windows with std:min and std:max

#include <wiringPi.h>
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

// Code for each state. Do not put while in them. The right function according to the current state
// will be call in the main loop.

STATE_DEFINE(UOStateMachine, Init, UOSMData)
{
    interface->initialize();

    #if USE_GPIO == 1
        
            #if USE_SV01
            interface->createNewGpioOutput(SV01_NAME, SV01_PIN);
            #endif

            #if USE_SV02
            interface->createNewGpioOutput(SV02_NAME, SV02_PIN);
            #endif
            
            #if USE_PWM_SBV01
            interface->createNewGpioPwmOutput(SBV01_NAME, SBV01_PIN);
            #endif

            #if USE_PWM_SBV02
            interface->createNewGpioPwmOutput(SBV02_NAME, SBV02_PIN);
            #endif

            #if USE_PWM_SBV03
            interface->createNewGpioPwmOutput(SBV03_NAME, SBV03_PIN);
            #endif
        
        #endif

    InternalEvent(ST_WAIT_FOR_INIT);
}

EXIT_DEFINE(UOStateMachine, ExitInit)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::ExitInit");
}

ENTRY_DEFINE(UOStateMachine, EnterWaitForInit, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::EnterWaitForInit");
    enterNewState(ST_WAIT_FOR_INIT);
}

STATE_DEFINE(UOStateMachine, WaitForInit, UOSMData)
{
    interfaceData = updateInterface(data, ST_WAIT_FOR_INIT);

    if (interfaceData->isInitialized())
    {
        InternalEvent(ST_CONTROL);
    }

    interface->updateOutputs(interfaceData);
}

EXIT_DEFINE(UOStateMachine, ExitWaitForInit)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::ExitWaitForInit");
}

ENTRY_DEFINE(UOStateMachine, EnterControl, UOSMData)
{
    SPDLOG_LOGGER_INFO(logger, "ServoControlSM::EnterControl");
    enterNewState(ST_CONTROL);
}

STATE_DEFINE(UOStateMachine, Control, UOSMData)
{
    interfaceData = updateInterface(data, ST_CONTROL);

    eventType eventNbr = interfaceData->eventNumber;

    /*
     * GPIO event number, a 4 bit binary number where the
     * 1st bit is the enable bit and the last 3 control
     * whether the PWM2, PWM1, and OUT1 are open/closed.
     * A '1' means to open the valve and a '0' to close it.
     *
     * 0 0 0 0 0 0
     * | | | | | ^--------- Enable bit
     * | | | | ^----------- USE_SV01
     * | | | ^------------- USE_SV02
     * | | ^--------------- USE_PWM_SBV01
     * | ^----------------- USE_PWM_SBV02
     * ^------------------- USE_PWM_SBV03
     */

    #if USE_GPIO == 1
        GpioData& gpioData = interfaceData->gpioData;

        // Check if enable bit is set
        bool enabled = eventNbr > 0 && (eventNbr & EVENT_ENABLE_MASK);

        #if USE_SV01 == 1
            if (enabled)
            {
                // Open SV01 is the first bit is set
                bool open = eventNbr & SV01_EVENT_ENABLE_MASK;

                gpioData.digitalOutputMap.insert({SV01_NAME, open ? SV01_OPEN : SV01_CLOSE});

                std::cout << "ServoControlSM::Control SV01 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

        #if USE_SV02 == 1
            if (enabled)
            {
                // Open SV02 if the second bit is set
                bool open = eventNbr & SV02_EVENT_ENABLE_MASK;

                gpioData.digitalOutputMap.insert({SV02_NAME, open ? SV02_OPEN : SV02_CLOSE});

                std::cout << "ServoControlSM::Control SV02 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

        #if USE_PWM_SBV01 == 1
            if (enabled)
            {
                // Open SBV01 if the third bit is set
                bool open = eventNbr & SBV01_EVENT_ENABLE_MASK;

                gpioData.pwmOutputMap.insert({SBV01_NAME, open ? SBV01_OPEN : SBV01_CLOSE});

                std::cout << "ServoControlSM::Control SBV01 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

        #if USE_PWM_SBV02 == 1
            if (enabled)
            {
                // Open SBV02 if the third bit is set
                bool open = eventNbr & SBV02_EVENT_ENABLE_MASK;

                gpioData.pwmOutputMap.insert({SBV02_NAME, open ? SBV02_OPEN : SBV02_CLOSE});

                std::cout << "ServoControlSM::Control SBV02 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

        #if USE_PWM_SBV03 == 1
            if (enabled)
            {
                // Open SBV03 if the third bit is set
                bool open = eventNbr & SBV03_EVENT_ENABLE_MASK;

                gpioData.pwmOutputMap.insert({SBV03_NAME, open ? SBV03_OPEN : SBV03_CLOSE});

                std::cout << "ServoControlSM::Control SBV03 " << (open ? "OPEN" : "CLOSE") << "\n";
            }
        #endif

    #endif

    interface->updateOutputs(interfaceData);
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
