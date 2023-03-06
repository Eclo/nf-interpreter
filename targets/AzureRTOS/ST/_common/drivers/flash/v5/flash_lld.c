//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2016 STMicroelectronics.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "flash_lld.h"

///////////////////////////////////////////////////////////////////////////////
// This driver has been tested with the following STM32 series: F4
///////////////////////////////////////////////////////////////////////////////

void flash_lld_readBytes(uint32_t startAddress, uint32_t length, uint8_t *buffer)
{
    __IO uint8_t *cursor = (__IO uint8_t *)startAddress;
    __IO uint8_t *endAddress = (__IO uint8_t *)(startAddress + length);

    // copy contents from flash to buffer starting from the start address
    while (cursor < endAddress)
    {
        *buffer++ = *cursor++;
    }
}

int flash_lld_write(uint32_t startAddress, uint32_t length, const uint8_t *buffer)
{
    __IO uint8_t *cursor = (__IO uint8_t *)startAddress;
    __IO uint8_t *endAddress = (__IO uint8_t *)(startAddress + length);
    uint8_t rowIndex;

    // default to false
    bool success = false;
    uint32_t bank = FLASH_BANK_1;

    // unlock the FLASH

    if (HAL_FLASH_Unlock() == HAL_OK)
    {
        // Set PG bit
        FLASH->CR1 |= FLASH_CR_PG;

        while (cursor < endAddress)
        {
            __ISB();
            __DSB();

            rowIndex = FLASH_NB_32BITWORD_IN_FLASHWORD;

            // if buffer has enough data, program words (32 bits) in a single operation to speed up things
            // NOTE: assuming that the supply voltage is able to cope with half-word programming
            if ((endAddress - cursor) >= 4)
            {
                // Program the flash word
                do
                {
                    *(__IO uint32_t *)cursor = *((uint32_t *)buffer);

                    // update flash and buffer pointers by the 'extra' size that was programmed
                    cursor += 4;
                    buffer += 4;

                    rowIndex--;
                } while (rowIndex != 0U);
            }
            else
            {
                // can only program words
                // TODO add error code?
                success = false;
                break;
            }

            __ISB();
            __DSB();

            // wait 500ms for any flash operation to be completed
            success = FLASH_WaitForLastOperation(500, bank) == HAL_OK;

            if (!success)
            {
                // quit on failure
                break;
            }
        }

        // after the program operation is completed disable the PG Bit
        FLASH->CR1 &= (~FLASH_CR_PG);

        // lock the FLASH
        HAL_FLASH_Lock();
    }

    return success;
}

int flash_lld_isErased(uint32_t startAddress, uint32_t length)
{

    __IO uint32_t *cursor = (__IO uint32_t *)startAddress;
    __IO uint32_t *endAddress = (__IO uint32_t *)(startAddress + length);

    // an erased flash address has to read FLASH_ERASED_WORD
    // OK to check by word (32 bits) because the erase is performed by 'page' whose size is word multiple
    while (cursor < endAddress)
    {
        if (*cursor++ != FLASH_ERASED_WORD)
        {
            // found an address with something other than FLASH_ERASED_WORD!!
            return false;
        }
    }

    // reached here so the segment must be erased
    return true;
}

int flash_lld_erase(uint32_t address)
{
    // default to false
    bool success = false;
    uint32_t eraseError = 0;
    FLASH_EraseInitTypeDef eraseInitStruct;

    // unlock the FLASH
    if (HAL_FLASH_Unlock() == HAL_OK)
    {
        // Fill EraseInit structure
        eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
        eraseInitStruct.Banks = FLASH_BANK_1;
        eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_4;
        eraseInitStruct.Sector = (address - FLASH_BASE) / FLASH_SECTOR_SIZE;
        ;
        eraseInitStruct.NbSectors = 1;

        success = (HAL_FLASHEx_Erase(&eraseInitStruct, &eraseError) == HAL_OK);

        // Data synchronous Barrier, forcing the CPU to respect the sequence of instruction without optimization
        __DSB();

        // lock the FLASH
        HAL_FLASH_Lock();
    }

    return success;
}
