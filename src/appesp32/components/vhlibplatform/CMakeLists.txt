idf_component_register(
    INCLUDE_DIRS "."
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../extmods/vhlibplatform
    ${CMAKE_BINARY_DIR}/extmods/vhlibplatform
)

target_link_libraries(${COMPONENT_LIB} INTERFACE vhlib_platform)
