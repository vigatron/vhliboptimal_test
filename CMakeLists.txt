cmake_minimum_required(VERSION 3.16)

set(CMAKE_PROJECT_NAME test_lib_optimal)

project(${CMAKE_PROJECT_NAME} VERSION 0.0.5 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED Core Widgets Gui)

add_compile_definitions(SAVE_RESULTS=1)

add_subdirectory(src/extmods/vhlibplatform)
add_subdirectory(src/extmods/vhliboptimal)

# ----------------------------------------------
# MAIN APP
# ----------------------------------------------
include_directories(
    src
    src/mods
    src/mods/iface
    src/mods/args
    src/mods/benchmark
    src/extmods
)

# ----------------------------------------------
file(GLOB_RECURSE source_list_mods
    src/*
    src/mods/*
    src/mods/iface/*
)

# ----------------------------------------------
add_executable(${CMAKE_PROJECT_NAME} ${source_list_mods}
    src/mods/args/vhargs.cpp
    src/mods/benchmark/benchmark.cpp
    src/mods/bmpbw.cpp
    src/pics/srcdata.cpp
)

# ----------------------------------------------
target_link_libraries( ${CMAKE_PROJECT_NAME} PUBLIC
    Qt6::Core Qt6::Widgets Qt6::Gui
    vhlib_platform
    vhlib_optimal
)

# ----------------------------------------------
target_compile_definitions(vhlib_optimal PUBLIC

    # Uncomment for .jpg > .bmp (1-bit) conversion
    # VHAPP_OPTIMAL_TEST_CONVERT_BMP

    # Application Settings
    VHAPP_OPTIMAL_TEST_PASS_COUNT=16

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
    VHLIB_OPTIMAL_GRID_LX=9
    VHLIB_OPTIMAL_GRID_LY=9

    VHLIB_OPTIMAL_OBJS_MAX=128
    VHLIB_OPTIMAL_SPNS_MAX=8192

    VHLIB_OPTIMAL_LOG_LEVEL=1

    # VHLIB_OPTIMAL_DEBUG
)


# add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
# 	COMMAND cp "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}" "$ENV{HOME}/bin/${CMAKE_PROJECT_NAME}" )
