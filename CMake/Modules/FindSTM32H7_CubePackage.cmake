#
# Copyright (c) .NET Foundation and Contributors
# See LICENSE file in the project root for full license information.
#

include(FetchContent)
FetchContent_GetProperties(stm32h7_hal_driver)
FetchContent_GetProperties(cmsis_device_h7)
FetchContent_GetProperties(cmsis_core)

if(RTOS_AZURERTOS_CHECK)
    FetchContent_GetProperties(azrtos_xcube_h7)
endif()

# set include directories
list(APPEND STM32H7_CubePackage_INCLUDE_DIRS ${cmsis_device_h7_SOURCE_DIR}/Include)
list(APPEND STM32H7_CubePackage_INCLUDE_DIRS ${stm32h7_hal_driver_SOURCE_DIR}/Inc)
list(APPEND STM32H7_CubePackage_INCLUDE_DIRS ${cmsis_core_SOURCE_DIR}/Include)
list(APPEND STM32H7_CubePackage_INCLUDE_DIRS ${TARGET_BASE_LOCATION})
list(APPEND STM32H7_CubePackage_INCLUDE_DIRS ${TARGET_BASE_LOCATION}/common)

# includes for AZRTOS X-Cube
if(RTOS_AZURERTOS_CHECK)
    list(APPEND STM32H7_CubePackage_INCLUDE_DIRS ${azrtos_xcube_h7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers)
    list(APPEND STM32H7_CubePackage_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/ST/_common/usbx)
endif()

# source files
set(STM32H7_CubePackage_SRCS

    system_stm32h7xx.c

    # add HAL files here as required
    stm32h7xx_hal.c
    stm32h7xx_hal_rcc.c
    stm32h7xx_hal_rcc_ex.c

    stm32h7xx_hal_cortex.c
    stm32h7xx_hal_gpio.c
    stm32h7xx_hal_pwr_ex.c
    stm32h7xx_hal_tim.c
    stm32h7xx_ll_fmc.c
    stm32h7xx_hal_sdram.c
    stm32h7xx_hal_wwdg.c
    stm32h7xx_hal_flash.c
    stm32h7xx_hal_flash_ex.c

    stm32h7xx_hal_dma.c
    stm32h7xx_hal_qspi.c

    target_hal_gpio.c

    # AZRTOS X-Cube )

)

# add AZRTOS X-Cube files
if(RTOS_AZURERTOS_CHECK)

    if(HAL_WP_USE_USB_CDC)
        
        # HAL
        list(APPEND STM32H7_CubePackage_SRCS stm32h7xx_hal_pcd.c)
        list(APPEND STM32H7_CubePackage_SRCS stm32h7xx_hal_pcd_ex.c)
        list(APPEND STM32H7_CubePackage_SRCS stm32h7xx_ll_usb.c)
       
        # X-Cube
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_callback.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_endpoint_create.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_endpoint_destroy.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_endpoint_reset.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_endpoint_stall.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_endpoint_status.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_frame_number_get.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_function.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_initialize_complete.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_initialize.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_interrupt_handler.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_transfer_abort.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_transfer_request.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_transfer_run.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_dcd_stm32_uninitialize.c)

        list(APPEND STM32H7_CubePackage_SRCS ux_device_cdc_acm.c)
        list(APPEND STM32H7_CubePackage_SRCS ux_device_descriptors.c)
        list(APPEND STM32H7_CubePackage_SRCS usb_otg.c)
        list(APPEND STM32H7_CubePackage_SRCS nf_usbx.c)
       
        # add exception to compiler warnings as errors
        SET_SOURCE_FILES_PROPERTIES(${azrtos_xcube_h7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_callback.c PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)
        SET_SOURCE_FILES_PROPERTIES(${azrtos_xcube_h7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_frame_number_get.c PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)

    endif()

endif()

foreach(SRC_FILE ${STM32H7_CubePackage_SRCS})

    set(STM32H7_CubePackage_SRC_FILE SRC_FILE-NOTFOUND)

    find_file(STM32H7_CubePackage_SRC_FILE ${SRC_FILE}
        PATHS 

        ${TARGET_BASE_LOCATION}/common/CubeMX
        ${TARGET_BASE_LOCATION}/common
        ${stm32h7_hal_driver_SOURCE_DIR}/Src
        
        ${azrtos_xcube_h7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers

        ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/ST/_common/usbx

        CMAKE_FIND_ROOT_PATH_BOTH
    )

    if (BUILD_VERBOSE)
        message("${SRC_FILE} >> ${STM32H7_CubePackage_SRC_FILE}")
    endif()

    list(APPEND STM32H7_CubePackage_SOURCES ${STM32H7_CubePackage_SRC_FILE})
    
endforeach()

set_source_files_properties(${stm32h7_hal_driver_SOURCE_DIR}/Src/stm32h7xx_hal_flash.c PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)

list(REMOVE_DUPLICATES STM32H7_CubePackage_INCLUDE_DIRS)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(STM32H7_CubePackage DEFAULT_MSG STM32H7_CubePackage_INCLUDE_DIRS STM32H7_CubePackage_SOURCES)
