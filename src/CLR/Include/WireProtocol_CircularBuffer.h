//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef WIREPROTOCOL_CIRCULARBUFFER_H
#define WIREPROTOCOL_CIRCULARBUFFER_H

#include <stdint.h>
#include <string.h>

#define BUF_MIN(x, y) ((x) < (y) ? (x) : (y))
#define BUF_MAX(x, y) ((x) > (y) ? (x) : (y))
#define ARRAY_LEN(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct WpCircularBuffer
{
    uint8_t *buffer;
    int32_t size;
    int32_t r;
    int32_t w;
} WpCircularBuffer;

uint8_t WP_InitializeBuffer(WpCircularBuffer *buff, void *buffdata, int32_t size);
int32_t WP_BufferBytesWaiting(WpCircularBuffer *buff);
int32_t WP_WriteBuffer(WpCircularBuffer *buff, const void *data, int32_t btw);
int32_t WP_ReadBuffer(WpCircularBuffer *buff, void *data, int32_t btr);

#endif // WIREPROTOCOL_CIRCULARBUFFER_H
