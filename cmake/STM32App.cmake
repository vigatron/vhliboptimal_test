# Ищем системные файлы C и драйверы HAL для конкретного семейства

message(STATUS "CUBEMX_PATH: ${CUBEMX_PATH}")
message(STATUS "STM32_CORE_FILES: ${STM32_CORE_FILES}")


set(TARGET_ELF "${PROJECT_NAME}_${BUILD_TARGET}.elf")

add_executable(${TARGET_ELF}
    ${STARTUP_FILE}
    ${STM32_CORE_FILES}
    ${HAL_DRIVERS_FILES}
    ${USB_User_Src}
    ${USB_Device_Library_Src}
    ${FreeRTOS_Src}

    ${APP_STM32_DIR}/emain.cpp
    ${APP_STM32_DIR}/task_def.cpp
    ${APP_STM32_DIR}/task_usb.cpp
    ${APP_STM32_DIR}/sysvcp.cpp
    ${APP_STM32_DIR}/global.cpp
    ${APP_STM32_DIR}/detector.cpp
    ${APP_STM32_DIR}/callbacks/callbacks.cpp

    src/pics/srcimgdata.cpp
)


target_include_directories(${TARGET_ELF} PRIVATE
    ${APP_STM32_DIR}
    ${APP_STM32_DIR}/classes
    ${HAL_DRIVER_DIR}/Inc
    ${HAL_DRIVER_DIR}/Inc/Legacy

    ${APP_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_ELF} PRIVATE
    vhlib_optimal
)

target_compile_definitions(${TARGET_ELF} PRIVATE
    BUILD_TARGET_NAME=${BUILD_TARGET}
    TARGET_${BUILD_TARGET}
    HSE_VALUE=${HSE_VALUE}
    ${MCU_DEF}
    USE_HAL_DRIVER
)

# --- Выбор команды прошивки по молчанию для каждого таргета ---
if(BUILD_TARGET STREQUAL "CMB32F407HDM")
    set(FLASH_COMMAND dfu-util -a 0 -s 0x08000000:leave -D ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${BUILD_TARGET}.bin)
    set(FLASH_COMMENT "Auto-flashing ${BUILD_TARGET} via DFU")
elseif(BUILD_TARGET STREQUAL "STM32F4DISCOVERY")
    set(FLASH_COMMAND st-flash --reset write ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${BUILD_TARGET}.bin 0x08000000)
    set(FLASH_COMMENT "Auto-flashing ${BUILD_TARGET} via ST-Link")
elseif(BUILD_TARGET STREQUAL "WAVESHARECORE7XXI")
    set(FLASH_COMMAND dfu-util -a 0 -s 0x08000000:leave -D ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${BUILD_TARGET}.bin)
    set(FLASH_COMMENT "Auto-flashing ${BUILD_TARGET} via DFU")
elseif(BUILD_TARGET STREQUAL "CMB32H750HDM")
    set(FLASH_COMMAND dfu-util -a 0 -s 0x08000000:leave -D ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${BUILD_TARGET}.bin)
    set(FLASH_COMMENT "Auto-flashing ${BUILD_TARGET} via DFU")
else()
    set(FLASH_COMMAND st-flash --reset write ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${BUILD_TARGET}.bin 0x08000000)
    set(FLASH_COMMENT "Auto-flashing ${BUILD_TARGET} via ST-Link")
endif()


# Генерация бинарников
add_custom_command(TARGET ${TARGET_ELF} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET_ELF}> ${PROJECT_NAME}_${BUILD_TARGET}.bin
    COMMAND ${CMAKE_OBJDUMP} -h -S $<TARGET_FILE:${TARGET_ELF}> > ${PROJECT_NAME}_${BUILD_TARGET}.lst
    
    COMMENT "Building image and flashing for ${BUILD_TARGET} (${MCU_DEF}, HSE=${HSE_VALUE}Hz)"
    COMMAND ${FLASH_COMMAND}
    COMMENT "${FLASH_COMMENT}"
)

# Прошивка через DFU (.bin файл)
add_custom_target(flash_dfu
    COMMAND dfu-util -a 0 -s 0x08000000:leave -D ${PROJECT_NAME}_${BUILD_TARGET}.bin
    DEPENDS ${TARGET_ELF}
    COMMENT "Flashing ${BUILD_TARGET} via DFU"
)

# Прошивка через ST-Link (.bin файл)
add_custom_target(flash_stlink
    COMMAND st-flash --reset write ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${BUILD_TARGET}.bin 0x08000000
    DEPENDS ${TARGET_ELF}
    COMMENT "Flashing ${BUILD_TARGET} via ST-Link"
    VERBATIM
)