cmake_minimum_required(VERSION 3.16)

set(CMAKE_PROJECT_NAME test_lib_optimal)

project(${CMAKE_PROJECT_NAME} VERSION 0.0.5 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED Core Widgets Gui)

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

file(GLOB_RECURSE source_list_mods
    src/*
    src/mods/*
    src/mods/iface/*
)

add_executable(${CMAKE_PROJECT_NAME} ${source_list_mods}
    src/mods/iface/iface_mem.cpp
    src/mods/args/vhargs.cpp
    src/mods/benchmark/benchmark.cpp
)

target_link_libraries( ${CMAKE_PROJECT_NAME} PUBLIC
    Qt5::Core Qt5::Widgets Qt5::Gui
    vhlib_platform
    vhlib_optimal
)

target_compile_definitions(vhlib_platform PUBLIC 
    VHLIBOPTIMAL_TEST_PASS_COUNT=16
)


# add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
# 	COMMAND cp "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}" "$ENV{HOME}/bin/${CMAKE_PROJECT_NAME}" )
