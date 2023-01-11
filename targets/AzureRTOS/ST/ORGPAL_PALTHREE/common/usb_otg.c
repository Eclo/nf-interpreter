//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2021 STMicroelectronics. All rights reserved.
// See LICENSE file in the project root for full license information.
//

/* Includes ------------------------------------------------------------------*/
#include <stm32f7xx_hal.h>

/* USER CODE BEGIN 0 */
#include <string.h>

/* Set hpcd_USB_OTG_FS at the end of non-cacheable
   Memory address 0x20027000. */
#if defined(__GNUC__)
__attribute__((section(".UsbHpcdSection")))
#endif
/* USER CODE END 0 */

extern void
    Error_Handler(void);

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USB_OTG_FS init function */

void MX_USB_OTG_FS_PCD_Init(void)
{
    /* USER CODE BEGIN USB_OTG_HS_Init 1 */
    memset(&hpcd_USB_OTG_FS, 0x0, sizeof(PCD_HandleTypeDef));
    /* USER CODE END USB_OTG_HS_Init 1 */
    hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
    hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
    hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
    hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
    hpcd_USB_OTG_FS.Init.phy_itface = USB_OTG_EMBEDDED_PHY;
    hpcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
    hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
    hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
    hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
    hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
    hpcd_USB_OTG_FS.Init.use_external_vbus = DISABLE;
    if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_PCD_MspInit(PCD_HandleTypeDef *pcdHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (pcdHandle->Instance == USB_OTG_FS)
    {
        /* USER CODE BEGIN USB_OTG_HS_MspInit 0 */

        /* USER CODE END USB_OTG_HS_MspInit 0 */

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /* USB_OTG_FS GPIO Configuration
         * PA9 VBUS_FS
         * PA10 OTG_FS_ID
         * PA11 OTG_FS_DM
         * PA12 OTG_FS_DP
         */

        /* Configure DM DP Pins */
        GPIO_InitStruct.Pin = (GPIO_PIN_11 | GPIO_PIN_12);
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* Configure VBUS Pin */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* Configure ID pin */
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* USB_OTG_FS clock enable */
        __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

        /* USB_OTG_FS interrupt Init */
        HAL_NVIC_SetPriority(OTG_FS_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
        /* USER CODE BEGIN USB_OTG_HS_MspInit 1 */

        /* USER CODE END USB_OTG_HS_MspInit 1 */
    }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef *pcdHandle)
{

    if (pcdHandle->Instance == USB_OTG_FS)
    {
        /* USER CODE BEGIN USB_OTG_HS_MspDeInit 0 */

        /* USER CODE END USB_OTG_HS_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_USB_OTG_HS_CLK_DISABLE();

        /* USB_OTG_FS GPIO Configuration
         * PA9 VBUS_FS
         * PA10 OTG_FS_ID
         * PA11 OTG_FS_DM
         * PA12 OTG_FS_DP
         */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);

        /* USB_OTG_HS interrupt Deinit */
        HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
        /* USER CODE BEGIN USB_OTG_HS_MspDeInit 1 */

        /* USER CODE END USB_OTG_HS_MspDeInit 1 */
    }
}

// This function handles USB-On-The-Go FS global interrupt request.
void OTG_FS_IRQHandler(void)
{
    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
