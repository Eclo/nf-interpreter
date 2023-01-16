//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#ifndef NF_USBX_H_
#define NF_USBX_H_

#include <target_ux_user.h>
#include <tx_api.h>
#include <ux_api.h>
#include <ux_system.h>
#include <ux_utility.h>
#include <ux_device_stack.h>
#include <ux_dcd_stm32.h>
#include <ux_device_descriptors.h>
#include <ux_device_cdc_acm.h>

#ifdef __cplusplus
extern "C"
{
#endif

    uint32_t NF_UsbX_Init(void);
    void NF_UsbX_UnInit(void);

    void UsbXThread_entry(uint32_t parameter);

#ifdef __cplusplus
}
#endif

#endif // NF_USBX_H_
