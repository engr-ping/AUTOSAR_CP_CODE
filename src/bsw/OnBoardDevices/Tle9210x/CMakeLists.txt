cmake_minimum_required(VERSION 3.24)

project(TLE9210X_DRIVER VERSION 1.0.0)

set(SOURCES )

file(GLOB_RECURSE TEMP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
list(APPEND SOURCES ${TEMP_SOURCES})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link with required libraries
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
)

# Compile definitions
target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
)