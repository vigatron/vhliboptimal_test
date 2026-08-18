# Проверяем корректность выбранной платы
if(NOT BUILD_TARGET IN_LIST ALLOWED_TARGETS)
    message(FATAL_ERROR "Unknown BUILD_TARGET: '${BUILD_TARGET}'. Allowed values: ${ALLOWED_TARGETS}")
endif()

message(STATUS "Loading target board configuration for: ${BUILD_TARGET}")

# set(CUBE_REPOSITORY_DIR     "~/STM32Cube/Repository")
set(APP_STM32_DIR           "${CMAKE_CURRENT_SOURCE_DIR}/src/appstm32")

if(BUILD_TARGET STREQUAL        "CMB32F407HDM")

    set(HSE_VALUE               "16000000")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32f4/stm32f4_common.cmake)

elseif(BUILD_TARGET STREQUAL    "STM32F4DISCOVERY")

    set(HSE_VALUE               "8000000")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32f4/stm32f4_common.cmake)

elseif(BUILD_TARGET STREQUAL    "WAVESHARECORE7XXI")

    set(HSE_VALUE               "8000000")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32f7/stm32f7_common.cmake)

elseif(BUILD_TARGET STREQUAL    "CMB32H750HDM")

    set(HSE_VALUE               "25000000")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32h7/stm32h7_common.cmake)

endif()

