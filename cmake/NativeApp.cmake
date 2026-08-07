message(STATUS "Configuring for native build with Qt6")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)


add_executable(${PROJECT_NAME}
    src/appnative/main.cpp
    src/appnative/setup.cpp
    src/appnative/report.cpp
    src/appnative/mods/args/vhargs.cpp
    src/appnative/mods/benchmark/benchmark.cpp
    src/appnative/mods/bmpbw.cpp
    src/appnative/mods/iface/iface.cpp
    src/appnative/mods/iface/iface_log.cpp
    src/pics/srcdata.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src/appnative
    src/appnative/mods
    src/appnative/mods/iface
    src/appnative/mods/args
    src/appnative/mods/benchmark
    src/appnative/extmods
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Gui
    vhlib_platform
    vhlib_optimal
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SAVE_RESULTS=1)

# add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
# 	COMMAND cp "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}" "$ENV{HOME}/bin/${CMAKE_PROJECT_NAME}" )

# List all flags
# gcc -march=native -v -E - < /dev/null 2>&1 | grep cc1
