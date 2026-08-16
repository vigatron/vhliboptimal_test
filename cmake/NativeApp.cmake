message(STATUS "Configuring for native build with Qt6")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)


add_executable(${PROJECT_NAME}
    src/appnative/main.cpp

    src/appnative/mods/args/vhargs.cpp
    src/appnative/mods/benchmark/benchmark.cpp
    src/appnative/mods/bmpbw.cpp
    src/appnative/mods/iface/iface_log.cpp
    src/appnative/mods/report/report.cpp

    src/globalmods/timer/vhtimerstamp.cpp
    src/globalmods/pics/srcimgdata.cpp
    src/globalmods/testcontainer/testcontainer.cpp
    src/globalmods/sysinfo/sysinfo_pc.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE

    "${CMAKE_CURRENT_BINARY_DIR}"
    src/appnative

    src/extmods

    src/globalmods
    src/globalmods/testcontainer

    src/appnative/mods
    src/appnative/mods/iface
    src/appnative/mods/imgsrc
    src/appnative/mods/imgdst
    src/appnative/mods/args
    src/appnative/mods/benchmark
    src/appnative/extmods
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Gui
    vhlib_platform
    vhlib_rle7b
    vhlib_optimal
)

# Application Settings
target_compile_definitions(${PROJECT_NAME} PRIVATE
    VHPLATFORM_PC
    VHLIBOPTIMAL_TEST_PASS_COUNT=16
    VHAPP_OPTIMAL_TEST_FLTVAL=200
    VHLIBOPTIMAL_TEST_EMBEDDEDBMPID=1
    SAVE_RESULTS=1
)

# add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
# 	COMMAND cp "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}" "$ENV{HOME}/bin/${CMAKE_PROJECT_NAME}" )

# List all flags
# gcc -march=native -v -E - < /dev/null 2>&1 | grep cc1
