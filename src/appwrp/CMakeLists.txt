cmake_minimum_required(version 3.14)

project(APPWRP_MODULE VERSION 1.0.0)

# Add IoWrp module if enabled
if (IOWRP STREQUAL "ENABLE" OR IOWRP)
    add_subdirectory(IoWrp)
endif()

# Add VRM module
add_subdirectory(VRM)