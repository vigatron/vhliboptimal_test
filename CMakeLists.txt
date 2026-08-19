cmake_minimum_required(VERSION 3.22)

# Варианты таргетов
set(ALLOWED_TARGETS "native" "CMB32F407HDM" "STM32F4DISCOVERY" "WAVESHARECORE7XXI" "CMB32H750HDM")
set(BUILD_TARGET "native" CACHE STRING "Select target: ${ALLOWED_TARGETS}")
set_property(CACHE BUILD_TARGET PROPERTY STRINGS ${ALLOWED_TARGETS})

project(test_lib_optimal VERSION 0.0.5 LANGUAGES C CXX ASM)

set(APP_VERSION_SUFFIX "-beta")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version_vhliboptimal_test.h"
)

# Подключение скриптов таргетов
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Подключаем модули библиотеки
add_subdirectory(src/extmods/vhlibplatform)
add_subdirectory(src/extmods/vhliboptimal)
add_subdirectory(src/extmods/vhlibrle7b)


# ------------------------------------------------------------
# VHLIBOptimal Related
# (объявляем общие дефайны, которые не зависят от таргета)
# ------------------------------------------------------------

set(VHLIB_OPTIMAL_DEFS

    VHLIB_OPTIMAL_PREFIX="beta"

    VHLIB_OPTIMAL_STL=0
    VHLIB_OPTIMAL_OBJS_MAX=800
    VHLIB_OPTIMAL_SPNS_MAX=10000

    # Embedded version
    VHLIB_OPTIMAL_STL=0

    # ------------------------------------------------------------
    # FIXED GRID Option
    # 7:128 / 8:256 / 9: 512 / 10: 1024 / 11: 2048 / 12: 4096 pxls
    # ------------------------------------------------------------
    VHLIB_OPTIMAL_GRID_FIXED

    # 9: 512x512 : 32K Grid : LEVELCS=0
    VHLIB_OPTIMAL_GRID_LX=9       # 512
    VHLIB_OPTIMAL_GRID_LY=9       # 512

    # # 8: 256x256 :  8K Grid : LEVELCS=1
    # VHLIB_OPTIMAL_GRID_LX=8     # 256
    # VHLIB_OPTIMAL_GRID_LY=8     # 256

    # # 7: 128x128 :  2K Grid : LEVELCS=2
    # VHLIB_OPTIMAL_GRID_LX=7     # 128
    # VHLIB_OPTIMAL_GRID_LY=7     # 128

    VHLIB_OPTIMAL_LOG_LEVEL=1
    # VHLIB_OPTIMAL_DEBUG

)



# 2. Наполняем специфичные для платформ флаги кэша
if(BUILD_TARGET STREQUAL "native")
    # Для ПК обычно эти секции не нужны, можно оставить пустым или задать свои

# *** STM32F407
elseif(BUILD_TARGET STREQUAL "CMB32F407HDM" OR BUILD_TARGET STREQUAL "STM32F4DISCOVERY")
    list(APPEND VHLIB_OPTIMAL_DEFS 
        # VHLIB_OPTIMAL_USE_ICACHE="ramfunc"
        VHLIB_OPTIMAL_USE_DCACHE=".ccmram"
    )

# *** STM32F746
elseif(BUILD_TARGET STREQUAL "WAVESHARECORE7XXI")
    list(APPEND VHLIB_OPTIMAL_DEFS
        # VHLIB_OPTIMAL_USE_ICACHE=".itcm_text"
        VHLIB_OPTIMAL_USE_DCACHE=".dtcm_bss"
    )

# *** STM32H750
elseif(BUILD_TARGET STREQUAL "CMB32H750HDM")
    list(APPEND VHLIB_OPTIMAL_DEFS
        # VHLIB_OPTIMAL_USE_ICACHE=".itcm_text"
        VHLIB_OPTIMAL_USE_DCACHE=".dtcm_bss"
    )
else()
    message(WARNING "Unknown BUILD_TARGET: ${BUILD_TARGET}. Cache settings not applied.")
endif()


# ----------------------------------------------
target_compile_definitions(vhlib_optimal PUBLIC ${VHLIB_OPTIMAL_DEFS} )

#
if(BUILD_TARGET STREQUAL "native")
    include(NativeApp)
else()
    include(STM32BoardConfig)
    include(STM32App)
endif()
