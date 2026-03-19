cmake_minimum_required(VERSION 3.24)
# 必须在最开头设置
set(CMAKE_SYSTEM_NAME Generic)

# 设置安装前缀为 build 目录下的 install 文件夹
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation prefix" FORCE)

# 设置CMake模块路径
include(${CMAKE_CURRENT_SOURCE_DIR}/script/cmake/chip_toolchain.cmake)
configure_toolchain(
    COMPILER tasking
    PATH "C:/TASKING/TriCore v6.3r1/ctc"
)


project(AUTOSAR_CP_CODE VERSION 1.0.0 LANGUAGES CXX C ASM)




set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

set(CHIP "tc3xx")


# 加载自定义工具函数

include(${CMAKE_CURRENT_SOURCE_DIR}/script/cmake/compiler_options.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/script/cmake/submodule_library.cmake)

set(IOWRP ENABLE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/common)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
