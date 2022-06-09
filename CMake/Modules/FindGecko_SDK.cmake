#
# Copyright (c) .NET Foundation and Contributors
# See LICENSE file in the project root for full license information.
#

include(FetchContent)

# include the Gecko HAL and CMSIS for the appropriate series
FetchContent_GetProperties(gecko_sdk)

# set include directories
list(APPEND Gecko_SDK_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/SiliconLabs/_common/autogen)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${TARGET_BASE_LOCATION}/autogen)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/SiliconLabs/_common/config)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${TARGET_BASE_LOCATION}/config)

list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/hardware/kit/common/bsp)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/hardware/kit/${TARGET_BOARD_SHORT}_${TARGET_SERIES}/config)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/common/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/common/toolchain/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/hardware/board/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/CMSIS/Include)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/CMSIS/RTOS2/Include)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/service/device_init/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/emdrv/dmadrv/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/emdrv/common/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/emlib/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/emdrv/gpiointerrupt/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/service/iostream/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/service/power_manager/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/common/toolchain/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/service/system/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/service/sleeptimer/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/emdrv/uartdrv/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/service/udelay/inc)
list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/driver/i2cspm/inc)

list(APPEND Gecko_SDK_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/CLR/Include)

# general files
set(gecko_sdk_srcs
    sl_board_control_gpio.c
    sl_board_init.c

    em_acmp.c
    em_adc.c
    em_assert.c
    em_cmu.c
    em_core.c
    em_cryotimer.c
    em_csen.c
    em_emu.c
    em_ldma.c
    em_gpio.c
    em_i2c.c
    em_lcd.c
    em_leuart.c
    em_lesense.c
    em_msc.c
    em_prs.c
    em_rmu.c
    em_rtc.c
    em_rtcc.c
    em_system.c
    em_timer.c
    em_usart.c
    em_vdac.c 

    # emdrv
    dmadrv.c
    uartdrv.c
    gpiointerrupt.c

    sl_device_init_dcdc_s1.c
    sl_device_init_emu_s1.c
    sl_device_init_hfxo_s1.c
    sl_device_init_lfxo_s1.c
    sl_device_init_nvic.c 
    sl_power_manager.c
    sl_power_manager_hal_s0_s1.c
    sl_sleeptimer.c
    sl_sleeptimer_hal_rtc.c
    sl_sleeptimer_hal_rtcc.c

    sl_slist.c
    sl_system_init.c
    sl_system_kernel.c
    sl_system_process_action.c

    sl_udelay.c
    sl_udelay_armv6m_gcc.S
    sl_uartdrv_init.c
    sl_iostream_usart.c
    sl_iostream_uart.c
    sl_iostream.c
    
    sl_device_init_clocks.c
    sl_event_handler.c
    sl_board_default_init_stub.c
    sl_i2cspm_init.c
    sl_i2cspm.c
    sl_iostream_handles.c
    sl_iostream_init_usart_instances.c

    # autogen at target level
)

#series specific files and includes
if("${TARGET_SERIES}" STREQUAL "EFM32GG11")
    
    list(APPEND Gecko_SDK_INCLUDE_DIRS ${gecko_sdk_SOURCE_DIR}/platform/Device/SiliconLabs/EFM32GG11B/Include)

    list(APPEND gecko_sdk_srcs system_efm32gg11b.c)
    list(APPEND gecko_sdk_srcs startup_efm32gg11b.c)

    foreach(src_file ${gecko_sdk_srcs})

        set(gecko_sdk_src_file src_file-NOTFOUND)

        find_file(gecko_sdk_src_file ${src_file}
            PATHS 

            # common paths
            ${gecko_sdk_SOURCE_DIR}/hardware/board/src
            ${gecko_sdk_SOURCE_DIR}/platform/common/src
            ${gecko_sdk_SOURCE_DIR}/platform/common/toolchain/src
            ${gecko_sdk_SOURCE_DIR}/platform/emdrv/dmadrv/src
            ${gecko_sdk_SOURCE_DIR}/platform/emdrv/gpiointerrupt/src
            ${gecko_sdk_SOURCE_DIR}/platform/emdrv/uartdrv/src
            ${gecko_sdk_SOURCE_DIR}/platform/emlib/src
            ${gecko_sdk_SOURCE_DIR}/platform/service/device_init/src
            ${gecko_sdk_SOURCE_DIR}/platform/service/iostream/src
            ${gecko_sdk_SOURCE_DIR}/platform/service/power_manager/src
            ${gecko_sdk_SOURCE_DIR}/platform/service/sleeptimer/src
            ${gecko_sdk_SOURCE_DIR}/platform/service/system/src
            ${gecko_sdk_SOURCE_DIR}/platform/service/udelay/src
            ${gecko_sdk_SOURCE_DIR}/platform/driver/i2cspm/src
            
            # device specific paths
            ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/SiliconLabs/_common/autogen

            # target series specific 
            ${gecko_sdk_SOURCE_DIR}/platform/Device/SiliconLabs/EFM32GG11B/Source
            ${gecko_sdk_SOURCE_DIR}/platform/Device/SiliconLabs/EFM32GG11B/Source/GCC

            ${TARGET_BASE_LOCATION}/autogen
            ${TARGET_BASE_LOCATION}/config

            CMAKE_FIND_ROOT_PATH_BOTH
        )

        if (BUILD_VERBOSE)
            message("${src_file} >> ${gecko_sdk_src_file}")
        endif()

        list(APPEND Gecko_SDK_SOURCES ${gecko_sdk_src_file})
        
    endforeach()

    list(REMOVE_DUPLICATES Gecko_SDK_INCLUDE_DIRS)

else()
    # series is NOT supported
    message(FATAL_ERROR "\n\nSorry but the ${TARGET_SERIES} is not supported at this time...\nYou can wait for it to be added, or you might want to contribute by working on a PR for it.\n\n")
endif()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Gecko_SDK DEFAULT_MSG Gecko_SDK_INCLUDE_DIRS Gecko_SDK_SOURCES)

# macro to be called from binutils to add Gecko SDK as a library
# optional EXTRA_INCLUDES with include paths to be added to the library
# optional EXTRA_COMPILE_DEFINITIONS with compiler definitions to be added to the library
macro(nf_add_gecko_sdk)
   
    # parse arguments
    cmake_parse_arguments(NFGCKSDK "" "BUILD_TARGET" "EXTRA_INCLUDES;EXTRA_COMPILE_DEFINITIONS" ${ARGN})
    
    if("${NFGCKSDK_BUILD_TARGET}" STREQUAL "${NANOBOOTER_PROJECT_NAME}")
        set(CONFIG_FILES_PATH "${TARGET_BASE_LOCATION}/nanoBooter")
    elseif("${NFGCKSDK_BUILD_TARGET}" STREQUAL "${NANOCLR_PROJECT_NAME}")
        set(CONFIG_FILES_PATH "${TARGET_BASE_LOCATION}/nanoCLR")
    endif()

    # add THESE has a library
    set(LIB_NAME gecko_sdk_${NFGCKSDK_BUILD_TARGET})

    add_library(
        ${LIB_NAME} STATIC 
        ${Gecko_SDK_SOURCES}
    )

    target_include_directories(
        ${LIB_NAME} PUBLIC 

        ${Gecko_SDK_INCLUDE_DIRS}
        ${NFGCKSDK_EXTRA_INCLUDES}
    )

    nf_set_compile_options(TARGET ${LIB_NAME} BUILD_TARGET ${NFGCKSDK_BUILD_TARGET})
    nf_set_compile_definitions(TARGET ${LIB_NAME} EXTRA_COMPILE_DEFINITIONS ${NFGCKSDK_EXTRA_COMPILE_DEFINITIONS} BUILD_TARGET ${NFGCKSDK_BUILD_TARGET})
    nf_set_link_options(TARGET ${LIB_NAME})

    # add alias
    add_library("nano::${LIB_NAME}" ALIAS ${LIB_NAME})
    
endmacro()