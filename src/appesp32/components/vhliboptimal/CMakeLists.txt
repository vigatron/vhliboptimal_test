idf_component_register(
    INCLUDE_DIRS "."
)

set(VHLIB_OPTIMAL_DEFS

    # VHLIB_OPTIMAL_PREFIX="beta"

    VHLIB_OPTIMAL_STL=0
    VHLIB_OPTIMAL_OBJS_MAX=800
    VHLIB_OPTIMAL_SPNS_MAX=10000

    # Embedded version
    VHLIB_OPTIMAL_STL=0

    # ------------------------------------------------------------
    # FIXED GRID Option
    # 7:128 / 8:256 / 9: 512 / 10: 1024 / 11: 2048 / 12: 4096 pxls
    # ------------------------------------------------------------
    VHLIB_OPTIMAL_GRID_FIXED

    # 9: 512x512 : 32K Grid : LEVELCS=0
    VHLIB_OPTIMAL_GRID_LX=9       # 512
    VHLIB_OPTIMAL_GRID_LY=9       # 512

    # 8: 256x256 :  8K Grid : LEVELCS=1
    # VHLIB_OPTIMAL_GRID_LX=8     # 256
    # VHLIB_OPTIMAL_GRID_LY=8     # 256

    # 7: 128x128 :  2K Grid : LEVELCS=2
    # VHLIB_OPTIMAL_GRID_LX=7     # 128
    # VHLIB_OPTIMAL_GRID_LY=7     # 128

    VHLIB_OPTIMAL_LOG_LEVEL=1
    # VHLIB_OPTIMAL_DEBUG

)

#
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../extmods/vhliboptimal
    ${CMAKE_BINARY_DIR}/extmods/vhliboptimal
)

target_link_libraries(${COMPONENT_LIB} INTERFACE vhlib_optimal)

# # 1. Флаги компиляции для исходников компонента
# target_compile_options(vhlib_optimal PRIVATE -O3 -flto)

# # 2. Флаги линковки (должны передаваться в итоговый .elf / исполняемый файл)
# target_link_options(vhlib_optimal INTERFACE -O3 -flto)

# 1. Флаги компиляции для исходников компонента
target_compile_options(vhlib_optimal PRIVATE
    "-O2"
    "-flto"
    "-funroll-loops"
    "-ffast-math"
    "-fno-exceptions"
    "-fno-rtti"
)

# 2. Флаги линковки (должны передаваться в итоговый .elf / исполняемый файл)
target_link_options(vhlib_optimal INTERFACE "-flto")


# target_include_directories(${COMPONENT_LIB} INTERFACE
#     ${CMAKE_BINARY_DIR}/extmods/vhliboptimal/generated
# )

# target_compile_definitions(${COMPONENT_LIB} INTERFACE ${VHLIB_OPTIMAL_DEFS})
target_compile_definitions(vhlib_optimal PUBLIC ${VHLIB_OPTIMAL_DEFS})
