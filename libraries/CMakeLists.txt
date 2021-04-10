# ---------------
# sbgECom library
# ---------------

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/libraries/sbgECom/src/*.c)
file(GLOB_RECURSE COMMON_SRC ${PROJECT_SOURCE_DIR}/libraries/sbgECom/common/*.c)
file(GLOB_RECURSE SM_SRC ${PROJECT_SOURCE_DIR}/libraries/sbgECom/src/*.cpp)

if (MSVC)
    target_link_libraries(sbgECom Ws2_32)
endif()

#
#	Exclude platform specific files
#
if (NOT MSVC)
    list(REMOVE_ITEM COMMON_SRC "${PROJECT_SOURCE_DIR}/libraries/sbgECom/common/interfaces/sbgInterfaceSerialWin.c")
else ()
    list(REMOVE_ITEM COMMON_SRC "${PROJECT_SOURCE_DIR}/libraries/sbgECom/common/interfaces/sbgInterfaceSerialUnix.c")
endif()

add_library(sbgECom STATIC ${SRC} ${COMMON_SRC} ${SM_SRC})

target_include_directories(sbgECom PUBLIC ./sbgECom/common ./sbgECom/src)


# ---------------
# WiringPi library
# ---------------

file(GLOB_RECURSE WIRINGPI_SRC ${PROJECT_SOURCE_DIR}/libraries/WiringPi/wiringPi/*.c)
add_library(WiringPi STATIC ${WIRINGPI_SRC})

target_include_directories(WiringPi PUBLIC ./WiringPi/wiringPi)

# ---------------
# Unit Testing - Catch2
# ---------------

add_subdirectory(./Catch2)
