#
# Copyright (c) .NET Foundation and Contributors
# See LICENSE file in the project root for full license information.
#

include(FetchContent)
FetchContent_GetProperties(stm32f7_hal_driver)
FetchContent_GetProperties(cmsis_device_f7)
FetchContent_GetProperties(cmsis_core)

if(RTOS_AZURERTOS_CHECK)
    FetchContent_GetProperties(azrtos_xcube_f7)
endif()

# set include directories
list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${cmsis_device_f7_SOURCE_DIR}/Include)
list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${stm32f7_hal_driver_SOURCE_DIR}/Inc)
list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${cmsis_core_SOURCE_DIR}/Include)
list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${TARGET_BASE_LOCATION})
list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${TARGET_BASE_LOCATION}/common)

# includes for AZRTOS X-Cube
if(RTOS_AZURERTOS_CHECK)
    list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${azrtos_xcube_f7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers)
    list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/ST/_common/usbx)
endif()

# source files
set(STM32F7_CubePackage_SRCS

    startup_stm32f769nihx.s
    
    system_stm32f7xx.c

    # add HAL files here as required
    stm32f7xx_hal.c
    stm32f7xx_hal_rcc.c
    stm32f7xx_hal_rcc_ex.c

    stm32f7xx_hal_cortex.c
    stm32f7xx_hal_msp.c
    stm32f7xx_hal_gpio.c
    stm32f7xx_hal_pwr_ex.c
    stm32f7xx_hal_tim.c

    stm32f7xx_hal_dma.c
    stm32f7xx_hal_qspi.c

    stm32f7xx_hal_msp.c
    target_hal_gpio.c

    # AZRTOS X-Cube 
    

)

# add exception to compiler warnings as errors
SET_SOURCE_FILES_PROPERTIES(${stm32f7_hal_driver_SOURCE_DIR}/Src/stm32f7xx_hal_eth.c PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)

# add AZRTOS X-Cube files
if(RTOS_AZURERTOS_CHECK)

    if(USBX_FEATURE_CDC)
        
        # HAL
        list(APPEND STM32F7_CubePackage_SRCS stm32f7xx_hal_pcd.c)
        list(APPEND STM32F7_CubePackage_SRCS stm32f7xx_hal_pcd_ex.c)
        list(APPEND STM32F7_CubePackage_SRCS stm32f7xx_ll_usb.c)
       
        # X-Cube
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_callback.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_endpoint_create.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_endpoint_destroy.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_endpoint_reset.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_endpoint_stall.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_endpoint_status.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_frame_number_get.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_function.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_initialize_complete.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_initialize.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_interrupt_handler.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_transfer_abort.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_transfer_request.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_transfer_run.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_dcd_stm32_uninitialize.c)

        list(APPEND STM32F7_CubePackage_SRCS ux_device_cdc_acm.c)
        list(APPEND STM32F7_CubePackage_SRCS ux_device_descriptors.c)
        list(APPEND STM32F7_CubePackage_SRCS usb_otg.c)
       
        # add exception to compiler warnings as errors
        SET_SOURCE_FILES_PROPERTIES(${azrtos_xcube_f7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_callback.c PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)
        SET_SOURCE_FILES_PROPERTIES(${azrtos_xcube_f7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_frame_number_get.c PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)

    endif()

endif()


foreach(SRC_FILE ${STM32F7_CubePackage_SRCS})

    set(STM32F7_CubePackage_SRC_FILE SRC_FILE-NOTFOUND)

    find_file(STM32F7_CubePackage_SRC_FILE ${SRC_FILE}
        PATHS 

        ${TARGET_BASE_LOCATION}/common/CubeMX
        ${TARGET_BASE_LOCATION}/common
        ${stm32f7_hal_driver_SOURCE_DIR}/Src
        
        ${azrtos_xcube_f7_SOURCE_DIR}/Middlewares/ST/usbx/common/usbx_stm32_device_controllers

        ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/ST/_common/usbx

        CMAKE_FIND_ROOT_PATH_BOTH
    )

    if (BUILD_VERBOSE)
        message("${SRC_FILE} >> ${STM32F7_CubePackage_SRC_FILE}")
    endif()

    list(APPEND STM32F7_CubePackage_SOURCES ${STM32F7_CubePackage_SRC_FILE})
endforeach()

list(REMOVE_DUPLICATES STM32F7_CubePackage_INCLUDE_DIRS)

# remove duplicated defines that clash with ChibiOS defines (when used along with)
if(${CHIBIOS_HAL_REQUIRED})

    # set(HAL_INCLUDE_FILE ${stm32f7_hal_driver_SOURCE_DIR}/Inc/Legacy/stm32_hal_legacy.h)

    # need to read the supplied files and rename the call
    file(READ
        "${HAL_INCLUDE_FILE}"
        HAL_INCLUDE_FILE_CONTENTS)

    string(REPLACE
        "KR_KEY_"
        "KR_KEY__DUMMY_FOR_NANO_BUILD"
        HAL_INCLUDE_FILE_FINAL_CONTENTS
        "${HAL_INCLUDE_FILE_CONTENTS}")
        
    file(WRITE 
        ${HAL_INCLUDE_FILE} 
        "${HAL_INCLUDE_FILE_FINAL_CONTENTS}")

endif()
 
include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(STM32F7_CubePackage DEFAULT_MSG STM32F7_CubePackage_INCLUDE_DIRS STM32F7_CubePackage_SOURCES)
