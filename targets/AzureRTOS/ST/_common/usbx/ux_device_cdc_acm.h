//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2021 STMicroelectronics. All rights reserved.
// See LICENSE file in the project root for full license information.
//

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UX_DEVICE_CDC_ACM_H
#define UX_DEVICE_CDC_ACM_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <ux_api.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <ux_device_class_cdc_acm.h>
    /* USER CODE END Includes */

    /* Exported types ------------------------------------------------------------*/
    /* USER CODE BEGIN ET */

    /* USER CODE END ET */

    /* Exported constants --------------------------------------------------------*/
    /* USER CODE BEGIN EC */

    /* USER CODE END EC */

    /* Exported macro ------------------------------------------------------------*/
    /* USER CODE BEGIN EM */

    /* USER CODE END EM */

    /* Exported functions prototypes ---------------------------------------------*/

    /* USER CODE BEGIN EFP */
    VOID ux_app_parameters_change(VOID *command);
    void CDC_DeInit_FS(void *cdc_acm);
    void CDC_Init_FS(void *cdc_acm);
    void usbx_cdc_acm_read_thread_entry(ULONG arg);
    void usbx_cdc_acm_write_thread_entry(ULONG arg);
    /* USER CODE END EFP */

    /* Private defines -----------------------------------------------------------*/
    /* USER CODE BEGIN PD */

    /* USER CODE END PD */

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif // UX_DEVICE_CDC_ACM_H
