cmake_minimum_required(VERSION 3.0)

project(sbgECom C CXX)

include_directories(
	${PROJECT_SOURCE_DIR}/../../src/
	${PROJECT_SOURCE_DIR}/../../common/
	${PROJECT_SOURCE_DIR}/../../WiringPi/wiringPi/ # Only imports one part of wiringPi for now, other folders can be added later
)

if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
	include_directories(
		${PROJECT_SOURCE_DIR}/../../../projects/HotFire/
	)
else()
	include_directories(
		${PROJECT_SOURCE_DIR}/../../../projects/OctoberSky1/
	)
endif()


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin/)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/../../src/*.c)
file(GLOB_RECURSE COMMON_SRC ${PROJECT_SOURCE_DIR}/../../common/*.c)
file(GLOB_RECURSE WIRINGPI_SRC ${PROJECT_SOURCE_DIR}/../../WiringPi/wiringPi/*.c)


file(GLOB_RECURSE SM_SRC ${PROJECT_SOURCE_DIR}/../../src/*.cpp)
#file(GLOB_RECURSE SM_SRC ${PROJECT_SOURCE_DIR}/../../common/*.cpp)

if (DEFINED ENV{HOTFIRE_TEST} OR HOTFIRE_TEST)
	file(GLOB_RECURSE SM_CONFIG_SRC ${PROJECT_SOURCE_DIR}/../../../projects/HotFire/*.cpp)
else()
	file(GLOB_RECURSE SM_CONFIG_SRC ${PROJECT_SOURCE_DIR}/../../../projects/OctoberSky1/*.cpp)
endif()


find_package (Threads)

#
#	Exclude platform specific files
#
if (NOT MSVC)
	list(REMOVE_ITEM COMMON_SRC "${PROJECT_SOURCE_DIR}/../../common/interfaces/sbgInterfaceSerialWin.c")
else ()
	list(REMOVE_ITEM COMMON_SRC "${PROJECT_SOURCE_DIR}/../../common/interfaces/sbgInterfaceSerialUnix.c")
endif()

add_library(sbgECom STATIC ${SRC} ${COMMON_SRC} ${SM_SRC} ${SM_CONFIG_SRC})

if (MSVC)
	target_link_libraries(sbgECom Ws2_32)
endif()

# add_executable(ellipseMinimal "${PROJECT_SOURCE_DIR}/../../examples/ellipseMinimal/src/ellipseMinimal.cpp")
# target_link_libraries(ellipseMinimal sbgECom)
# add_dependencies(ellipseMinimal sbgECom)

# add_executable(test_hello "${PROJECT_SOURCE_DIR}/../../examples/ellipseMinimal/src/test_hello.cpp")
# target_link_libraries(test_hello sbgECom)
# add_dependencies(test_hello sbgECom)

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

add_executable(MainLoop "${PROJECT_SOURCE_DIR}/../../src/init/MainLoop.cpp")
target_link_libraries(MainLoop sbgECom)
add_dependencies(MainLoop sbgECom)
target_link_libraries(MainLoop stdc++fs)


# add_executable(ekinoxMinimal "${PROJECT_SOURCE_DIR}/../../examples/ekinoxMinimal/src/ekinoxMinimal.c")
# target_link_libraries(ekinoxMinimal sbgECom)
# add_dependencies(ekinoxMinimal sbgECom)

# add_executable(ellipseOnboardMagCalib "${PROJECT_SOURCE_DIR}/../../examples/ellipseOnboardMagCalib/src/ellipseOnboardMagCalib.c")
# target_link_libraries(ellipseOnboardMagCalib sbgECom)
# add_dependencies(ellipseOnboardMagCalib sbgECom)

# target_link_libraries (test_hello ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (MainLoop ${CMAKE_THREAD_LIBS_INIT})