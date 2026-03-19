
# ==================== 芯片选择 ====================
# 设置 CHIP 变量: stm32f407, stm32f103, tc3xx, s32k144
# 例: set(CHIP "tc3xx")
if(NOT DEFINED CHIP)
    message(FATAL_ERROR "请先设置 CHIP 变量")
endif()

# 链接脚本路径（如果不在默认位置）
# set(LINKER_SCRIPT "自定义路径/链接脚本.ld")

# ==================== 芯片配置 ====================
if(CHIP STREQUAL "stm32f407")
    set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
    set(ARCH_DEFINES
        STM32F407xx
        STM32F407VG
        USE_HAL_DRIVER
        HSE_VALUE=8000000
    )
    if(NOT LINKER_SCRIPT)
        set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/ld/stm32f407.ld")
    endif()
    set(FLASH_ORIGIN 0x08000000)
    set(FLASH_SIZE 1024K)
    set(RAM_ORIGIN 0x20000000)
    set(RAM_SIZE 128K)

elseif(CHIP STREQUAL "stm32f103")
    set(CPU_FLAGS "-mcpu=cortex-m3 -mthumb")
    set(ARCH_DEFINES
        STM32F103xB
        USE_STDPERIPH_DRIVER
        HSE_VALUE=8000000
    )
    if(NOT LINKER_SCRIPT)
        set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/ld/stm32f103.ld")
    endif()

elseif(CHIP STREQUAL "tc3xx")
    # Tasking TC397 配置
    set(TASKING_CPU "--core=tc1.6.2 --fp-model=1 --default-near-size=0 --eabi-compliant --integer-enumeration --language=GKpvX --optimize=3 --tradeoff=0 --global-type-checking --debug-info=default")

    # 只放合法宏
    set(ARCH_DEFINES
        COMPILERCFG_EXTENSION_MCAL_FILE
        IOC_TOOL=IOC_tasking
        IOC_CPUFAMILY=IOC_TRICORE
        OS_SCHEDULING_ALGORITHM=OS_LINKED_LIST
        OS_RELEASE_SUFFIX=OS_AS403
        ATOMICS_USE_GENERIC_IMPL=1
        ATOMICS_USER_MULTICORE_CASE=0
        COM_STACK_MINIMAL
        TMEX_SWATT_TEST
        TEST_COM_SYSTEMTIME
        TEST_COM_WAIT
        MULTICORE_TESTFRAME
        ECUM_PROVIDE_LEGACY_SYMBOLIC_NAMES
    )
    if(NOT LINKER_SCRIPT)
        # set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/ld/tc397.ld")
    endif()

elseif(CHIP STREQUAL "s32k144")
    set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
    set(ARCH_DEFINES S32K144 CPU_S32K144)
    if(NOT LINKER_SCRIPT)
        set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/ld/s32k144.ld")
    endif()

else()
    message(FATAL_ERROR "未知芯片: ${CHIP}，请修改 CHIP 变量")
endif()

# ==================== 编译器相关 ====================
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(COMMON_FLAGS "${CPU_FLAGS} -ffunction-sections -fdata-sections")
    set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu11" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++17 -fno-exceptions" CACHE STRING "" FORCE)
    set(CMAKE_ASM_FLAGS "${CPU_FLAGS}" CACHE STRING "" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} -Wl,--gc-sections -T ${LINKER_SCRIPT}" CACHE STRING "" FORCE)
    set(CMAKE_C_FLAGS_DEBUG "-Og -g3" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG "-Og -g3" CACHE STRING "" FORCE)
    set(CMAKE_C_FLAGS_RELEASE "-O3" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE STRING "" FORCE)

elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(COMMON_FLAGS "${CPU_FLAGS} -ffunction-sections -fdata-sections")
    set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu11" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++17" CACHE STRING "" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} -T ${LINKER_SCRIPT}" CACHE STRING "" FORCE)

elseif(CMAKE_C_COMPILER_ID STREQUAL "Tasking")
    if(CHIP STREQUAL "tc3xx")
        set(CMAKE_C_FLAGS "${TASKING_CPU}" CACHE STRING "" FORCE)
        set(CMAKE_EXE_LINKER_FLAGS "${TASKING_CPU} -Wl-d${LINKER_SCRIPT}" CACHE STRING "" FORCE)
    else()
        set(CMAKE_C_FLAGS "--cpu=${CPU_FLAGS} --fp-model=hard" CACHE STRING "" FORCE)
        set(CMAKE_EXE_LINKER_FLAGS "--cpu=${CPU_FLAGS} -Wl-d${LINKER_SCRIPT}" CACHE STRING "" FORCE)
    endif()

elseif(CMAKE_C_COMPILER_ID STREQUAL "GHS")
    set(CMAKE_C_FLAGS "--cpu=${CPU_FLAGS} --thumb --sda=all" CACHE STRING "" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS "--cpu=${CPU_FLAGS} -L${LINKER_SCRIPT}" CACHE STRING "" FORCE)
endif()

# ==================== 添加宏 ====================
add_compile_definitions(${ARCH_DEFINES})

# ==================== 输出信息 ====================
message(STATUS "芯片配置完成")
message(STATUS "芯片:     ${CHIP}")
message(STATUS "链接脚本: ${LINKER_SCRIPT}")
message(STATUS "C标志:    ${CMAKE_C_FLAGS}")
message(STATUS "===================================")

# ==================== 辅助函数 ====================
function(add_hex_target TARGET)
    if(CMAKE_OBJCOPY)
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${TARGET}> ${TARGET}.hex
            COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET}> ${TARGET}.bin
            COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET}>
            COMMENT "生成HEX/BIN文件和查看大小"
        )
    endif()
endfunction()