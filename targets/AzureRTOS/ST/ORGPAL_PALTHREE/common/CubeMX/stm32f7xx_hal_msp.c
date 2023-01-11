//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2021 STMicroelectronics. All rights reserved.
// See LICENSE file in the project root for full license information.
//

// Includes ------------------------------------------------------------------*/
#include <stm32f7xx_hal.h>
// USER CODE BEGIN Includes

// USER CODE END Includes
extern DMA_HandleTypeDef hdma_sdmmc2_rx;

extern DMA_HandleTypeDef hdma_sdmmc2_tx;

void Error_Handler(void);

// Private typedef -----------------------------------------------------------*/
// USER CODE BEGIN TD

// USER CODE END TD

// Private define ------------------------------------------------------------*/
// USER CODE BEGIN Define

// USER CODE END Define

// Private macro -------------------------------------------------------------*/
// USER CODE BEGIN Macro

// USER CODE END Macro

// Private variables ---------------------------------------------------------*/
// USER CODE BEGIN PV

// USER CODE END PV

// Private function prototypes -----------------------------------------------*/
// USER CODE BEGIN PFP

// USER CODE END PFP

// External functions --------------------------------------------------------*/
// USER CODE BEGIN ExternalFunctions

// USER CODE END ExternalFunctions

// USER CODE BEGIN 0

// USER CODE END 0
//
// Initializes the Global MSP.
 
void HAL_MspInit(void)
{
    // USER CODE BEGIN MspInit 0

    // USER CODE END MspInit 0

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    // System interrupt init*/

    // USER CODE BEGIN MspInit 1

    // USER CODE END MspInit 1
}

//
// @brief  DeInitializes the Global MSP.  
// @retval None
void HAL_MspDeInit(void)
{
}

// //
// // @brief SD MSP Initialization
// * This function configures the hardware resources used in this example
// * @param hsd: SD handle pointer
// * @retval None
//
// void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
// {
//   GPIO_InitTypeDef GPIO_InitStruct = {0};
//   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
//   if(hsd->Instance==SDMMC2)
//   {
//   // USER CODE BEGIN SDMMC2_MspInit 0

//   // USER CODE END SDMMC2_MspInit 0
//   // Initializes the peripherals clock
//
//     PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC2|RCC_PERIPHCLK_CLK48;
//     PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
//     PeriphClkInitStruct.Sdmmc2ClockSelection = RCC_SDMMC2CLKSOURCE_CLK48;
//     if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
//     {
//       Error_Handler();
//     }

//     // Peripheral clock enable
//     __HAL_RCC_SDMMC2_CLK_ENABLE();

//     __HAL_RCC_GPIOB_CLK_ENABLE();
//     __HAL_RCC_GPIOD_CLK_ENABLE();
//     __HAL_RCC_GPIOG_CLK_ENABLE();
//     //SDMMC2 GPIO Configuration
//     PB4     ------> SDMMC2_D3
//     PB3     ------> SDMMC2_D2
//     PD7     ------> SDMMC2_CMD
//     PD6     ------> SDMMC2_CK
//     PG10     ------> SDMMC2_D1
//     PG9     ------> SDMMC2_D0
//
//     GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_3;
//     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//     GPIO_InitStruct.Pull = GPIO_NOPULL;
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//     GPIO_InitStruct.Alternate = GPIO_AF10_SDMMC2;
//     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//     GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
//     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//     GPIO_InitStruct.Pull = GPIO_NOPULL;
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//     GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
//     HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

//     GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_9;
//     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//     GPIO_InitStruct.Pull = GPIO_NOPULL;
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//     GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
//     HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

//     // SDMMC2 DMA Init
//     // SDMMC2_RX Init
//     hdma_sdmmc2_rx.Instance = DMA2_Stream0;
//     hdma_sdmmc2_rx.Init.Channel = DMA_CHANNEL_11;
//     hdma_sdmmc2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
//     hdma_sdmmc2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
//     hdma_sdmmc2_rx.Init.MemInc = DMA_MINC_ENABLE;
//     hdma_sdmmc2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
//     hdma_sdmmc2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
//     hdma_sdmmc2_rx.Init.Mode = DMA_PFCTRL;
//     hdma_sdmmc2_rx.Init.Priority = DMA_PRIORITY_LOW;
//     hdma_sdmmc2_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
//     hdma_sdmmc2_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
//     hdma_sdmmc2_rx.Init.MemBurst = DMA_MBURST_INC4;
//     hdma_sdmmc2_rx.Init.PeriphBurst = DMA_PBURST_INC4;
//     if (HAL_DMA_Init(&hdma_sdmmc2_rx) != HAL_OK)
//     {
//       Error_Handler();
//     }

//     __HAL_LINKDMA(hsd,hdmarx,hdma_sdmmc2_rx);

//     // SDMMC2_TX Init
//     hdma_sdmmc2_tx.Instance = DMA2_Stream5;
//     hdma_sdmmc2_tx.Init.Channel = DMA_CHANNEL_11;
//     hdma_sdmmc2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
//     hdma_sdmmc2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
//     hdma_sdmmc2_tx.Init.MemInc = DMA_MINC_ENABLE;
//     hdma_sdmmc2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
//     hdma_sdmmc2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
//     hdma_sdmmc2_tx.Init.Mode = DMA_PFCTRL;
//     hdma_sdmmc2_tx.Init.Priority = DMA_PRIORITY_LOW;
//     hdma_sdmmc2_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
//     hdma_sdmmc2_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
//     hdma_sdmmc2_tx.Init.MemBurst = DMA_MBURST_INC4;
//     hdma_sdmmc2_tx.Init.PeriphBurst = DMA_PBURST_INC4;
//     if (HAL_DMA_Init(&hdma_sdmmc2_tx) != HAL_OK)
//     {
//       Error_Handler();
//     }

//     __HAL_LINKDMA(hsd,hdmatx,hdma_sdmmc2_tx);

//   // USER CODE BEGIN SDMMC2_MspInit 1

//   // USER CODE END SDMMC2_MspInit 1
//   }

// }

// //
// // @brief SD MSP De-Initialization
// * This function freeze the hardware resources used in this example
// * @param hsd: SD handle pointer
// * @retval None
//
// void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
// {
//   if(hsd->Instance==SDMMC2)
//   {
//   // USER CODE BEGIN SDMMC2_MspDeInit 0

//   // USER CODE END SDMMC2_MspDeInit 0
//     // Peripheral clock disable
//     __HAL_RCC_SDMMC2_CLK_DISABLE();

//     //SDMMC2 GPIO Configuration
//     PB4     ------> SDMMC2_D3
//     PB3     ------> SDMMC2_D2
//     PD7     ------> SDMMC2_CMD
//     PD6     ------> SDMMC2_CK
//     PG10     ------> SDMMC2_D1
//     PG9     ------> SDMMC2_D0
//
//     HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4|GPIO_PIN_3);

//     HAL_GPIO_DeInit(GPIOD, GPIO_PIN_7|GPIO_PIN_6);

//     HAL_GPIO_DeInit(GPIOG, GPIO_PIN_10|GPIO_PIN_9);

//     // SDMMC2 DMA DeInit
//     HAL_DMA_DeInit(hsd->hdmarx);
//     HAL_DMA_DeInit(hsd->hdmatx);
//   // USER CODE BEGIN SDMMC2_MspDeInit 1

//   // USER CODE END SDMMC2_MspDeInit 1
//   }

// }

// //
// // @brief UART MSP Initialization
// * This function configures the hardware resources used in this example
// * @param huart: UART handle pointer
// * @retval None
//
// void HAL_UART_MspInit(UART_HandleTypeDef* huart)
// {
//   GPIO_InitTypeDef GPIO_InitStruct = {0};
//   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
//   if(huart->Instance==USART1)
//   {
//   // USER CODE BEGIN USART1_MspInit 0

//   // USER CODE END USART1_MspInit 0
//   // Initializes the peripherals clock
//
//     PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
//     PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
//     if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
//     {
//       Error_Handler();
//     }

//     // Peripheral clock enable
//     __HAL_RCC_USART1_CLK_ENABLE();

//     __HAL_RCC_GPIOA_CLK_ENABLE();
//     //USART1 GPIO Configuration
//     PA10     ------> USART1_RX
//     PA9     ------> USART1_TX
//
//     GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_9;
//     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//     GPIO_InitStruct.Pull = GPIO_NOPULL;
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//     GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
//     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//   // USER CODE BEGIN USART1_MspInit 1

//   // USER CODE END USART1_MspInit 1
//   }

// }

// //
// // @brief UART MSP De-Initialization
// * This function freeze the hardware resources used in this example
// * @param huart: UART handle pointer
// * @retval None
//
// void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
// {
//   if(huart->Instance==USART1)
//   {
//   // USER CODE BEGIN USART1_MspDeInit 0

//   // USER CODE END USART1_MspDeInit 0
//     // Peripheral clock disable
//     __HAL_RCC_USART1_CLK_DISABLE();

//     //USART1 GPIO Configuration
//     PA10     ------> USART1_RX
//     PA9     ------> USART1_TX
//
//     HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10|GPIO_PIN_9);

//   // USER CODE BEGIN USART1_MspDeInit 1

//   // USER CODE END USART1_MspDeInit 1
//   }

// }

// USER CODE BEGIN 1

// USER CODE END 1

// clang-format on
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Configure the main internal regulator output voltage

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    __HAL_RCC_HSE_CONFIG(RCC_HSE_OFF);

    // Initializes the RCC Oscillators according to the specified parameters
    // in the RCC_OscInitTypeDef structure
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 6;
    RCC_OscInitStruct.PLL.PLLN = 216;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    RCC_OscInitStruct.PLL.PLLR = 2;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    // Activate the Over-Drive mode
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }

    // Initializes the CPU, AHB and APB buses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
        Error_Handler();
    }
}

void PeriphCommonClock_Config(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    // Initializes the peripherals clock
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_TIM;
    PeriphClkInitStruct.TIMPresSelection = RCC_TIMPRES_ACTIVATED;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* Select PLLSAI output as USB clock source */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
    PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
    PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2; 
    PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct)  != HAL_OK)
    {
        Error_Handler();
    }
}

void MPU_Config(void)
{
    MPU_Region_InitTypeDef MPU_InitStruct = {0};

    // Disables the MPU
    HAL_MPU_Disable();

    // Initializes and configures the Region and the memory to be protected
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress = 0;
    MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
    MPU_InitStruct.SubRegionDisable = 0x87;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    // Initializes and configures the Region and the memory to be protected
    MPU_InitStruct.Number = MPU_REGION_NUMBER1;
    MPU_InitStruct.BaseAddress = 0x20027000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_32KB;
    MPU_InitStruct.SubRegionDisable = 0x0;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    
    // Enables the MPU
    HAL_MPU_Enable(MPU_HFNMI_PRIVDEF);
}

void Error_Handler(void)
{
    __asm("BKPT #0\n");
    while (1)
    { /*nop*/
    }
}