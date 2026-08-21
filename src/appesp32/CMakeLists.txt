# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(appesp32)

# 1. Задаем версию в явном виде
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 5)

# === FLAGS ===

# 1. Забираем флаги из CMAKE_CXX_FLAGS и из свойств сборки ESP-IDF
idf_build_get_property(IDF_COMPILE_OPTIONS COMPILE_OPTIONS)
set(RAW_ALL_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} ${IDF_COMPILE_OPTIONS}")

# 2. Фильтруем: оставляем только флаги на -O, -f, -g, -W, -m
string(REGEX MATCHALL "(^| )[ -]-(O|f|g|W|m)[^ ;]*" MATCHED_FLAGS "${RAW_ALL_FLAGS}")

# 3. Чистим полученный список
string(REPLACE ";" " " VH_CXX_FLAGS "${MATCHED_FLAGS}")
string(REGEX REPLACE "[ \t]+" " " VH_CXX_FLAGS "${VH_CXX_FLAGS}")
string(STRIP "${VH_CXX_FLAGS}" VH_CXX_FLAGS)

message(STATUS "VH_CXX_FLAGS: ${VH_CXX_FLAGS}")

# configure_file(
#     "${CMAKE_CURRENT_SOURCE_DIR}/../../version.h.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/generated/version_vhliboptimal_test.h"
#     @ONLY
# )

# Глобальный дефайн для всего проекта
add_compile_definitions(
    VHPLATFORM_ESP32
    CMAKE_CXX_FLAGS_STR="${VH_CXX_FLAGS}"
    VHAPP_VHLIBOPTIMAL_TEST_VERSION_MAJOR=0
    VHAPP_VHLIBOPTIMAL_TEST_VERSION_MINOR=0
    VHAPP_VHLIBOPTIMAL_TEST_VERSION_PATCH=5
)


idf_build_set_property(COMPILE_DEFINITIONS VHPLATFORM_ESP32 APPEND)

# Отключаем warning глобально для всех файлов проекта
add_compile_options("-Wno-ignored-qualifiers")

set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/components/vhlibplatform
    ${CMAKE_CURRENT_SOURCE_DIR}/components/vhlibrle7b
    ${CMAKE_CURRENT_SOURCE_DIR}/components/vhliboptimal
)
