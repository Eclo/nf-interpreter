//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#ifndef WP_UART_H
#define WP_UART_H

#include <stm32f7xx_hal.h>
#include <WireProtocol_CircularBuffer.h>

#include <wp_uart_config.h>

#include <stdbool.h>
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_dma.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_usart.h"

// define baud rate and buffers size, if not already defined
#ifndef WP_BAUDRATE
#define WP_BAUDRATE 921600
#endif
#ifndef WP_RX_BUFFER_SIZE
#define WP_RX_BUFFER_SIZE 512
#endif
#ifndef WP_TX_BUFFER_SIZE
#define WP_TX_BUFFER_SIZE 512
#endif

#define wpUSART_IRQn                    USART3_IRQn
#define wpUSART_IRQHANDLER()            void USART3_IRQHandler(void)
#define wpUSART_PERIPHERAL_CLOCK_ENABLE LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3)

#define wpUSART_GPIO_PORT                    GPIOD
#define wpUSART_RX_PIN                       LL_GPIO_PIN_9
#define wpUSART_TX_PIN                       LL_GPIO_PIN_8
#define wpUSART_GPIO_PERIPHERAL_CLOCK_ENABLE LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD)

#define wpDMA                               DMA1
#define wpDMA_ReceiveStreamInterrupt        DMA1_Stream0_IRQn
#define wpDMA_TransmitStreamInterrupt       DMA1_Stream1_IRQn
#define wpUSART_DMA_PERIPHERAL_CLOCK_ENABLE LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1)

#define wpDMA_ReceiveStream              LL_DMA_STREAM_0
#define wpDMA_ReceiveMux                 LL_DMAMUX1_REQ_USART3_RX
#define wpDMA_ReceiveStream_IRQHandler() void DMA1_Stream0_IRQHandler(void)

#define wpDMA_TransmitStream              LL_DMA_STREAM_1
#define wpDMA_TransmitMux                 LL_DMAMUX1_REQ_USART3_TX
#define wpDMA_TransmitStream_IRQHandler() void DMA1_Stream1_IRQHandler(void)

#ifdef __cplusplus
extern "C"
{
#endif

    void InitWireProtocolCommunications();
    bool wp_uart_WriteBytes(uint8_t *ptr, uint16_t size);
    int wp_uart_ReadBytes(uint8_t **ptr, uint32_t *size, uint32_t wait_time);
    void wp_uart_InitializeUsart(void);
    void wp_uart_DataReceived(void);
    uint8_t wp_uart_StartTransmitTransfer(void);

#ifdef __cplusplus
}
#endif

#endif // WP_UART_H
