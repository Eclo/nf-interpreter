//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "sys_dev_usbstream_native.h"

// clang-format off

static const CLR_RT_MethodHandler method_lookup[] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_sys_dev_usbstream_native_System_Device_UsbClient_UsbStream::Flush___VOID,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_sys_dev_usbstream_native_System_Device_UsbClient_UsbStream::NativeClose___VOID,
    Library_sys_dev_usbstream_native_System_Device_UsbClient_UsbStream::NativeOpen___I4__STRING__STRING,
    Library_sys_dev_usbstream_native_System_Device_UsbClient_UsbStream::NativeWrite___VOID__SZARRAY_U1__I4__I4,
    Library_sys_dev_usbstream_native_System_Device_UsbClient_UsbStream::NativeRead___I4__SZARRAY_U1__I4__I4,
};

const CLR_RT_NativeAssemblyData g_CLR_AssemblyNative_System_Device_UsbStream =
{
    "System.Device.UsbStream",
    0x79416300,
    method_lookup,
    { 1, 0, 0, 0 }
};

// clang-format on
