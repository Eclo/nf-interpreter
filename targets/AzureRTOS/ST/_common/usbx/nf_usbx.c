//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2021 STMicroelectronics. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <nf_usbx.h>

// byte pool for UsbX
#define UX_DEVICE_APP_MEM_POOL_SIZE 1024 * 16
#define USBX_MEMORY_SIZE            (12 * 1024)

#if defined(__GNUC__)
__attribute__((section(".UsbxPoolSection")))
#endif
uint8_t ux_device_byte_pool_buffer[UX_DEVICE_APP_MEM_POOL_SIZE];
TX_BYTE_POOL ux_device_app_byte_pool;

TX_THREAD ux_app_thread;
TX_THREAD ux_cdc_read_thread;
TX_THREAD ux_cdc_write_thread;

TX_EVENT_FLAGS_GROUP EventFlag;

/* CDC Class Calling Parameter structure */
UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_acm_parameter;

#define USBX_APP_STACK_SIZE 1024

void usbx_app_thread_entry(uint32_t arg);

extern void MX_USB_OTG_FS_PCD_Init(void);
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

uint32_t NF_UsbX_Init()
{
    uint32_t ret = UX_SUCCESS;

    ret = tx_byte_pool_create(
        &ux_device_app_byte_pool,
        "Ux App memory pool",
        ux_device_byte_pool_buffer,
        UX_DEVICE_APP_MEM_POOL_SIZE);
    if (ret != UX_SUCCESS)
    {
        HAL_AssertEx();
        return ret;
    }

    /* USER CODE BEGIN MX_USBX_Device_Init */
    uint8_t *pointer;
    /* Device framework FS length*/
    uint32_t device_framework_fs_length;
    /* Device framework HS length*/
    uint32_t device_framework_hs_length;
    /* Device String framework length*/
    uint32_t string_framework_length;
    /* Device language id framework length*/
    uint32_t languge_id_framework_length;
    /* Device Framework Full Speed */
    uint8_t *device_framework_full_speed;
    /* Device Framework High Speed */
    uint8_t *device_framework_high_speed;
    /* String Framework*/
    uint8_t *string_framework;
    /* Language_Id_Framework*/
    uint8_t *language_id_framework;
    /* Status Tx */
    uint16_t tx_status = UX_SUCCESS;

    /* Allocate USBX_MEMORY_SIZE. */
    tx_status = tx_byte_allocate(&ux_device_app_byte_pool, (void **)&pointer, USBX_MEMORY_SIZE, TX_NO_WAIT);

    /* Check memory allocation */
    if (TX_SUCCESS != tx_status)
    {
        HAL_AssertEx();
    }

    /* Initialize USBX Memory */
    ux_system_initialize(pointer, USBX_MEMORY_SIZE, UX_NULL, 0);

    /* Get_Device_Framework_High_Speed and get the length */
    device_framework_high_speed = USBD_Get_Device_Framework_Speed(USBD_HIGH_SPEED, &device_framework_hs_length);

    /* Get_Device_Framework_Full_Speed and get the length */
    device_framework_full_speed = USBD_Get_Device_Framework_Speed(USBD_FULL_SPEED, &device_framework_fs_length);

    /* Get_String_Framework and get the length */
    string_framework = USBD_Get_String_Framework(&string_framework_length);

    /* Get_Language_Id_Framework and get the length */
    language_id_framework = USBD_Get_Language_Id_Framework(&languge_id_framework_length);

    /* The code below is required for installing the device portion of USBX.
    In this application */
    ret = _ux_device_stack_initialize(
        device_framework_high_speed,
        device_framework_hs_length,
        device_framework_full_speed,
        device_framework_fs_length,
        string_framework,
        string_framework_length,
        language_id_framework,
        languge_id_framework_length,
        UX_NULL);

    /* Check the Stack initialize status */
    if (ret != UX_SUCCESS)
    {
        HAL_AssertEx();
    }

    /* Initialize the cdc class parameters for the device. */
    cdc_acm_parameter.ux_slave_class_cdc_acm_instance_activate = CDC_Init_FS;

    /* Deinitialize the cdc class parameters for the device. */
    cdc_acm_parameter.ux_slave_class_cdc_acm_instance_deactivate = CDC_DeInit_FS;

    /* Manage the CDC class requests */
    cdc_acm_parameter.ux_slave_class_cdc_acm_parameter_change = ux_app_parameters_change;

    /* registers a slave class to the slave stack. The class is connected with
       interface 0 */
    ret = ux_device_stack_class_register(
        _ux_system_slave_class_cdc_acm_name,
        ux_device_class_cdc_acm_entry,
        1,
        0,
        (void *)&cdc_acm_parameter);

    /* Check the device stack class status */
    if (ret != UX_SUCCESS)
    {
        HAL_AssertEx();
    }

    /* Allocate the stack for main_usbx_app_thread_entry. */
    tx_status = tx_byte_allocate(&ux_device_app_byte_pool, (void **)&pointer, USBX_APP_STACK_SIZE, TX_NO_WAIT);

    /* Check memory allocation */
    if (TX_SUCCESS != tx_status)
    {
        HAL_AssertEx();
    }

    /* Create the usbx_app_thread_entry main thread. */
    tx_status = tx_thread_create(
        &ux_app_thread,
        "main_usbx_app_thread_entry",
        usbx_app_thread_entry,
        0,
        pointer,
        USBX_APP_STACK_SIZE,
        5,
        5,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    /* Allocate the stack for usbx_cdc_acm_read_thread_entry. */
    tx_status = tx_byte_allocate(&ux_device_app_byte_pool, (void **)&pointer, USBX_APP_STACK_SIZE, TX_NO_WAIT);

    /* Check memory allocation */
    if (TX_SUCCESS != tx_status)
    {
        HAL_AssertEx();
    }

    /* Create the usbx_cdc_acm_thread_entry thread. */
    tx_status = tx_thread_create(
        &ux_cdc_read_thread,
        "cdc_acm_read_usbx_app_thread_entry",
        usbx_cdc_acm_read_thread_entry,
        1,
        pointer,
        USBX_APP_STACK_SIZE,
        5,
        5,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    /* Check usbx_cdc_acm_read_thread_entry creation */
    if (TX_SUCCESS != tx_status)
    {
        HAL_AssertEx();
    }

    /* Allocate the stack for usbx_cdc_acm_write_thread_entry. */
    tx_status = tx_byte_allocate(&ux_device_app_byte_pool, (void **)&pointer, USBX_APP_STACK_SIZE, TX_NO_WAIT);

    /* Check memory allocation */
    if (TX_SUCCESS != tx_status)
    {
        HAL_AssertEx();
    }

    /* Create the usbx_cdc_acm_thread_entry thread. */
    tx_status = tx_thread_create(
        &ux_cdc_write_thread,
        "cdc_acm_write_usbx_app_thread_entry",
        usbx_cdc_acm_write_thread_entry,
        1,
        pointer,
        USBX_APP_STACK_SIZE,
        5,
        5,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    /* Check usbx_cdc_acm_write_thread_entry creation */
    if (TX_SUCCESS != tx_status)
    {
        HAL_AssertEx();
    }

    /* Create the event flags group. */
    if (tx_event_flags_create(&EventFlag, "Event Flag") != TX_SUCCESS)
    {
        ret = TX_GROUP_ERROR;
    }

    return ret;
}

void usbx_app_thread_entry(uint32_t arg)
{
    (void)arg;

    // initialization of USB device

    /* USB_OTG_HS init function */
    MX_USB_OTG_FS_PCD_Init();

    /* Set Rx FIFO */
    HAL_PCDEx_SetRxFiFo(&hpcd_USB_OTG_FS, 0x200);
    /* Set Tx FIFO 0 */
    HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 0, 0x80);
    /* Set Tx FIFO 1 */
    HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 1, 0x174);

    /* USER CODE END USB_Device_Init_PreTreatment_1 */

    /* initialize the device controller driver */
    ux_dcd_stm32_initialize((ULONG)USB_OTG_FS, (ULONG)&hpcd_USB_OTG_FS);

    /* Start the USB device */
    HAL_PCD_Start(&hpcd_USB_OTG_FS);
}