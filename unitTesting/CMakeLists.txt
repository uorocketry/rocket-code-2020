file(GLOB_RECURSE TESTING_SRC ${PROJECT_SOURCE_DIR}/unitTesting/*.cpp)

add_executable(tests ${TESTING_SRC})

target_link_libraries(tests PRIVATE Catch2::Catch2)
