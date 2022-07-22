include(FetchContent)

# ---------------
# sbgECom library
# ---------------
FetchContent_Declare(
        sbgECom
        GIT_REPOSITORY https://github.com/SBG-Systems/sbgECom.git
        GIT_TAG        3.1.2358-stable
        SOURCE_SUBDIR  cmake
)

FetchContent_MakeAvailable(sbgECom)
target_include_directories(sbgECom PUBLIC ${sbgECom_SOURCE_DIR}/../common ${sbgECom_SOURCE_DIR}/../src)
# ---------------
# WiringPi library
# ---------------
FetchContent_Declare(
        WiringPi
        GIT_REPOSITORY https://github.com/WiringPi/WiringPi.git
        GIT_TAG        master
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
)


FetchContent_GetProperties(WiringPi)
if(NOT wiringpi_POPULATED)
    FetchContent_Populate(WiringPi)

    file(GLOB_RECURSE WIRINGPI_SRC ${wiringpi_SOURCE_DIR}/wiringPi/*.c)
    add_library(WiringPi STATIC ${WIRINGPI_SRC})

    target_include_directories(WiringPi PUBLIC ${wiringpi_SOURCE_DIR}/wiringPi)

    # Ignore annoying warnings we can't do anything about
    set_target_properties(WiringPi PROPERTIES COMPILE_FLAGS "-w")
    # Bring the populated content into the build
endif()

# ---------------
# spdlog library
# ---------------
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.10.0
)

# ---------------
# Unit Testing - Catch2
# ---------------
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG       v3.1.0

)

# ---------------
# Unit Testing - Catch2
# ---------------
FetchContent_Declare(
        cobs-c
        GIT_REPOSITORY https://github.com/cmcqueen/cobs-c.git
        GIT_TAG       0.5.0
)

FetchContent_GetProperties(cobs-c)
if(NOT cobs-c_POPULATED)
    FetchContent_Populate(cobs-c)
    add_library(cobs-c STATIC ${cobs-c_SOURCE_DIR}/cobs.c)
    target_include_directories(cobs-c PUBLIC ${cobs-c_SOURCE_DIR})
endif()

# ---------------
# Protobuf Definitions
# ---------------
FetchContent_Declare(
        protobufDef
        GIT_REPOSITORY https://github.com/uorocketry/protobuf-definitions.git
        GIT_TAG       master
)

FetchContent_MakeAvailable(spdlog catch2 protobufDef)
