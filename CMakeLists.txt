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

# # Объединяем глобальные флаги
# string(JOIN " " MY_ALL_FLAGS
#     "${CMAKE_CXX_FLAGS}"
#     "${CMAKE_CXX_FLAGS_DEBUG}"
# )

# ----------------------------------------------
target_compile_definitions(vhlib_optimal PUBLIC

    # ------------------------------------------------------------
    # VHLIBOptimal Related
    # ------------------------------------------------------------
    VHLIB_OPTIMAL_PREFIX="beta"
    # Embedded version
    # VHLIB_OPTIMAL_EMBEDDED
    VHLIB_OPTIMAL_STL=0

    VHLIB_OPTIMAL_OBJS_MAX=800
    VHLIB_OPTIMAL_SPNS_MAX=10000

    # ------------------------------------------------------------
    # FIXED GRID Option
    # 7:128 / 8:256 / 9: 512 / 10: 1024 / 11: 2048 / 12: 4096 pxls
    # ------------------------------------------------------------
    VHLIB_OPTIMAL_GRID_FIXED

    # # 9: 512x512 : 32K Grid : LEVELCS=0
    # VHLIB_OPTIMAL_GRID_LX=9       # 512
    # VHLIB_OPTIMAL_GRID_LY=9       # 512

    # # 8: 256x256 :  8K Grid : LEVELCS=1
    # VHLIB_OPTIMAL_GRID_LX=8     # 256
    # VHLIB_OPTIMAL_GRID_LY=8     # 256

    # # 7: 128x128 :  2K Grid : LEVELCS=2
    # VHLIB_OPTIMAL_GRID_LX=7     # 128
    # VHLIB_OPTIMAL_GRID_LY=7     # 128

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
