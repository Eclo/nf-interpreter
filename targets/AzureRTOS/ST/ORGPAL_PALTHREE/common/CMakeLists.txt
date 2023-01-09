#
# Copyright (c) .NET Foundation and Contributors
# See LICENSE file in the project root for full license information.
#

# append common source files
#list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/usbcfg.c)
# list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/stm32f7xx_hal_msp.c)
list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/stm32f7xx_hal_gpio.c)
# list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/CubeMX/system_stm32f7xx.c)

list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f769nihx.s)
list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tx_initialize_low_level.s)
list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Device_BlockStorage$<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:-DEBUG>.c)
list(APPEND COMMON_PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/targetHAL_ConfigurationManager.cpp)

# make var global
set(COMMON_PROJECT_SOURCES ${COMMON_PROJECT_SOURCES} CACHE INTERNAL "make global")
