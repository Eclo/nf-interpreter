//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2021 STMicroelectronics. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <nf_filex.h>

// byte pool for FileX
#define FX_APP_MEM_POOL_SIZE 1024 * 4

#if defined(__GNUC__)
__attribute__((aligned(4)))
#endif
uint8_t fx_byte_pool_buffer[FX_APP_MEM_POOL_SIZE];
static TX_BYTE_POOL fx_app_byte_pool;

#define DEFAULT_STACK_SIZE    (2 * 1024)
#define FILEX_THREAD_PRIORITY 5
TX_THREAD fx_app_thread;

#define DEFAULT_QUEUE_LENGTH 1
TX_QUEUE tx_msg_queue;

FX_MEDIA sdio_disk;
FX_FILE fx_file;

uint32_t NF_FileX_Init()
{
    void *pointer;
    uint32_t ret = FX_SUCCESS;

    ret = tx_byte_pool_create(&fx_app_byte_pool, "Fx App memory pool", fx_byte_pool_buffer, FX_APP_MEM_POOL_SIZE);
    if (ret != TX_SUCCESS)
    {
        HAL_AssertEx();
        return ret;
    }

    // Allocate memory for the main thread's stack
    ret = tx_byte_allocate(&fx_app_byte_pool, &pointer, DEFAULT_STACK_SIZE, TX_NO_WAIT);

    if (ret != FX_SUCCESS)
    {
        HAL_AssertEx();
        return ret;
    }

    // Create FileX thread
    tx_thread_create(
        &fx_app_thread,
        "FileX App Thread",
        FileXThread_entry,
        0,
        pointer,
        DEFAULT_STACK_SIZE,
        FILEX_THREAD_PRIORITY,
        FILEX_THREAD_PRIORITY,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    // Create the message queue
    tx_queue_create(&tx_msg_queue, "sd_event_queue", TX_1_ULONG, pointer, DEFAULT_QUEUE_LENGTH * sizeof(ULONG));

    // Initialize FileX
    fx_system_initialize();

    // done here
    return ret;
}