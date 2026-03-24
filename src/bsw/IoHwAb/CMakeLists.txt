cmake_minimum_required(VERSION 3.24)


# Add all IoHwAb sub-modules
add_subdirectory(IoHwAb_AnalogIn)
add_subdirectory(IoHwAb_DigitalIn)
add_subdirectory(IoHwAb_DigitalOut)
add_subdirectory(IoHwAb_PwmCap)
add_subdirectory(IoHwAb_PwmOut)
#add_subdirectory(IoHwAb_Motor)
add_subdirectory(AdcIf)
add_subdirectory(DioIf)
add_subdirectory(PwmIf)
# add_subdirectory(HbIf)
