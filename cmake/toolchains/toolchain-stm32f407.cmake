# Кросс-компиляция под ARM Cortex-M
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER    ${TOOLCHAIN_PATH}arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER  ${TOOLCHAIN_PATH}arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  ${TOOLCHAIN_PATH}arm-none-eabi-gcc)
set(CMAKE_OBJCOPY       ${TOOLCHAIN_PATH}arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP       ${TOOLCHAIN_PATH}arm-none-eabi-objdump)

#
set(CMAKE_CXX_STANDARD 17)

# Важно: отключаем проверку запуска тестового бинаря
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#
set(VHBASE_ARM_OPTIONS
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -Wall
    -fdata-sections
    -ffunction-sections
    -fstack-usage
)

#
add_compile_options(${VHBASE_ARM_OPTIONS})

#
add_compile_definitions(
    STM32F4
    STM32F407xx
    USE_HAL_DRIVER
)

#
add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>
)

#
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp")

# 
set(COMMON_PERF_FLAGS "-fsingle-precision-constant -fomit-frame-pointer -fno-math-errno -fno-trapping-math -fno-common")

#
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-O3 -g0 ${COMMON_PERF_FLAGS}" )

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g0 -flto ${COMMON_PERF_FLAGS} -funroll-loops -ffast-math -fdevirtualize-at-ltrans")

#
string(REPLACE ";" " " VHBASE_ARM_OPTIONS_CLEAN "${VHBASE_ARM_OPTIONS}")
set(VH_CXX_FLAGS "${VHBASE_ARM_OPTIONS_CLEAN} ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")

#
message(STATUS "Base CXX Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Release CXX Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "VH_CXX_FLAGS: ${VH_CXX_FLAGS}")

#
set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nano.specs")

#
add_link_options(
    -O3
    -flto
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -u _printf_float
    -T${CMAKE_SOURCE_DIR}/src/appstm32/platformstm32f407/STM32F407xx_FLASH.ld
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--print-memory-usage
)

#
set(TOOLCHAIN_LINK_LIBRARIES "m")
