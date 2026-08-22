# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(appesp32)

# 1. Задаем версию в явном виде
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 6)

# === FLAGS ===

# flags are fixed on vhliboptimal component level
set(VH_CXX_FLAGS "-O2 -flto -funroll-loops -ffast-math -fno-exceptions -fno-rtti")

message(STATUS "VH_CXX_FLAGS: ${VH_CXX_FLAGS}")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version_vhliboptimal_test.h"
    @ONLY
)

# Глобальный дефайн для всего проекта
add_compile_definitions(
    VHPLATFORM_ESP32
)

idf_build_set_property(COMPILE_DEFINITIONS VHPLATFORM_ESP32 APPEND)

set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/components/vhlibplatform
    ${CMAKE_CURRENT_SOURCE_DIR}/components/vhlibrle7b
    ${CMAKE_CURRENT_SOURCE_DIR}/components/vhliboptimal
)
