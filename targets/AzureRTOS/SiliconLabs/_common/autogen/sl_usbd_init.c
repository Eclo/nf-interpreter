//****************************************************************************
// Includes.

#include <target_platform.h>

#include "sl_status.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wundef"
#endif

#include <sl_usbd_core.h>

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#if GECKO_FEATURE_USBD_HID == TRUE
#include "sl_usbd_class_hid.h"
#endif

#if GECKO_FEATURE_USBD_WINUSB == TRUE
#include "sl_usbd_class_vendor.h"
#endif

#if HAL_WP_USE_USB_CDC == TRUE
#include "sl_usbd_class_cdc.h"
#include "sl_usbd_class_cdc_acm.h"
#endif

//****************************************************************************
// Global functions.

/* USB initialization function */
void sli_usbd_init(void)
{

    sl_usbd_core_init();

#if GECKO_FEATURE_USBD_HID == TRUE
    sl_usbd_hid_init();
#endif

#if HAL_WP_USE_USB_CDC == TRUE
    sl_usbd_cdc_init();
    sl_usbd_cdc_acm_init();
#endif

#if GECKO_FEATURE_USBD_WINUSB == TRUE
    sl_usbd_vendor_init();
#endif

}
