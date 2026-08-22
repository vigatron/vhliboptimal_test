message(STATUS "Configuring for native build with Qt6")


add_executable(${PROJECT_NAME}
    src/appnative/main.cpp

    src/globalmods/timer/vhtimerstamp.cpp
    src/globalmods/pics/srcimgdata.cpp
    src/globalmods/sysinfo/sysinfo.cpp
    
    src/appnative/mods/iface/iface_log.cpp
    src/globalmods/testcontainer/testcontainer.cpp
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
    vhlib_platform
    vhlib_rle7b
    vhlib_optimal
)

# Application Settings
target_compile_definitions(${PROJECT_NAME} PRIVATE
    VHPLATFORM_PC
    APP_VERSION_SUFFIX="${APP_VERSION_SUFFIX_STR}"
    VHLIBOPTIMAL_TEST_PASS_COUNT=16
    VHLIBOPTIMAL_TEST_FLTVAL=200
    VHLIBOPTIMAL_TEST_EMBEDDEDBMPID=1
    SAVE_RESULTS=1
)
