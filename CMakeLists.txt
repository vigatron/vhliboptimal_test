cmake_minimum_required(VERSION 3.22)

# Варианты таргетов
set(ALLOWED_TARGETS "native" "CMB32F407HDM" "STM32F4DISCOVERY" "WAVESHARECORE7XXI" "CMB32H750HDM")
set(BUILD_TARGET "native" CACHE STRING "Select target: ${ALLOWED_TARGETS}")
set_property(CACHE BUILD_TARGET PROPERTY STRINGS ${ALLOWED_TARGETS})

project(test_lib_optimal VERSION 0.0.5 LANGUAGES C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение скриптов таргетов
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Подключаем модули библиотеки
add_subdirectory(src/extmods/vhlibplatform)
add_subdirectory(src/extmods/vhliboptimal)

# ----------------------------------------------
target_compile_definitions(vhlib_optimal PUBLIC

    # Uncomment for .jpg > .bmp (1-bit) conversion
    # VHAPP_OPTIMAL_TEST_CONVERT_BMP

    # Application Settings
    VHAPP_OPTIMAL_TEST_PASS_COUNT=1
    VHAPP_OPTIMAL_TEST_FLTVAL=200

    # ------------------------------------------------------------
    # VHLIBOptimal Related
    # ------------------------------------------------------------

    # Embedded version
    # VHLIB_OPTIMAL_EMBEDDED
    VHLIB_OPTIMAL_STL=0

    # ------------------------------------------------------------
    # FIXED GRID Option
    # ------------------------------------------------------------
    # 7:128 / 8:256 / 9: 512 / 10: 1024 / 11: 2048 / 12: 4096 pxls
    VHLIB_OPTIMAL_GRID_FIXED
    VHLIB_OPTIMAL_GRID_LX=7
    VHLIB_OPTIMAL_GRID_LY=7

    VHLIB_OPTIMAL_OBJS_MAX=128
    VHLIB_OPTIMAL_SPNS_MAX=1024

    VHLIB_OPTIMAL_LOG_LEVEL=1

    # VHLIB_OPTIMAL_DEBUG
)

#
if(BUILD_TARGET STREQUAL "native")
    include(NativeApp)
else()
    include(BoardConfig)
    include(STM32App)
endif()
