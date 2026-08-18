# Кросс-компиляция под ARM Cortex-M
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER    ${TOOLCHAIN_PATH}arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER  ${TOOLCHAIN_PATH}arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  ${TOOLCHAIN_PATH}arm-none-eabi-gcc)
set(CMAKE_OBJCOPY       ${TOOLCHAIN_PATH}arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP       ${TOOLCHAIN_PATH}arm-none-eabi-objdump)

# Cube Folder
set(CMAKE_CXX_STANDARD 17)

# Важно: отключаем проверку запуска тестового бинаря
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 1. Общие флаги архитектуры и платформы (для C и C++)
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(MCU_FAMILY "STM32F4")
set(MCU_DEF "STM32F407xx")
set(VHDEFS "-D${MCU_FAMILY} -D${MCU_DEF} -DUSE_HAL_DRIVER")

# 2. Общие базовые флаги C и C++
set(CMAKE_C_FLAGS "${TARGET_FLAGS} -Wall -fdata-sections -ffunction-sections -fstack-usage" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${TARGET_FLAGS} -Wall -fdata-sections -ffunction-sections -fstack-usage -fno-rtti -fno-exceptions -fno-threadsafe-statics" CACHE STRING "" FORCE)

# 3. Флаги специфичные для типов сборок (Debug / Release)
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-Os -g0" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g0 -flto -ffast-math -fsingle-precision-constant -fomit-frame-pointer -fno-common -fdevirtualize-at-ltrans -fvisibility-inlines-hidden" CACHE STRING "" FORCE)

# 4. Проверка (выведет актуальные значения)
message(STATUS "Base CXX Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Release CXX Flags: ${CMAKE_CXX_FLAGS_RELEASE}")

set(VH_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_EXE_LINKER_FLAGS "${TARGET_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/src/appstm32/platformstm32f407/STM32F407xx_FLASH.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")

#
set(TOOLCHAIN_LINK_LIBRARIES "m")
