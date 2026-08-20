# gemini

# Кросс-компиляция под ARM Cortex-M
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER    ${TOOLCHAIN_PATH}arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER  ${TOOLCHAIN_PATH}arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  ${TOOLCHAIN_PATH}arm-none-eabi-gcc)
set(CMAKE_OBJCOPY       ${TOOLCHAIN_PATH}arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP       ${TOOLCHAIN_PATH}arm-none-eabi-objdump)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# MCU target flags
set(TARGET_FLAGS "-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(VH_CXX_FLAGS "-flto -ffast-math -fsingle-precision-constant -fomit-frame-pointer -fno-common -fdevirtualize-at-ltrans -fvisibility-inlines-hidden")

# Базовые флаги (через _INIT)
set(CMAKE_C_FLAGS_INIT "${TARGET_FLAGS} -Wall -fdata-sections -ffunction-sections -fstack-usage")
set(CMAKE_CXX_FLAGS_INIT "${TARGET_FLAGS} -Wall -fdata-sections -ffunction-sections ${VH_CXX_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_ASM_FLAGS_INIT "${TARGET_FLAGS} -x assembler-with-cpp -MMD -MP")

# Принудительно задаем сборки в CACHE FORCE
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-Os -g0" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g0" CACHE STRING "" FORCE)

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS_INIT "${TARGET_FLAGS} -T ${CMAKE_SOURCE_DIR}/src/appstm32/platformstm32f407/STM32F407xx_FLASH.ld --specs=nano.specs -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -Wl,--print-memory-usage")

set(TOOLCHAIN_LINK_LIBRARIES "m")
