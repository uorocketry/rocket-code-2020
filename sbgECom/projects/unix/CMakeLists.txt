cmake_minimum_required(VERSION 3.0)

project(sbgECom)

include_directories(
	${PROJECT_SOURCE_DIR}/../../src/
	${PROJECT_SOURCE_DIR}/../../common/
)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin/)

file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/../../src/*.c)
file(GLOB_RECURSE COMMON_SRC ${PROJECT_SOURCE_DIR}/../../common/*.c)

#
#	Exclude platform specific files
#
if (NOT MSVC)
	list(REMOVE_ITEM COMMON_SRC "${PROJECT_SOURCE_DIR}/../../common/interfaces/sbgInterfaceSerialWin.c")
else ()
	list(REMOVE_ITEM COMMON_SRC "${PROJECT_SOURCE_DIR}/../../common/interfaces/sbgInterfaceSerialUnix.c")
endif()

add_library(sbgECom STATIC ${SRC} ${COMMON_SRC})

if (MSVC)
	target_link_libraries(sbgECom Ws2_32)
endif()

add_executable(ellipseMinimal "${PROJECT_SOURCE_DIR}/../../examples/ellipseMinimal/src/ellipseMinimal.c")
target_link_libraries(ellipseMinimal sbgECom)
add_dependencies(ellipseMinimal sbgECom)

add_executable(ekinoxMinimal "${PROJECT_SOURCE_DIR}/../../examples/ekinoxMinimal/src/ekinoxMinimal.c")
target_link_libraries(ekinoxMinimal sbgECom)
add_dependencies(ekinoxMinimal sbgECom)

add_executable(ellipseOnboardMagCalib "${PROJECT_SOURCE_DIR}/../../examples/ellipseOnboardMagCalib/src/ellipseOnboardMagCalib.c")
target_link_libraries(ellipseOnboardMagCalib sbgECom)
add_dependencies(ellipseOnboardMagCalib sbgECom)
