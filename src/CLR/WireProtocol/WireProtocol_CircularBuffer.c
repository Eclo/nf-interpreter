//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <WireProtocol_CircularBuffer.h>

uint8_t WP_InitializeBuffer(WpCircularBuffer *buffer, void *data, int32_t size)
{
    if (buffer == NULL || data == NULL || size == 0)
    {
        return 0;
    }

    memset((void *)buffer, 0x00, sizeof(*buffer));
    buffer->size = size;
    buffer->buffer = data;
    memset(data, 0x00, size);

    return 1;
}

int32_t WP_WriteBuffer(WpCircularBuffer *buffer, const void *data, int32_t btw)
{
    int32_t tocopy;
    int32_t free;
    int32_t size;
    const uint8_t *d = data;

    if (data == NULL || btw == 0)
    {
        return 0;
    }

    // Calculate maximum number of bytes available to write
    // Use temporary values in case they are changed during operations
    int32_t w = buffer->w;
    int32_t r = buffer->r;

    if (w == r)
    {
        size = buffer->size;
    }
    else if (r > w)
    {
        size = r - w;
    }
    else
    {
        size = buffer->size - (w - r);
    }

    // buffer free size is always 1 less than actual size
    free = size - 1;

    btw = BUF_MIN(free, btw);
    if (btw == 0)
    {
        return 0;
    }

    // Step 1: Write data to linear part of buffer
    tocopy = BUF_MIN(buffer->size - buffer->w, btw);
    memcpy(&buffer->buffer[buffer->w], d, tocopy);
    buffer->w += tocopy;
    btw -= tocopy;

    // Step 2: Write data to beginning of buffer (overflow part)
    if (btw > 0)
    {
        memcpy(buffer->buffer, &d[tocopy], btw);
        buffer->w = btw;
    }

    // Step 3: Check end of buffer
    if (buffer->w >= buffer->size)
    {
        buffer->w = 0;
    }

    return tocopy + btw;
}

int32_t WP_ReadBuffer(WpCircularBuffer *buffer, void *data, int32_t btr)
{
    int32_t tocopy;
    int32_t full;
    uint8_t *d = data;

    if (data == NULL || btr == 0)
    {
        return 0;
    }

    // Calculate maximum number of bytes available to read
    full = WP_BufferBytesWaiting(buffer);
    btr = BUF_MIN(full, btr);
    if (btr == 0)
    {
        return 0;
    }

    // Step 1: Read data from linear part of buffer
    tocopy = BUF_MIN(buffer->size - buffer->r, btr);
    memcpy(d, &buffer->buffer[buffer->r], tocopy);
    buffer->r += tocopy;
    btr -= tocopy;

    // Step 2: Read data from beginning of buffer (overflow part)
    if (btr > 0)
    {
        memcpy(&d[tocopy], buffer->buffer, btr);
        buffer->r = btr;
    }

    // Step 3: Check end of buffer
    if (buffer->r >= buffer->size)
    {
        buffer->r = 0;
    }

    return tocopy + btr;
}

int32_t WP_BufferBytesWaiting(WpCircularBuffer *buffer)
{
    int32_t size;

    // Use temporary values in case they are changed during operations
    int32_t w = buffer->w;
    int32_t r = buffer->r;

    if (w == r)
    {
        size = 0;
    }
    else if (w > r)
    {
        size = w - r;
    }
    else
    {
        size = buffer->size - (r - w);
    }

    return size;
}
