cmake_minimum_required(VERSION 3.24)


set(MODULE_NAME DioIf)


# 在子目录的 CMakeLists.txt 中
file(GLOB LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

file(GLOB LIB_PUBLIC_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)


# 使用封装的函数创建库
submodule_add_library(${MODULE_NAME}
    TYPE STATIC
    VERSION 1.0.0
    SOURCES
        ${LIB_SOURCES}
    PUBLIC_HEADERS
        ${LIB_PUBLIC_HEADERS}
)

# 安装配置
submodule_install_target(${MODULE_NAME})