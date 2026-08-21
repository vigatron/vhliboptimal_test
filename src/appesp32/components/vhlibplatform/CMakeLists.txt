idf_component_register(
    # INCLUDE_DIRS
    #     ${CMAKE_BINARY_DIR}/extmods/vhlibplatform/generated
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../extmods/vhlibplatform
    ${CMAKE_BINARY_DIR}/extmods/vhlibplatform
    # ${CMAKE_BINARY_DIR}/extmods/vhlibplatform/generated
)

target_link_libraries(${COMPONENT_LIB} INTERFACE vhlib_platform)
