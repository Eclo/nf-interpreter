//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "wp_uart.h"
#include <assert.h>
#include <tx_api.h>

// USART receive buffer for DMA - make sure it is in RAM accessible by the DMA controller used.
// Also, check alignment
__attribute__((section(".dma_buffer"))) __attribute__((aligned(32)))
uint8_t wpUSART_DMA_Receive_Buffer[WP_RX_BUFFER_SIZE];
static_assert((sizeof(wpUSART_DMA_Receive_Buffer) % 32) == 0, "Must be a multiple by 32");

WpCircularBuffer ReceiveCircularBuffer;
uint8_t wp_ReceiveData[WP_RX_BUFFER_SIZE];

WpCircularBuffer TransmitCircularBuffer;
uint8_t wp_TransmitData[WP_TX_BUFFER_SIZE];

//  Length of currently active TX DMA transfer
volatile size_t usart_tx_dma_current_len;

TX_EVENT_FLAGS_GROUP wpReceivedBytesEvent;

void InitWireProtocolCommunications()
{
    wp_uart_InitializeUsart();

    WP_InitializeBuffer(&TransmitCircularBuffer, wp_TransmitData, sizeof(wp_TransmitData));
    WP_InitializeBuffer(&ReceiveCircularBuffer, wp_ReceiveData, sizeof(wp_ReceiveData));

    // Create event based data synchronization
    tx_event_flags_create(&wpReceivedBytesEvent, "wpReceiveDataEvent");
}

void wp_uart_InitializeUsart(void)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Peripheral clock enable
    wpUSART_PERIPHERAL_CLOCK_ENABLE;
    wpUSART_GPIO_PERIPHERAL_CLOCK_ENABLE;
    wpUSART_DMA_PERIPHERAL_CLOCK_ENABLE;

    // UART TX/RX GPIO pin configuration and clock
    GPIO_InitStruct.Pin = wpUSART_TX_PIN | wpUSART_RX_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // wpUSART Receive Initialize
    LL_DMA_SetPeriphRequest(wpDMA, wpDMA_ReceiveStream, wpDMA_ReceiveMux);
    LL_DMA_SetDataTransferDirection(wpDMA, wpDMA_ReceiveStream, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetStreamPriorityLevel(wpDMA, wpDMA_ReceiveStream, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(wpDMA, wpDMA_ReceiveStream, LL_DMA_MODE_CIRCULAR);
    LL_DMA_SetPeriphIncMode(wpDMA, wpDMA_ReceiveStream, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(wpDMA, wpDMA_ReceiveStream, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetMemorySize(wpDMA, wpDMA_ReceiveStream, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetPeriphSize(wpDMA, wpDMA_ReceiveStream, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_DisableFifoMode(wpDMA, wpDMA_ReceiveStream);
    LL_DMA_SetPeriphAddress(
        wpDMA,
        wpDMA_ReceiveStream,
        LL_USART_DMA_GetRegAddr(wpUSART, LL_USART_DMA_REG_DATA_RECEIVE));
    LL_DMA_SetMemoryAddress(wpDMA, wpDMA_ReceiveStream, (uint32_t)wpUSART_DMA_Receive_Buffer);
    LL_DMA_SetDataLength(wpDMA, wpDMA_ReceiveStream, ARRAY_LEN(wpUSART_DMA_Receive_Buffer));

    // wpUSART Transmit Initialize
    LL_DMA_SetPeriphRequest(wpDMA, wpDMA_TransmitStream, wpDMA_TransmitMux);
    LL_DMA_SetDataTransferDirection(wpDMA, wpDMA_TransmitStream, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetStreamPriorityLevel(wpDMA, wpDMA_TransmitStream, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(wpDMA, wpDMA_TransmitStream, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(wpDMA, wpDMA_TransmitStream, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(wpDMA, wpDMA_TransmitStream, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(wpDMA, wpDMA_TransmitStream, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(wpDMA, wpDMA_TransmitStream, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_DisableFifoMode(wpDMA, wpDMA_TransmitStream);
    LL_DMA_SetPeriphAddress(
        wpDMA,
        wpDMA_TransmitStream,
        LL_USART_DMA_GetRegAddr(wpUSART, LL_USART_DMA_REG_DATA_TRANSMIT));

    // Enable receive half transfer interrupt
    LL_DMA_EnableIT_HT(wpDMA, wpDMA_ReceiveStream);

    // Enable receive transfer complete interrupt
    LL_DMA_EnableIT_TC(wpDMA, wpDMA_ReceiveStream);

    // Enable transmit transfer complete interrupt
    LL_DMA_EnableIT_TC(wpDMA, wpDMA_TransmitStream);

    // DMA interrupt initialize
    NVIC_SetPriority(wpDMA_ReceiveStreamInterrupt, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(wpDMA_ReceiveStreamInterrupt);
    NVIC_SetPriority(wpDMA_TransmitStreamInterrupt, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(wpDMA_TransmitStreamInterrupt);

    // Configure WireProtocol wpUSART
    USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
    USART_InitStruct.BaudRate = wpBAUD_RATE;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;

    // Required to make changes, LL_USART_Init doesn't work unless disabled
    LL_USART_Disable(wpUSART);
    LL_USART_Init(wpUSART, &USART_InitStruct);
    LL_USART_SetTXFIFOThreshold(wpUSART, LL_USART_FIFOTHRESHOLD_7_8);
    LL_USART_SetRXFIFOThreshold(wpUSART, LL_USART_FIFOTHRESHOLD_7_8);
    LL_USART_EnableFIFO(wpUSART);
    LL_USART_ConfigAsyncMode(wpUSART);
    LL_USART_EnableDMAReq_RX(wpUSART);
    LL_USART_EnableDMAReq_TX(wpUSART);
    LL_USART_EnableIT_IDLE(wpUSART);

    // USART interrupt, same priority as DMA channel
    NVIC_SetPriority(wpUSART_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(wpUSART_IRQn);

    LL_DMA_EnableStream(wpDMA, wpDMA_ReceiveStream);
    LL_USART_Enable(wpUSART);

    // Polling wpUSART initialization
    while (!LL_USART_IsActiveFlag_TEACK(wpUSART) || !LL_USART_IsActiveFlag_REACK(wpUSART))
    {
    }
}

int wp_uart_ReadBytes(uint8_t **ptr, uint32_t *size, uint32_t wait_time)
{
    ULONG actual_flags;
    uint32_t requestedSize = *size;
    tx_event_flags_get(&wpReceivedBytesEvent, 0x1, TX_OR_CLEAR, &actual_flags, wait_time);

    // Bytes have arrived try to read what was requested
    ULONG read = WP_ReadBuffer(&ReceiveCircularBuffer, *ptr, requestedSize);

    return read;
}

bool wp_uart_WriteBytes(uint8_t *ptr, uint16_t size)
{
    SCB_CleanInvalidateDCache();
    wp_uart_WriteBuffer(&TransmitCircularBuffer, ptr, size);
    SCB_CleanInvalidateDCache();

    wp_uart_StartTransmitTransfer();

    return true;
}

void wp_uart_DataReceived(void)
{
    static size_t old_position;

    // Calculate current position in buffer and check for new data available
    int length_data_received = LL_DMA_GetDataLength(wpDMA, wpDMA_ReceiveStream);
    size_t position = ARRAY_LEN(wpUSART_DMA_Receive_Buffer) - length_data_received;

    if (position != old_position)
    {
        SCB_CleanInvalidateDCache_by_Addr((uint32_t *)&wpUSART_DMA_Receive_Buffer, sizeof(wpUSART_DMA_Receive_Buffer));

        if (position > old_position)
        {
            WP_WriteBuffer(&ReceiveCircularBuffer, &wpUSART_DMA_Receive_Buffer[old_position], position - old_position);
        }
        else
        {
            // Processing is done in "overflow" mode..
            WP_WriteBuffer(
                &ReceiveCircularBuffer,
                &wpUSART_DMA_Receive_Buffer[old_position],
                ARRAY_LEN(wpUSART_DMA_Receive_Buffer) - old_position);

            if (position > 0)
            {
                WP_WriteBuffer(&ReceiveCircularBuffer, &wpUSART_DMA_Receive_Buffer[0], position);
            }
        }

        old_position = position;
        tx_event_flags_set(&wpReceivedBytesEvent, 0x1, TX_OR);
    }
}

uint8_t wp_uart_StartTransmitTransfer(void)
{
    //  First check if transfer is currently in-active, by examining the value of
    //  usart_tx_dma_current_len variable. This variable is set before DMA transfer
    //  is started and cleared in DMA TX complete interrupt. It is not necessary to
    //  disable the interrupts before checking the variable:
    //
    //  When usart_tx_dma_current_len == 0
    //     - This function is called by either application or TX DMA interrupt
    //     - When called from interrupt, it was just reset before the call
    //  indicating transfer just completed and ready for more
    //     - When called from an application, transfer was previously already
    //  in-active and immediate call from interrupt cannot happen at this moment
    //
    //  When usart_tx_dma_current_len != 0
    //     - This function is called only by an application.
    //     - It will never be called from interrupt with usart_tx_dma_current_len
    //  != 0 condition
    //
    //  Disabling interrupts before checking for next transfer is advised
    //  only if multiple operating system threads can access this function w/o
    //  exclusive access protection (mutex) configured, or if application calls
    //  this function from multiple interrupts.
    //
    //  This example assumes worst use case scenario, hence interrupts are disabled
    //  prior every check
    //
    uint8_t started = 0;
    size_t length;
    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    // Use temporary values in case they are changed during operations
    size_t w = TransmitCircularBuffer.w;
    size_t r = TransmitCircularBuffer.r;

    if (w > r)
    {
        length = w - r;
    }
    else if (r > w)
    {
        length = TransmitCircularBuffer.size - r;
    }
    else
    {
        length = 0;
    }

    if (usart_tx_dma_current_len == 0 && (usart_tx_dma_current_len = length) > 0)
    {
        // Wait for any previous DMA to finish
        // Wait for any previous DMA / stream 1 transfers to complete
        while (LL_DMA_IsActiveFlag_TC1(wpDMA))
        {
        };
        // Disable channel if enabled
        LL_DMA_DisableStream(wpDMA, wpDMA_TransmitStream);

        // Clear all flags
        LL_DMA_ClearFlag_TC1(wpDMA);
        LL_DMA_ClearFlag_HT1(wpDMA);
        LL_DMA_ClearFlag_TE1(wpDMA);
        LL_DMA_ClearFlag_DME1(wpDMA);
        LL_DMA_ClearFlag_FE1(wpDMA);

        // Prepare DMA data and length
        LL_DMA_SetDataLength(wpDMA, wpDMA_TransmitStream, usart_tx_dma_current_len);
        LL_DMA_SetMemoryAddress(
            wpDMA,
            wpDMA_TransmitStream,
            (uint32_t)&TransmitCircularBuffer.buffer[TransmitCircularBuffer.r]);

        LL_DMA_EnableStream(wpDMA, wpDMA_TransmitStream);
        started = 1;
    }

    __set_PRIMASK(primask);

    return started;
}

wpDMA_ReceiveStream_IRQHandler()
{
    // Check half-transfer complete interrupt
    if (LL_DMA_IsEnabledIT_HT(wpDMA, wpDMA_ReceiveStream) && LL_DMA_IsActiveFlag_HT0(wpDMA))
    {
        LL_DMA_ClearFlag_HT0(wpDMA);
        wp_uart_DataReceived();
    }

    // Check transfer-complete interrupt
    if (LL_DMA_IsEnabledIT_TC(wpDMA, wpDMA_ReceiveStream) && LL_DMA_IsActiveFlag_TC0(wpDMA))
    {
        LL_DMA_ClearFlag_TC0(wpDMA);
        wp_uart_DataReceived();
    }
}

wpDMA_TransmitStream_IRQHandler()
{
    if (LL_DMA_IsEnabledIT_TC(wpDMA, wpDMA_TransmitStream) && LL_DMA_IsActiveFlag_TC1(wpDMA))
    {
        LL_DMA_ClearFlag_TC1(wpDMA);

        size_t number_bytes_waiting = wp_BufferBytesWaiting(&TransmitCircularBuffer);

        TransmitCircularBuffer.r += BUF_MIN(usart_tx_dma_current_len, number_bytes_waiting);
        
        if (TransmitCircularBuffer.r >= TransmitCircularBuffer.size)
        {
            TransmitCircularBuffer.r -= TransmitCircularBuffer.size;
        }

        // Clear length variable
        usart_tx_dma_current_len = 0;

        // Start sending more data
        wp_uart_StartTransmitTransfer();
    }
}

wpUSART_IRQHANDLER()
{
    if (LL_USART_IsActiveFlag_PE(wpUSART) || LL_USART_IsActiveFlag_FE(wpUSART) || LL_USART_IsActiveFlag_NE(wpUSART) ||
        LL_USART_IsActiveFlag_ORE(wpUSART) || LL_USART_IsActiveFlag_PE(wpUSART))
    {
        // Clear Parity,Framing,Noise,Overrun errors
        LL_USART_ClearFlag_PE(wpUSART);
        LL_USART_ClearFlag_FE(wpUSART);
        LL_USART_ClearFlag_NE(wpUSART);
        LL_USART_ClearFlag_ORE(wpUSART);

        // Initialize Circular buffer for Receive after an error
        WP_InitializeBuffer(&ReceiveCircularBuffer, wp_uart_ReceiveData, sizeof(wp_ReceiveData));
    }
    // Check for IDLE line interrupt
    else if (LL_USART_IsActiveFlag_IDLE(wpUSART))
    {
        LL_USART_ClearFlag_IDLE(wpUSART);
        wp_uart_DataReceived();
    }
}
