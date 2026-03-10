cmake_minimum_required(version 3.14)

project(IOHWAB_MODULE VERSION 1.0.0)

# Add all IoHwAb sub-modules
add_subdirectory(IoHwAb_AnalogIn)
add_subdirectory(IoHwAb_DigitalIn)
add_subdirectory(IoHwAb_DigitalOut)
add_subdirectory(IoHwAb_PwmCap)
add_subdirectory(IoHwAb_PwmOut)
