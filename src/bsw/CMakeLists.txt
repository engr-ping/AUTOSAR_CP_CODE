cmake_minimum_required(VERSION 3.24)


# Add all BSW modules
add_subdirectory(AdcIf)
add_subdirectory(DioIf)
add_subdirectory(IoHwAb)
#add_subdirectory(OnBoardDevices)
add_subdirectory(Pfm)
add_subdirectory(Vrm)
add_subdirectory(PwmIf)

# Note: OhbIf is currently empty, uncomment below when it has content
# add_subdirectory(OhbIf)
