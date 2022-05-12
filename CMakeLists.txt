cmake_minimum_required(VERSION 3.12)

project(RocketCode2020 C CXX)

cmake_host_system_information(RESULT _memfree QUERY AVAILABLE_PHYSICAL_MEMORY)
set_property(GLOBAL PROPERTY JOB_POOLS four_jobs=4)
if (_memfree LESS 1000)
    set(CMAKE_JOB_POOL_COMPILE four_jobs)
endif ()

add_subdirectory(./libraries)

if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
    add_compile_definitions(HOTFIRE_TEST=$ENV{HOTFIRE_TEST})
endif ()

if (DEFINED ENV{USE_LOGGER} OR USE_LOGGER)
    add_compile_definitions(USE_LOGGER=$ENV{USE_LOGGER})
endif ()

if (DEFINED ENV{USE_SOCKET_CLIENT} OR USE_SOCKET_CLIENT)
    add_compile_definitions(USE_SOCKET_CLIENT=$ENV{USE_SOCKET_CLIENT})
endif ()

if (DEFINED ENV{USE_INPUT} OR USE_INPUT)
    add_compile_definitions(USE_INPUT=$ENV{USE_INPUT})
endif ()

if (DEFINED ENV{SKIP_INIT} OR SKIP_INIT)
    add_compile_definitions(SKIP_INIT=$ENV{SKIP_INIT})
endif ()

if (DEFINED ENV{TESTING} OR TESTING)
    add_compile_definitions(TESTING=$ENV{TESTING})
endif ()

if (DEFINED ENV{DESKTOP_COMPAT} OR DESKTOP_COMPAT)
    add_compile_definitions(DESKTOP_COMPAT=$ENV{DESKTOP_COMPAT})
endif ()

#Sensors

if (DEFINED ENV{USE_SBG} OR USE_SBG)
    add_compile_definitions(USE_SBG=$ENV{USE_SBG})
endif ()

if (DEFINED ENV{USE_RADIO} OR USE_RADIO)
    add_compile_definitions(USE_RADIO=$ENV{USE_RADIO})
endif ()

if (DEFINED ENV{USE_WIRING_Pi} OR USE_WIRING_Pi)
    add_compile_definitions(USE_WIRING_Pi=$ENV{USE_WIRING_Pi})
endif ()

if (DEFINED ENV{USE_GPIO} OR USE_GPIO)
    add_compile_definitions(USE_GPIO=$ENV{USE_GPIO})
endif ()

if (DEFINED ENV{USE_ARDUINO_PROXY} OR USE_ARDUINO_PROXY)
    add_compile_definitions(USE_ARDUINO_PROXY=$ENV{USE_ARDUINO_PROXY})
endif ()

#-- -- -- -- -- -- -- -
#Main executable
#-- -- -- -- -- -- -- -
find_package(Threads)

if (DEFINED ENV{SERVO_CONTROL} OR SERVO_CONTROL)
    file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/ServoControl/*.cpp)
elseif (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
    file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/HotFire/*.cpp)
else ()
    file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/OctoberSky1/*.cpp)
endif ()

file(GLOB_RECURSE SRC_MAIN ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(MainLoopLib ${SRC_MAIN} ${MAIN_CONFIG_SRC})

target_include_directories(MainLoopLib PUBLIC ./src/)

target_precompile_headers(MainLoopLib PUBLIC ${PROJECT_SOURCE_DIR}/src/common/pch.h)

if (DEFINED ENV{SERVO_CONTROL} OR SERVO_CONTROL)
    target_include_directories(MainLoopLib PUBLIC
            ./projects/ServoControl/
            )
    target_include_directories(MainLoopLib PUBLIC
            ./projects/HotFire/
            )
elseif (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
    target_include_directories(MainLoopLib PUBLIC
            ./projects/HotFire/
            )
else ()
    target_include_directories(MainLoopLib PUBLIC
            ./projects/OctoberSky1/
            )
endif ()

target_link_libraries(MainLoopLib sbgECom)
add_dependencies(MainLoopLib sbgECom)

target_link_libraries(MainLoopLib WiringPi)
add_dependencies(MainLoopLib WiringPi)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
    target_include_directories(MainLoopLib PUBLIC "$ENV{BOOST_DIRECTORY}")
    target_link_directories(MainLoopLib PUBLIC "$ENV{BOOST_DIRECTORY}/stage/lib")
    target_link_libraries(MainLoopLib boost_filesystem boost_system)

    target_include_directories(MainLoopLib PUBLIC "$ENV{LIBI2C_DIRECTORY}/include")
    target_link_directories(MainLoopLib PUBLIC "$ENV{LIBI2C_DIRECTORY}/lib")
else ()
    target_link_libraries(MainLoopLib systemd)
    find_package(Boost 1.65.1 COMPONENTS system filesystem REQUIRED)
    target_include_directories(MainLoopLib PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(MainLoopLib ${Boost_LIBRARIES})
endif ()

target_link_libraries(MainLoopLib i2c)

target_link_libraries(MainLoopLib spdlog::spdlog)

target_link_libraries(MainLoopLib protobufDef)

target_link_libraries(MainLoopLib cobs-c)

target_link_libraries(MainLoopLib ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(MainLoopLib i2c)
add_executable(MainLoop ./src/init/MainLoop.cpp)
target_link_libraries(MainLoop MainLoopLib)

add_subdirectory(./unitTesting)
