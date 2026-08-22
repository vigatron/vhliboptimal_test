
idf_component_register(
    SRCS 
        "mainesp32.cpp"
        ${CMAKE_SOURCE_DIR}/../../src/globalmods/timer/vhtimerstamp.cpp
        ${CMAKE_SOURCE_DIR}/../../src/globalmods/pics/srcimgdata.cpp
        ${CMAKE_SOURCE_DIR}/../../src/globalmods/sysinfo/sysinfo.cpp
        ${CMAKE_SOURCE_DIR}/../../src/globalmods/testcontainer/testcontainer.cpp

    INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}

        ${CMAKE_SOURCE_DIR}/../extmods

        ${CMAKE_SOURCE_DIR}/../extmods/vhlibplatform/src
        ${CMAKE_SOURCE_DIR}/../extmods/vhlibrle7b/src
        ${CMAKE_SOURCE_DIR}/../extmods/vhliboptimal/src

        ${CMAKE_SOURCE_DIR}/../globalmods

        ${CMAKE_BINARY_DIR}
)

target_compile_definitions(${COMPONENT_LIB} PRIVATE 
    VHLIBOPTIMAL_TEST_PASS_COUNT=16
)

