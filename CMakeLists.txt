cmake_minimum_required(VERSION 3.0)

project(RocketCode2020 C CXX)

add_subdirectory(./libraries)


if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
	add_definitions(-D HOTFIRE_TEST)
endif()

if (DEFINED ENV{USE_LOGGER} OR USE_LOGGER)
	add_definitions(-D USE_LOGGER)
endif()

if (DEFINED ENV{USE_SOCKET_CLIENT} OR USE_SOCKET_CLIENT)
	add_definitions(-D USE_SOCKET_CLIENT)
endif()

if (DEFINED ENV{USE_INPUT} OR USE_INPUT)
	add_definitions(-D USE_INPUT)
endif()

if (DEFINED ENV{SKIP_INIT} OR SKIP_INIT)
	add_definitions(-D SKIP_INIT)
endif()

if (DEFINED ENV{TESTING} OR TESTING)
	add_definitions(-D TESTING)
endif()

# Sensors

if (DEFINED ENV{USE_SBG} OR USE_SBG)
	add_definitions(-D USE_SBG)
endif()

if (DEFINED ENV{USE_RADIO} OR USE_RADIO)
	add_definitions(-D USE_RADIO)
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

add_executable(MainLoop ${SRC_MAIN} ${MAIN_CONFIG_SRC})

target_include_directories(MainLoop PUBLIC ./src/)

if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
	target_include_directories(MainLoop PUBLIC
			./projects/HotFire/
	)
else()
	target_include_directories(MainLoop PUBLIC
			./projects/OctoberSky1/
	)
endif()

target_link_libraries(MainLoop sbgECom)
add_dependencies(MainLoop sbgECom)

target_link_libraries(MainLoop WiringPi)
add_dependencies(MainLoop WiringPi)

target_link_libraries(MainLoop stdc++fs)

target_link_libraries (MainLoop ${CMAKE_THREAD_LIBS_INIT})

# ---------------
# Unit Testing - Catch2
# ---------------

file(GLOB_RECURSE TESTING_SRC ${PROJECT_SOURCE_DIR}/unitTesting/tests/*.cpp)

add_subdirectory(./unitTesting/Catch2)
add_executable(tests ${TESTING_SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2)
