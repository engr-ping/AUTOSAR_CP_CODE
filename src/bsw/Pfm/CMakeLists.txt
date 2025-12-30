cmake_minimum_required(version 3.14)


set(PROJECT_NAME hello_world)

project(${PROJECT_NAME} VERSION 1.0.0)

set(SOURCES )

file(GLOB_RECURSE TEMP_SOURCES "${PROJECT_SOURCE_DIR}/*.c")
list(APPEND SOURCES ${TEMP_SOURCES})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
PUBLIC 
    ${PROJECT_SOURCE_DIR}
)

# add ather libraries
target_link_libraries(${PROJECT_NAME} 
PUBLIC 
    
)


# set compile opation
target_compile_definitions(${PROJECT_NAME}
    PRIVATE 

)