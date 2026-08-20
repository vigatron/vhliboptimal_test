set(STARTUP_FILE        "${APP_STM32_DIR}/platformstm32h750/startup_stm32h750xx.s")
set(SYS_CORE_DIR        "${APP_STM32_DIR}/platformstm32h750/Core/Src")
set(HAL_DRIVER_DIR      "${CUBEMX_PATH}/Drivers/STM32H7xx_HAL_Driver")

# Includes 750 Related
set(APP_INCLUDE_DIRS

    ${APP_STM32_DIR}/platformstm32h750
    ${APP_STM32_DIR}/platformstm32h750/Core/Inc
    ${APP_STM32_DIR}/platformstm32h750/USB_DEVICE/App
    ${APP_STM32_DIR}/platformstm32h750/USB_DEVICE/Target

    ${CUBEMX_PATH}/Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ${CUBEMX_PATH}/Drivers/CMSIS/Include

    ${CUBEMX_PATH}/Drivers/CMSIS/RTOS2/Include
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/include
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1

    ${CUBEMX_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${CUBEMX_PATH}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc

)

set(USB_User_Src
    ${APP_STM32_DIR}/platformstm32h750/USB_DEVICE/Target/usbd_conf.c
    ${APP_STM32_DIR}/platformstm32h750/USB_DEVICE/App/usb_device.c
    ${APP_STM32_DIR}/platformstm32h750/USB_DEVICE/App/usbd_desc.c
    ${APP_STM32_DIR}/platformstm32h750/USB_DEVICE/App/usbd_cdc_if.c
)

# STM32 HAL/LL Drivers
set(HAL_DRIVERS_FILES
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_tim.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_tim_ex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_pcd.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_pcd_ex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_ll_usb.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_rcc.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_rcc_ex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_flash.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_flash_ex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_gpio.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_hsem.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_dma.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_dma_ex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_mdma.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_pwr.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_pwr_ex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_cortex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_i2c.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_i2c_ex.c
    ${HAL_DRIVER_DIR}/Src/stm32h7xx_hal_exti.c
)

set(USB_Device_Library_Src
    ${CUBEMX_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
    ${CUBEMX_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
    ${CUBEMX_PATH}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
    ${CUBEMX_PATH}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c
)

set(FreeRTOS_Src
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/portable/Common/mpu_wrappers_v2.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/list.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${CUBEMX_PATH}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c
)

set(STM32_CORE_FILES

    "${SYS_CORE_DIR}/freertos.c"
    "${SYS_CORE_DIR}/syscalls.c"
    "${SYS_CORE_DIR}/sysmem.c"
    "${SYS_CORE_DIR}/systemh750.cpp"

    "${SYS_CORE_DIR}/stm32h7xx_hal_msp.c"
    "${SYS_CORE_DIR}/stm32h7xx_hal_timebase_tim.c"
    "${SYS_CORE_DIR}/stm32h7xx_it.c"

    "${SYS_CORE_DIR}/system_stm32h7xx.c"

)
