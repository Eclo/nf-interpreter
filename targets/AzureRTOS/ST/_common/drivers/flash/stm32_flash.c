//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <stm32_flash.h>

void stm32FlashInit(void)
{
    flash_lld_init();
}

void stm32FlashObjectInit()
{

}

void stm32FlashReadBytes(uint32_t startAddress, uint32_t length, uint8_t *buffer)
{
    assert_param((startAddress > FLASH_BASE) && (length > 0U) && (buffer != NULL));

    flash_lld_readBytes(startAddress, length, buffer);
}

int stm32FlashWrite(uint32_t startAddress, uint32_t length, const uint8_t *buffer)
{
    assert_param((startAddress > FLASH_BASE) && (length > 0U) && (buffer != NULL));

    return flash_lld_write(startAddress, length, buffer);
}

int stm32FlashIsErased(uint32_t startAddress, uint32_t length)
{
    assert_param((startAddress > FLASH_BASE) && (length > 0U));

    return flash_lld_isErased(startAddress, length);
}

int stm32FlashErase(uint32_t address)
{
    assert_param(address > FLASH_BASE);

    return flash_lld_erase(address);
}
