include(FetchContent)
# ---------------
# sbgECom library
# ---------------
FetchContent_Declare(
        sbgECom
        GIT_REPOSITORY https://github.com/SBG-Systems/sbgECom.git
        GIT_TAG        3.1.2358-stable
)

FetchContent_GetProperties(sbgECom)
if(NOT sbgecom_POPULATED)
    FetchContent_Populate(sbgECom)

    set(SBG_COMMON_DIR ${sbgecom_SOURCE_DIR}/common)
    set(SBG_SRC_DIR ${sbgecom_SOURCE_DIR}/src)

    file(GLOB_RECURSE SBG_SRC ${SBG_SRC_DIR}/*.c)
    file(GLOB_RECURSE SBG_COMMON_SRC ${SBG_COMMON_DIR}/*.c)

    if (NOT MSVC)
        list(REMOVE_ITEM SBG_COMMON_SRC "${SBG_COMMON_DIR}/interfaces/sbgInterfaceSerialWin.c")
    else ()
        list(REMOVE_ITEM SBG_COMMON_SRC "${SBG_COMMON_DIR}/interfaces/sbgInterfaceSerialUnix.c")
    endif()

    add_library(sbgECom STATIC ${SBG_SRC} ${SBG_COMMON_SRC})
    target_include_directories(sbgECom PUBLIC ${SBG_COMMON_DIR} ${SBG_SRC_DIR})
endif()

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

FetchContent_MakeAvailable(protobufDef)
