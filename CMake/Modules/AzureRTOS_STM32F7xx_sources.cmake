#
# Copyright (c) .NET Foundation and Contributors
# See LICENSE file in the project root for full license information.
#

FetchContent_GetProperties(azure_rtos)

list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/ST/_common/drivers/flash)
list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/CLR/Include)
list(APPEND STM32F7_CubePackage_INCLUDE_DIRS ${azure_rtos_SOURCE_DIR}/common/inc)

list(REMOVE_DUPLICATES STM32F7_CubePackage_INCLUDE_DIRS)

set(STM32F7_CubePackage_SRCS

    # flash driver
    stm32_flash.c
    flash_lld.c

)

foreach(SRC_FILE ${STM32F7_CubePackage_SRCS})

    set(STM32F7_CubePackage_SRC_FILE SRC_FILE-NOTFOUND)

    find_file(STM32F7_CubePackage_SRC_FILE ${SRC_FILE}
        PATHS 
        
        # flash driver
        ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/ST/_common/drivers/flash
        ${CMAKE_SOURCE_DIR}/targets/AzureRTOS/ST/_common/drivers/flash/v2

        CMAKE_FIND_ROOT_PATH_BOTH
    )

    if (BUILD_VERBOSE)
        message("${SRC_FILE} >> ${STM32F7_CubePackage_SRC_FILE}")
    endif()

    list(APPEND STM32F7_CubePackage_SOURCES ${STM32F7_CubePackage_SRC_FILE})

endforeach()

list(REMOVE_DUPLICATES STM32F7_CubePackage_SOURCES)
