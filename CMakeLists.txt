cmake_minimum_required(VERSION 3.15)

project(RocketCode2020 C CXX)
set(CMAKE_CXX_STANDARD 17)

cmake_host_system_information(RESULT _memfree QUERY AVAILABLE_PHYSICAL_MEMORY)
set_property(GLOBAL PROPERTY JOB_POOLS four_jobs=4)
if (_memfree LESS 1000)
    set(CMAKE_JOB_POOL_COMPILE four_jobs)
endif ()


# Import conan dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message(STATUS "################# Loaded Conan Libs: ${CONAN_LIBS} #################")

# Import custom dependencies
add_subdirectory(./libraries)

list(APPEND CompilerFlags
        # Flags
        "HOTFIRE_TEST"
        "USE_LOGGER" "USE_INPUT"
        "USE_SOCKET_CLIENT"
        "SKIP_INIT"
        "TESTING"
        "DESKTOP_COMPAT"
        # Sensors
        "USE_SBG"  "USE_RADIO"  "USE_WIRING_Pi"  "USE_GPIO"  "USE_ARDUINO_PROXY"  "USE_SENSORS" "USE_SENSOR_SUITE"
        )

foreach(flag IN LISTS CompilerFlags)
    if (DEFINED ENV{${flag}})
        add_compile_definitions(${flag}=$ENV{${flag}})
    elseif(DEFINED ${flag})
        add_compile_definitions(${flag}=${${flag}})
    endif ()
endforeach()

#-- -- -- -- -- -- -- -
#Main executable
#-- -- -- -- -- -- -- -
find_package(Threads)

if (DEFINED ENV{SERVO_CONTROL} OR SERVO_CONTROL)
    file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/ServoControl/*.*)
elseif (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
    file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/HotFire/**)
else ()
    file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/OctoberSky1/**)
endif ()

file(GLOB_RECURSE SRC_MAIN ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(MainLoopLib ${SRC_MAIN} ${MAIN_CONFIG_SRC})
target_include_directories(MainLoopLib PUBLIC ./src/)


target_link_libraries(MainLoopLib ${CONAN_LIBS})
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


if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")
    target_include_directories(MainLoopLib PUBLIC "$ENV{BOOST_DIRECTORY}")
    target_link_directories(MainLoopLib PUBLIC "$ENV{BOOST_DIRECTORY}/stage/lib")
    target_link_libraries(MainLoopLib boost_filesystem boost_system)

    target_include_directories(MainLoopLib PUBLIC "$ENV{LIBI2C_DIRECTORY}/include")
    target_link_directories(MainLoopLib PUBLIC "$ENV{LIBI2C_DIRECTORY}/lib")
else ()
    target_link_libraries(MainLoopLib systemd)
endif ()


target_link_libraries(MainLoopLib protobufDef)
target_link_libraries(MainLoopLib cobs-c)
target_link_libraries(MainLoopLib ${CMAKE_THREAD_LIBS_INIT})

add_executable(MainLoop ./src/init/MainLoop.cpp)
target_link_libraries(MainLoop MainLoopLib)

add_subdirectory(./unitTesting)
