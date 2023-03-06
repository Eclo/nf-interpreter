//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2016 STMicroelectronics. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef FLASH_LLD_H
#define FLASH_LLD_H

#include <stm32h7xx_hal.h>

#define FLASH_ERASED_WORD 0x0FFFFFFFFU

#ifdef __cplusplus
extern "C"
{
#endif

    void flash_lld_init();
    void flash_lld_readBytes(uint32_t startAddress, uint32_t length, uint8_t *buffer);
    int flash_lld_write(uint32_t startAddress, uint32_t length, const uint8_t *buffer);
    int flash_lld_isErased(uint32_t startAddress, uint32_t length);
    int flash_lld_erase(uint32_t address);
    uint8_t flash_lld_getSector(uint32_t address);

#ifdef __cplusplus
}
#endif

#endif // FLASH_LLD_H
