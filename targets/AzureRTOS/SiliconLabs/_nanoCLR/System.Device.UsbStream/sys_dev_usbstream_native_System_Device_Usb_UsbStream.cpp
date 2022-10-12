//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <sys_dev_usbstream_native.h>
#include "sys_dev_usbstream_native_target.h"

static void UsbAsyncWriteCompleted(
    uint8_t class_nbr,
    void *p_buf,
    uint32_t buf_len,
    uint32_t xfer_len,
    void *p_callback_arg,
    sl_status_t status)
{
    (void)class_nbr;
    (void)p_buf;
    (void)buf_len;
    (void)xfer_len;
    (void)p_callback_arg;
    (void)status;

    Events_Set(SYSTEM_EVENT_FLAG_USB_OUT);
}

static void UsbAsyncReadCompleted(
    uint8_t class_nbr,
    void *p_buf,
    uint32_t buf_len,
    uint32_t xfer_len,
    void *p_callback_arg,
    sl_status_t status)
{
    (void)class_nbr;
    (void)p_buf;
    (void)buf_len;
    (void)xfer_len;
    (void)p_callback_arg;
    (void)status;

    Events_Set(SYSTEM_EVENT_FLAG_USB_IN);
}

// -- //

HRESULT Library_sys_dev_usbstream_native_System_Device_Usb_UsbStream::Flush___VOID(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    NANOCLR_SET_AND_LEAVE(stack.NotImplementedStub());

    NANOCLR_NOCLEANUP();
}

HRESULT Library_sys_dev_usbstream_native_System_Device_Usb_UsbStream::NativeClose___VOID(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    NANOCLR_SET_AND_LEAVE(stack.NotImplementedStub());

    NANOCLR_NOCLEANUP();
}

HRESULT Library_sys_dev_usbstream_native_System_Device_Usb_UsbStream::NativeOpen___I4__STRING__STRING(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    const char *deviceDescription;
    const char *deviceClassGuid;

    // get device class GUID
    deviceClassGuid = stack.Arg1().RecoverString();
    ;

    // clear destination
    memset(UsbClassVendorDeviceInterfaceGuid, 0, sizeof(UsbClassVendorDeviceInterfaceGuid));

    for (uint16_t i = 0; i < sizeof(UsbClassVendorDeviceInterfaceGuid); i += 2)
    {
        UsbClassVendorDeviceInterfaceGuid[i] = *deviceClassGuid++;
    }

    // get description
    deviceDescription = stack.Arg2().RecoverString();
    FAULT_ON_NULL(deviceDescription);

    // store device description
    hal_strcpy_s(UsbClassVendorDescription, sizeof(UsbClassVendorDescription), deviceDescription);

    sli_usbd_vendor_winusb_init();

    stack.SetResult_I4(sl_usbd_vendor_winusb_number);

    NANOCLR_NOCLEANUP();
}

HRESULT Library_sys_dev_usbstream_native_System_Device_Usb_UsbStream::NativeWrite___VOID__SZARRAY_U1__I4__I4(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    CLR_RT_HeapBlock_Array *dataBuffer;
    CLR_RT_HeapBlock hbTimeout;
    int64_t *timeoutTicks;
    bool eventResult = true;

    uint8_t *data;
    uint32_t length = 0;
    uint32_t count = 0;
    uint32_t offset = 0;
    sl_status_t reqStatus;
    bool conn;
    uint32_t estimatedDurationMiliseconds;

    // get a pointer to the managed object instance and check that it's not NULL
    CLR_RT_HeapBlock *pThis = stack.This();
    FAULT_ON_NULL(pThis);

    if ((bool)pThis[FIELD___disposed].NumericByRef().u1)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_OBJECT_DISPOSED);
    }

    // perform parameter validation and setup TX operation

    // dereference the data buffer from the argument
    dataBuffer = stack.Arg1().DereferenceArray();
    offset = stack.Arg2().NumericByRef().s4;
    count = stack.Arg3().NumericByRef().s4;

    // get the size of the buffer
    length = dataBuffer->m_numOfElements;

    // check parameters
    FAULT_ON_NULL_ARG(dataBuffer);

    if ((offset > length) || (count > length))
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_OPERATION);
    }

    if (offset + count > length)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    // check if device is connected (enabled)
    sl_usbd_vendor_is_enabled(sl_usbd_vendor_winusb_number, &conn);

    if (!conn)
    {
        // device is not connected, return exception
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_OPERATION);
    }

    // get a the pointer to the array by using the offset
    data = dataBuffer->GetElement(offset);

    // rough estimation!!
    estimatedDurationMiliseconds = count / 64;

    // setup timeout
    hbTimeout.SetInteger((CLR_INT64)estimatedDurationMiliseconds * TIME_CONVERSION__TO_MILLISECONDS);
    NANOCLR_CHECK_HRESULT(stack.SetupTimeoutFromTicks(hbTimeout, timeoutTicks));

    // this is a long running operation...
    if (stack.m_customState == 1)
    {
        // ... and hasn't started yet
        // push onto the eval stack how many bytes are being pushed to the USB
        stack.PushValueI4(count);

        // bump custom state
        stack.m_customState = 2;

        // start write operation with async API
        // requesting handling of "End-of-transfer"
        reqStatus = sl_usbd_vendor_write_bulk_async(
            sl_usbd_vendor_winusb_number,
            (void *)data,
            count,
            UsbAsyncWriteCompleted,
            NULL,
            true);

        _ASSERTE(reqStatus == SL_STATUS_OK);
    }

    while (eventResult)
    {
        // non-blocking wait allowing other threads to run while we wait for the USB operation to complete
        NANOCLR_CHECK_HRESULT(
            g_CLR_RT_ExecutionEngine.WaitEvents(stack.m_owningThread, *timeoutTicks, Event_UsbOut, eventResult));
    }

    // pop "count" heap block from stack
    stack.PopValue();

    // pop timeout heap block from stack
    stack.PopValue();

    NANOCLR_NOCLEANUP();
}

HRESULT Library_sys_dev_usbstream_native_System_Device_Usb_UsbStream::NativeRead___I4__SZARRAY_U1__I4__I4(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    CLR_RT_HeapBlock_Array *dataBuffer;
    CLR_RT_HeapBlock hbTimeout;
    int64_t *timeoutTicks;
    bool eventResult = true;

    uint8_t *data;
    uint32_t length = 0;
    uint32_t count = 0;
    uint32_t offset = 0;
    sl_status_t reqStatus;
    bool conn;
    uint32_t bytesTransfered;
    uint32_t estimatedDurationMiliseconds;

    // get a pointer to the managed object instance and check that it's not NULL
    CLR_RT_HeapBlock *pThis = stack.This();
    FAULT_ON_NULL(pThis);

    if ((bool)pThis[FIELD___disposed].NumericByRef().u1)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_OBJECT_DISPOSED);
    }

    // perform parameter validation and setup TX operation

    // dereference the data buffer from the argument
    dataBuffer = stack.Arg1().DereferenceArray();
    offset = stack.Arg2().NumericByRef().s4;
    count = stack.Arg3().NumericByRef().s4;

    // get the size of the buffer
    length = dataBuffer->m_numOfElements;

    // check parameters
    FAULT_ON_NULL_ARG(dataBuffer);

    if ((offset > length) || (count > length))
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_OPERATION);
    }

    if (offset + count > length)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    // check if device is connected (enabled)
    sl_usbd_vendor_is_enabled(sl_usbd_vendor_winusb_number, &conn);

    if (!conn)
    {
        // device is not connected, return exception
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_OPERATION);
    }

    // get a the pointer to the array by using the offset
    data = dataBuffer->GetElement(offset);

    // rough estimation!!
    estimatedDurationMiliseconds = count / 64;

    // setup timeout
    hbTimeout.SetInteger((CLR_INT64)estimatedDurationMiliseconds * TIME_CONVERSION__TO_MILLISECONDS);
    NANOCLR_CHECK_HRESULT(stack.SetupTimeoutFromTicks(hbTimeout, timeoutTicks));

    // this is a long running operation...
    if (stack.m_customState == 1)
    {
        // ... and hasn't started yet
        // push onto the eval stack how many bytes are being pushed to the USB
        stack.PushValueI4(count);

        // bump custom state
        stack.m_customState = 2;

        // start read operation with async API
        // requesting handling of "End-of-transfer"
        reqStatus = sl_usbd_vendor_read_bulk_async(
            sl_usbd_vendor_winusb_number,
            (void *)data,
            count,
            UsbAsyncReadCompleted,
            NULL);

        _ASSERTE(reqStatus == SL_STATUS_OK);
    }

    while (eventResult)
    {
        // non-blocking wait allowing other threads to run while we wait for the USB operation to complete
        NANOCLR_CHECK_HRESULT(
            g_CLR_RT_ExecutionEngine.WaitEvents(stack.m_owningThread, *timeoutTicks, Event_UsbIn, eventResult));
    }

    // pop "count" heap block from stack
    stack.PopValue();

    // pop timeout heap block from stack
    stack.PopValue();

    stack.SetResult_I4(bytesTransfered);

    NANOCLR_NOCLEANUP();
}