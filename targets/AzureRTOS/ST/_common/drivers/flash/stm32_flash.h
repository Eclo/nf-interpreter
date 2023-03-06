//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#ifndef HAL_NF_ST_FLASH_H
#define HAL_NF_ST_FLASH_H

#ifdef STM32H7XX
#include <stm32h7xx_hal.h>
#include <v5/flash_lld.h>
#endif

#ifdef STM32F7XX
#include <stm32f7xx_hal.h>
#include <v2/flash_lld.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    void stm32FlashInit(void);
    void stm32FlashObjectInit();
    void stm32FlashReadBytes(uint32_t startAddress, uint32_t length, uint8_t *buffer);
    int stm32FlashWrite(uint32_t startAddress, uint32_t length, const uint8_t *buffer);
    int stm32FlashIsErased(uint32_t startAddress, uint32_t length);
    int stm32FlashErase(uint32_t address);

#ifdef __cplusplus
}
#endif

#endif // HAL_NF_ST_FLASH_H
