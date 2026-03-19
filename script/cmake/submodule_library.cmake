# 定义一个统一的库创建函数
function(submodule_add_library TARGET_NAME)
    cmake_parse_arguments(
        ARG
        ""  # 布尔选项
        "TYPE;VERSION"  # 单值参数
        "SOURCES;PUBLIC_HEADERS;PRIVATE_HEADERS;DEPENDS;DEFINES"  # 多值参数
        ${ARGN}
    )
    
    # 设置默认值
    if(NOT ARG_TYPE)
        set(ARG_TYPE "STATIC")
    endif()
    
    # 创建库
    add_library(${TARGET_NAME} ${ARG_TYPE})
    
    # 添加源文件
    if(ARG_SOURCES)
        target_sources(${TARGET_NAME} PRIVATE ${ARG_SOURCES})
    endif()
    
    # 添加公共头文件（用于安装）
    if(ARG_PUBLIC_HEADERS)
        target_sources(${TARGET_NAME} PUBLIC 
            FILE_SET HEADERS 
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${ARG_PUBLIC_HEADERS}
        )
    endif()

    # 设置包含目录
    target_include_directories(${TARGET_NAME} 
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    # 添加依赖
    if(ARG_DEPENDS)
        target_link_libraries(${TARGET_NAME} PUBLIC ${ARG_DEPENDS})
    endif()
    
    # 添加编译定义
    if(ARG_DEFINES)
        target_compile_definitions(${TARGET_NAME} PRIVATE ${ARG_DEFINES})
    endif()
    
    # 设置版本
    if(ARG_VERSION)
        set_target_properties(${TARGET_NAME} PROPERTIES 
            VERSION ${ARG_VERSION}
            SOVERSION ${ARG_VERSION}
        )
    endif()
    
    # 设置输出目录
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endfunction()

# 统一的测试添加函数
function(submodule_add_test TEST_NAME TARGET_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_link_libraries(${TEST_NAME} PRIVATE ${TARGET_NAME} GTest::gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    
    # 设置测试属性
    set_target_properties(${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
    )
endfunction()

# 统一的安装配置函数
function(submodule_install_target TARGET_NAME)
    install(TARGETS ${TARGET_NAME}
        EXPORT ${TARGET_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        FILE_SET HEADERS DESTINATION include/${TARGET_NAME}
    )
    
    # 导出目标
    install(EXPORT ${TARGET_NAME}Targets
        FILE ${TARGET_NAME}Targets.cmake
        NAMESPACE AUTOSAR::
        DESTINATION lib/cmake/${TARGET_NAME}
    )
endfunction()