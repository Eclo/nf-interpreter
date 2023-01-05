//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <hal.h>

#define SD_PRESENT     1UL
#define SD_NOT_PRESENT 0UL

typedef enum {
CARD_STATUS_CHANGED             = 99,
CARD_STATUS_DISCONNECTED        = 88,
CARD_STATUS_CONNECTED           = 77
} SD_ConnectionStateTypeDef;

extern TX_QUEUE tx_msg_queue;

// Detects if SD card is correctly plugged in the memory slot or not.
// @param Instance  SD Instance
// @retval Returns if SD is detected or not
int32_t SD_IsDetected(uint32_t Instance)
{
    int32_t ret;
    if (Instance >= 1)
    {
        ret = HAL_ERROR;
    }
    else
    {
        /* Check SD card detect pin */
        if (HAL_GPIO_ReadPin(SD_DETECT_GPIO_Port, SD_DETECT_Pin) == GPIO_PIN_SET)
        {
            ret = SD_NOT_PRESENT;
        }
        else
        {
            ret = SD_PRESENT;
        }
    }

    return (int32_t)ret;
}

__attribute__((noreturn)) void FileXThread_entry(uint32_t parameter)
{
    (void)parameter;
      uint32_t s_msg = CARD_STATUS_CHANGED;

    while (1)
    {
        if (SD_IsDetected(FX_STM32_SD_INSTANCE) == SD_PRESENT)
        {
            // SD card is already inserted, place the info into the queue
            tx_queue_send(&tx_msg_queue, &s_msg, TX_NO_WAIT);
        }
    }

    // this never returns
}
