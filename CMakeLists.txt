cmake_minimum_required(VERSION 3.12)

project(RocketCode2020 C CXX)

add_subdirectory(./libraries)


if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
	add_compile_definitions(HOTFIRE_TEST=$ENV{HOTFIRE_TEST})
endif()

if (DEFINED ENV{USE_LOGGER} OR USE_LOGGER)
	add_compile_definitions(USE_LOGGER=$ENV{USE_LOGGER})
endif()

if (DEFINED ENV{USE_SOCKET_CLIENT} OR USE_SOCKET_CLIENT)
	add_compile_definitions(USE_SOCKET_CLIENT=$ENV{USE_SOCKET_CLIENT})
endif()

if (DEFINED ENV{USE_INPUT} OR USE_INPUT)
	add_compile_definitions(USE_INPUT=$ENV{USE_INPUT})
endif()

if (DEFINED ENV{SKIP_INIT} OR SKIP_INIT)
	add_compile_definitions(SKIP_INIT=$ENV{SKIP_INIT})
endif()

if (DEFINED ENV{TESTING} OR TESTING)
	add_compile_definitions(TESTING=$ENV{TESTING})
endif()

# Sensors

if (DEFINED ENV{USE_SBG} OR USE_SBG)
	add_compile_definitions(USE_SBG=$ENV{USE_SBG})
endif()

if (DEFINED ENV{USE_RADIO} OR USE_RADIO)
	add_compile_definitions(USE_RADIO=$ENV{USE_RADIO})
endif()

if (DEFINED ENV{USE_WIRING_Pi} OR USE_WIRING_Pi)
	add_compile_definitions(USE_WIRING_Pi=$ENV{USE_WIRING_Pi})
endif()

if (DEFINED ENV{USE_GPIO} OR USE_GPIO)
	add_compile_definitions(USE_GPIO=$ENV{USE_GPIO})
endif()

# ---------------
# Main executable
# ---------------
find_package (Threads)

if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
	file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/HotFire/*.cpp)
else()
	file(GLOB_RECURSE MAIN_CONFIG_SRC ${PROJECT_SOURCE_DIR}/projects/OctoberSky1/*.cpp)
endif()

file(GLOB_RECURSE SRC_MAIN ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(MainLoopLib ${SRC_MAIN} ${MAIN_CONFIG_SRC})

target_include_directories(MainLoopLib PUBLIC ./src/)

if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
	target_include_directories(MainLoopLib PUBLIC
			./projects/HotFire/
	)
else()
	target_include_directories(MainLoopLib PUBLIC
			./projects/OctoberSky1/
	)
endif()

target_link_libraries(MainLoopLib sbgECom)
add_dependencies(MainLoopLib sbgECom)

target_link_libraries(MainLoopLib WiringPi)
add_dependencies(MainLoopLib WiringPi)

target_link_libraries(MainLoopLib stdc++fs)

target_link_libraries (MainLoopLib ${CMAKE_THREAD_LIBS_INIT})

add_executable(MainLoop ./src/init/MainLoop.cpp)
target_link_libraries(MainLoop MainLoopLib)


add_subdirectory(./unitTesting)
