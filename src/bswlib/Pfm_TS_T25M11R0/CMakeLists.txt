# Very important: Don't forget this line or some things are not working as expected!
# The behavior of this file depends on this!
cmake_minimum_required(VERSION 3.20)

project(Pfm
    VERSION      2.0.0
    DESCRIPTION  "CMake static file"
    LANGUAGES    C
)

list(REMOVE_ITEM EXTRA_LIBS Pfm)

#############################################################################
# Definition of Source and Header Files
#
# Notes:
# - Use PRIVATE as much as possible
# - Use PUBLIC/INTERFACE only for those files/directories which are meant
#   for consumers of this package
#############################################################################

message(STATUS "Create PUBLIC library")

# The type of the library (STATIC or SHARED) depends on the variable BUILD_SHARED_LIBS (ON or OFF)
# Note: Don't add sources here, better use target_sources()

# check if there are any source files. If not, make an interface library
add_library(Pfm)
# Define an ALIAS "<name>::<name>" so that cmake knows that "<name>::<name>" is a target
#   and not a library
# Note: Both add_library(...) lines are necessary
add_library(Pfm::Pfm ALIAS Pfm)

# Common include directories for the compiler
target_include_directories(Pfm
    PUBLIC
        # When building: then search in the package source include folder
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${TRESOS_OUTPUT_BASE_DIR}/Pfm/include>
        # When installing: search in the install include folder
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Pfm>
)

# Common source files and headers
target_sources(Pfm
    PUBLIC
        # When building: then search in the package source include folder
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/Pfm.h>
    
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Pfm.c

)
# check if there are any source files. If not, link an interface library
#add all linked libraries
target_link_libraries(Pfm PRIVATE
    ${EXTRA_LIBS}
)
#############################################################################
# Specific compile options for the target
#
# compile options can be added or removed from the compile option list of the target:
# - variables <target>_COMPILE_OPTIONS_ADD and/or <target>_COMPILE_OPTIONS_REMOVE
# shall be defined as lists of compiler flags to add or remove
# - don't forget to include generator expressions in the flags
# e.g. $<$<COMPILE_LANGUAGE:C>:-Ospeed>
#############################################################################
if(DEFINED Pfm_COMPILE_OPTIONS_REMOVE OR DEFINED Pfm_COMPILE_OPTIONS_ADD)
    get_target_property(_target_compile_flags Pfm COMPILE_OPTIONS)
    foreach(OPT ${Pfm_COMPILE_OPTIONS_REMOVE})
        list(REMOVE_ITEM _target_compile_flags ${OPT})
    endforeach()
    foreach(OPT ${Pfm_COMPILE_OPTIONS_ADD})
        list(APPEND _target_compile_flags ${OPT})
    endforeach()
    set_target_properties(Pfm PROPERTIES COMPILE_OPTIONS "${_target_compile_flags}")
endif()


#############################################################################
# Install Steps (only necessary for libraries/executables)
#############################################################################
# Define a cache variable Pfm_INSTALL_CMAKEDIR
include(GNUInstallDirs)
set(Pfm_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/Pfm"
    CACHE PATH "Path to Pfm cmake files"
)
# Only for debugging: print the directory value
message("Pfm_INSTALL_CMAKEDIR = ${Pfm_INSTALL_CMAKEDIR}")

#----------------------------------------------------------------------------
# Generate PfmTargets.cmake (which is included in PfmConfig.cmake)
#----------------------------------------------------------------------------
# Defines where to install the generated libs, executables and headers
install(TARGETS Pfm EXPORT PfmTargets)

# Generate a file "${CMAKE_INSTALL_LIBDIR}/cmake/Pfm/PfmTargets.cmake"
#   with the definitions above
install(EXPORT PfmTargets
    FILE        PfmTargets.cmake
    NAMESPACE   Pfm::
    DESTINATION ${Pfm_INSTALL_CMAKEDIR}
)

#----------------------------------------------------------------------------
# Generate PfmConfig.cmake and PfmConfigVersion.cmake
#----------------------------------------------------------------------------
include(CMakePackageConfigHelpers)
# Use "cmake/PfmConfig.cmake.in" to generate
#   "${CMAKE_CURRENT_BINARY_DIR}/PfmConfig.cmake" by replacing @var@
#   with the corresponding values
configure_package_config_file(
    cmake/PfmConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/PfmConfig.cmake
    INSTALL_DESTINATION ${Pfm_INSTALL_CMAKEDIR}
    PATH_VARS Pfm_INSTALL_CMAKEDIR
)
# Write the version to "${CMAKE_CURRENT_BINARY_DIR}/PfmConfigVersion.cmake"
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/PfmConfigVersion.cmake
    VERSION       ${Pfm_VERSION}
    COMPATIBILITY SameMajorVersion
)
# Copy the files from above to
# - ${CMAKE_INSTALL_LIBDIR}/cmake/Pfm/PfmConfig.cmake
# - ${CMAKE_INSTALL_LIBDIR}/cmake/Pfm/PfmConfigVersion.cmake
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/PfmConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/PfmConfigVersion.cmake
    DESTINATION ${Pfm_INSTALL_CMAKEDIR}
)
# Allow an extension cmake file to be included to add specific content to this file
#   from the project cmake files
# The name of the file uses the name of the folder containing this CMakeLists.txt so first
#   we must get this name
cmake_path(GET CMAKE_CURRENT_LIST_DIR STEM current_folder)
string(TOLOWER ${current_folder} current_folder)
set(cmake_extension_file
    ${CMAKE_SOURCE_DIR}/${variants_dir}/${variant}/build/${current_folder}_cmake_extension.cmake
)
if(EXISTS ${cmake_extension_file})
    include(${cmake_extension_file})
endif()
# The following line prevents the file to be modified automatically by script:
#PATCH 96e8febe-ea6f-495c-8263-ecab5c347160
