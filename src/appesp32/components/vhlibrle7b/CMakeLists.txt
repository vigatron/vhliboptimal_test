idf_component_register(
    # INCLUDE_DIRS
    #     ${CMAKE_BINARY_DIR}/extmods/vhlibrle7b/generated
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../extmods/vhlibrle7b
    ${CMAKE_BINARY_DIR}/extmods/vhlibrle7b
)

target_link_libraries(${COMPONENT_LIB} INTERFACE vhlib_rle7b)
