cmake_minimum_required(version 3.14)

project(ONBOARD_DEVICES_MODULE VERSION 1.0.0)

# Add all On-Board Device modules
add_subdirectory(Bjt)
add_subdirectory(Tle9210x)
add_subdirectory(Tle941xy)
add_subdirectory(Vn7x)
