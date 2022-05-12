add_library(mavlink INTERFACE)

target_include_directories(mavlink INTERFACE generated/)
target_include_directories(mavlink INTERFACE generated/common)
target_include_directories(mavlink INTERFACE generated/minimal)
target_include_directories(mavlink INTERFACE generated/uorocketry)

target_compile_options(mavlink INTERFACE -Wno-address-of-packed-member -Wno-cast-align)
