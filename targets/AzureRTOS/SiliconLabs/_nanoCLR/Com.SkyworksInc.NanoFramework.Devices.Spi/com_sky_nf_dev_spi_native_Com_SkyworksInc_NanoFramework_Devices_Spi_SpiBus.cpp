// Copyright Skyworks Solutions, Inc. All Rights Reserved.

#include "com_sky_nf_dev_spi_native_target.h"

extern NF_PAL_SPI *GetNfPalfromBusIndex(uint8_t busIndex);
extern void SpiTransferCompleteCallback(NF_SpiDriver_Handle_t handle, Ecode_t transferStatus, int itemsTransferred);

typedef Library_com_sky_nf_dev_spi_native_Com_SkyworksInc_NanoFramework_Devices_Spi_SpiBus Devices_Spi_SpiBus;
typedef Library_com_sky_nf_dev_spi_native_Com_SkyworksInc_NanoFramework_Devices_Spi_SpiBaseConfiguration
    SpiBaseConfiguration;
typedef Library_corlib_native_System_SpanByte SpanByte;

static HRESULT SPI_nWrite_nRead(
    NF_PAL_SPI *palSpi,
    SPI_DEVICE_CONFIGURATION &sdev,
    SPI_WRITE_READ_SETTINGS &wrc,
    uint8_t *writeBuffer,
    int32_t writeSize,
    uint8_t *readBuffer,
    int32_t readSize);

// Saved config for each available SPI bus
SPI_DEVICE_CONFIGURATION SpiConfigs[NUM_SPI_BUSES];

void Com_Sky_Spi_Callback(int busIndex)
{
    (void)busIndex;

    // fire event for SPI transaction complete
    Events_Set(SYSTEM_EVENT_FLAG_SPI_MASTER);
}

// duplicated from src\System.Device.Spi\sys_dev_spi_native_System_Device_Spi_SpiDevice.cpp
// estimate the time required to perform the SPI transaction
// TODO doesn't take into account of full duplex or sequential ( assumes sequential at the moment )
bool System_Device_IsLongRunningOperation(
    uint32_t writeSize,
    uint32_t readSize,
    bool fullDuplex,
    bool bufferIs16bits,
    float byteTime,
    uint32_t &estimatedDurationMiliseconds)
{
    if (bufferIs16bits)
    {
        // double the buffers size
        writeSize = 2 * writeSize;
        readSize = 2 * readSize;
    }

    if (fullDuplex)
    {
        estimatedDurationMiliseconds = byteTime * MAX(writeSize, readSize);
    }
    else
    {
        estimatedDurationMiliseconds = byteTime * (writeSize + readSize);
    }

    if (estimatedDurationMiliseconds > CLR_RT_Thread::c_TimeQuantum_Milliseconds)
    {
        // total operation time will exceed thread quantum, so this is a long running operation
        return true;
    }
    else
    {
        return false;
    }
}

HRESULT ExecuteTransfer(CLR_RT_StackFrame &stack, bool isSpanByte)
{
    NANOCLR_HEADER();

    CLR_RT_HeapBlock *config = NULL;
    CLR_RT_HeapBlock_Array *writeBuffer;
    CLR_RT_HeapBlock_Array *readBuffer;
    CLR_RT_HeapBlock *writeSpanByte;
    CLR_RT_HeapBlock *readSpanByte;
    uint8_t *writeData = NULL;
    uint8_t *readData = NULL;
    int16_t writeSize = 0;
    int16_t readSize = 0;
    int16_t readOffset = 0;
    int16_t writeOffset = 0;
    bool fullDuplex;

    bool isLongRunningOperation;
    uint32_t estimatedDurationMiliseconds;
    CLR_RT_HeapBlock hbTimeout;
    CLR_INT64 *timeout;
    bool eventResult = true;
    int8_t busIndex;
    SPI_WRITE_READ_SETTINGS rws;
    NF_PAL_SPI *palSpi = NULL;

    // get a pointer to the managed object instance and check that it's not NULL
    CLR_RT_HeapBlock *pThis = stack.This();
    FAULT_ON_NULL(pThis);

    // get bus index
    busIndex = (int8_t)stack.Arg1().NumericByRef().s4;

    if (stack.m_customState == 0)
    {
        // check if this SPI has been initialized
        palSpi = GetNfPalfromBusIndex(busIndex);
        if (palSpi->Handle == NULL)
        {
            // compose SPI_DEVICE_CONFIGURATION
            // get ref to SpiBaseConfiguration from static _busConnectionSettings array, access it by index
            config = (CLR_RT_HeapBlock *)pThis[Devices_Spi_SpiBus::FIELD_STATIC___busConnectionSettings]
                         .DereferenceArray()
                         ->GetElement(busIndex);

            // CS is always active low
            SpiConfigs[busIndex].ChipSelectActive = false;
            // always bus master
            SpiConfigs[busIndex].BusMode = SpiBusMode_master;

            // internally SPI bus ID is zero based, so better take care of that here
            SpiConfigs[busIndex].Spi_Bus = busIndex;

            SpiConfigs[busIndex].DeviceChipSelect = config[SpiBaseConfiguration::FIELD___csLine].NumericByRef().s4;

            // sanity check chip select line
            if (SpiConfigs[busIndex].DeviceChipSelect < -1)
            {
                NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
            }

            SpiConfigs[busIndex].Spi_Mode = (SpiMode)config[SpiBaseConfiguration::FIELD___spiMode].NumericByRef().s4;
            SpiConfigs[busIndex].DataOrder16 =
                (DataBitOrder)config[SpiBaseConfiguration::FIELD___dataFlow].NumericByRef().s4;
            SpiConfigs[busIndex].Clock_RateHz = config[SpiBaseConfiguration::FIELD___clockFrequency].NumericByRef().s4;
            SpiConfigs[busIndex].ByteTime = (1.0 / SpiConfigs[busIndex].Clock_RateHz) * 1000 * 8;
            SpiConfigs[busIndex].BusConfiguration =
                (SpiBusConfiguration)config[SpiBaseConfiguration::FIELD___busConfiguration].NumericByRef().s4;
            SpiConfigs[busIndex].MD16bits =
                config[SpiBaseConfiguration::FIELD___databitLength].NumericByRef().s4 == 16 ? true : false;
            // store this here too
            palSpi->BufferIs16bits = SpiConfigs[busIndex].MD16bits;

            CPU_SPI_Initialize(busIndex, SpiConfigs[busIndex]);
        }

        // Buffers used either for the SpanBye either for the Byte array

        if (isSpanByte)
        {
            // dereference the write and read SpanByte from the arguments
            writeSpanByte = stack.Arg1().Dereference();

            if (writeSpanByte != NULL)
            {
                // get buffer
                writeBuffer = writeSpanByte[SpanByte::FIELD___array].DereferenceArray();

                if (writeBuffer != NULL)
                {
                    // Get the write offset, only the elements defined by the span must be written, not the whole
                    // array
                    writeOffset = writeSpanByte[SpanByte::FIELD___start].NumericByRef().s4;

                    // use the span length as write size, only the elements defined by the span must be written
                    writeSize = writeSpanByte[SpanByte::FIELD___length].NumericByRef().s4;
                    writeData = (unsigned char *)writeBuffer->GetElement(writeOffset);
                }
            }

            if (writeData == NULL)
            {
                // nothing to write, have to zero this
                writeSize = 0;
            }

            readSpanByte = stack.Arg2().Dereference();

            if (readSpanByte != NULL)
            {
                // get buffer
                readBuffer = readSpanByte[SpanByte::FIELD___array].DereferenceArray();

                if (readBuffer != NULL)
                {
                    // Get the read offset, only the elements defined by the span must be read, not the whole array
                    readOffset = readSpanByte[SpanByte::FIELD___start].NumericByRef().s4;

                    // use the span length as read size, only the elements defined by the span must be read
                    readSize = readSpanByte[SpanByte::FIELD___length].NumericByRef().s4;
                    readData = (unsigned char *)readBuffer->GetElement(readOffset);
                }
            }

            if (readData == NULL)
            {
                // nothing to read, have to zero this
                readSize = 0;
            }
        }
        else
        {
            writeBuffer = stack.Arg1().DereferenceArray();

            if (writeBuffer != NULL)
            {
                // grab the pointer to the array by getting the first element of the array
                writeData = (unsigned char *)writeBuffer->GetFirstElementUInt16();

                // get the size of the buffer by reading the number of elements in the HeapBlock array
                writeSize = writeBuffer->m_numOfElements;
            }

            readBuffer = stack.Arg2().DereferenceArray();

            if (readBuffer != NULL)
            {
                // grab the pointer to the array by getting the first element of the array
                readData = (unsigned char *)readBuffer->GetFirstElementUInt16();

                // get the size of the buffer by reading the number of elements in the HeapBlock array
                readSize = readBuffer->m_numOfElements;
            }
        }

        // assuming full duplex all the time
        fullDuplex = true;

        // Set up read/write settings for SPI_Write_Read call
        rws = {fullDuplex, 0, palSpi->BufferIs16bits, 0};

        // Check to see if we should run async so as not to hold up other tasks
        isLongRunningOperation = System_Device_IsLongRunningOperation(
            writeSize,
            readSize,
            fullDuplex,
            palSpi->BufferIs16bits,
            SpiConfigs[busIndex].ByteTime,
            (uint32_t &)estimatedDurationMiliseconds);

        if (isLongRunningOperation)
        {
            // if this is a long running operation, set a timeout equal to the estimated transaction duration in
            // milliseconds this value has to be in ticks to be properly loaded by SetupTimeoutFromTicks() below

            // Use twice the estimated Duration as timeout
            estimatedDurationMiliseconds *= 2;

            hbTimeout.SetInteger((CLR_INT64)estimatedDurationMiliseconds * TIME_CONVERSION__TO_MILLISECONDS);

            // if m_customState == 0 then push timeout on to eval stack[0] then move to m_customState = 1
            // Return current timeout value
            NANOCLR_CHECK_HRESULT(stack.SetupTimeoutFromTicks(hbTimeout, timeout));

            // protect the buffers from GC so DMA can find them where they are supposed to be
            if (writeData != NULL)
            {
                CLR_RT_ProtectFromGC gcWriteBuffer(*writeBuffer);
            }
            if (readData != NULL)
            {
                CLR_RT_ProtectFromGC gcReadBuffer(*readBuffer);
            }

            // Set callback for async calls to nano spi
            rws.callback = Com_Sky_Spi_Callback;
        }

        // Start SPI transfer
        // We can ask for async transfer by setting callback but it depends if underlying supports it
        // return of CLR_E_BUSY means async started
        hr = SPI_nWrite_nRead(
            palSpi,
            SpiConfigs[busIndex],
            rws,
            (uint8_t *)writeData,
            (int32_t)writeSize,
            (uint8_t *)readData,
            (int32_t)readSize);

        // Async transfer started, go to custom 2 state (wait completion)
        if (hr == CLR_E_BUSY)
        {
            stack.m_customState = 2;
        }
    }

    // Waiting for Async operation to complete
    if (stack.m_customState == 2)
    {
        // Get timeout from eval stack we set up
        stack.SetupTimeoutFromTicks(hbTimeout, timeout);

        while (eventResult)
        {
            // non-blocking wait allowing other threads to run while we wait for the Spi transaction to complete
            NANOCLR_CHECK_HRESULT(
                g_CLR_RT_ExecutionEngine.WaitEvents(stack.m_owningThread, *timeout, Event_SpiMaster, eventResult));

            if (!eventResult)
            {
                // Timeout
                NANOCLR_SET_AND_LEAVE(CLR_E_TIMEOUT);
            }
        }

        // pop timeout heap block from stack
        stack.PopValue();

        // null pointers and vars
        pThis = NULL;
    }

    NANOCLR_NOCLEANUP();
}

static HRESULT SPI_nWrite_nRead(
    NF_PAL_SPI *palSpi,
    SPI_DEVICE_CONFIGURATION &sdev,
    SPI_WRITE_READ_SETTINGS &wrc,
    uint8_t *writeBuffer,
    int32_t writeSize,
    uint8_t *readBuffer,
    int32_t readSize)
{
    NANOCLR_HEADER();

    bool busConfigIsHalfDuplex;

    // If callback then use async operation
    bool sync = (wrc.callback == 0);

    // Save width of transfer
    palSpi->BufferIs16bits = wrc.Bits16ReadWrite;

    // Callback sync / async
    palSpi->Callback = wrc.callback;

    if (writeBuffer != NULL)
    {
        palSpi->WriteSize = writeSize;
    }

    if (readBuffer != NULL)
    {
        palSpi->ReadSize = readSize;
    }

    // === Setup the operation and init buffers ===
    palSpi->BusIndex = sdev.Spi_Bus;

    // adjust the bus index to match the PAL struct
    NF_SpiDriver_SetFramelength(palSpi->Handle, wrc.Bits16ReadWrite ? 16 : 8);

    // set bus config flag
    busConfigIsHalfDuplex = (palSpi->BusConfiguration == SpiBusConfiguration_HalfDuplex);

    if (writeBuffer != NULL)
    {
        // set the pointer to the write buffer as BYTE
        palSpi->WriteBuffer = (uint8_t *)writeBuffer;
    }

    if (readBuffer != NULL)
    {
        // set DMA read buffer
        if (palSpi->ReadSize > 0)
        {
            palSpi->ReadBuffer = (uint8_t *)readBuffer;
        }
    }

    // if CS is to be controlled by the driver, set the GPIO
    if (palSpi->ChipSelect >= 0)
    {
        // assert pin based on CS active level
        CPU_GPIO_SetPinState(palSpi->ChipSelect, (GpioPinValue)sdev.ChipSelectActive);
    }

    if (sync)
    {
        // Sync operation
        // perform SPI operation using driver's SYNC API
        if (palSpi->WriteSize != 0 && palSpi->ReadSize != 0)
        {
            // Transmit+Receive
            if (wrc.fullDuplex)
            {
                // Full duplex
                // Uses the largest buffer size as transfer size
                NF_SpiDriver_TransferBlocking(
                    palSpi->Handle,
                    palSpi->WriteBuffer,
                    palSpi->ReadBuffer,
                    palSpi->WriteSize > palSpi->ReadSize ? palSpi->WriteSize : palSpi->ReadSize);
            }
            else
            {
                // send operation
                // TODO
                // if (busConfigIsHalfDuplex)
                // {
                //     // half duplex operation, set output enable
                //     palSpi->Handle->spi->CR1 |= SPI_CR1_BIDIOE;
                // }
                NF_SpiDriver_TransmitBlocking(palSpi->Handle, palSpi->WriteBuffer, palSpi->WriteSize);

                // receive operation
                // TODO
                // if (busConfigIsHalfDuplex)
                // {
                //     // half duplex operation, set output enable
                //     palSpi->Handle->spi->CR1 &= ~SPI_CR1_BIDIOE;
                // }
                NF_SpiDriver_ReceiveBlocking(palSpi->Handle, palSpi->ReadBuffer, palSpi->ReadSize);
            }
        }
        else
        {
            // Transmit only or Receive only
            if (palSpi->ReadSize != 0)
            {
                // receive
                // TODO
                // if (busConfigIsHalfDuplex)
                // {
                //     // half duplex operation, set output enable
                //     palSpi->Handle->spi->CR1 &= ~SPI_CR1_BIDIOE;
                // }
                NF_SpiDriver_ReceiveBlocking(palSpi->Handle, palSpi->ReadBuffer, palSpi->ReadSize);
            }
            else
            {
                // send
                // TODO
                if (busConfigIsHalfDuplex)
                {
                    // half duplex operation, set output enable
                    // palSpi->Handle->spi->CR1 |= SPI_CR1_BIDIOE;
                }
                NF_SpiDriver_TransmitBlocking(palSpi->Handle, palSpi->WriteBuffer, palSpi->WriteSize);
            }
        }

        // if CS is to be controlled by the driver, set the GPIO
        if (palSpi->ChipSelect >= 0)
        {
            // de-assert pin based on CS active level
            CPU_GPIO_TogglePinState(palSpi->ChipSelect);
        }
    }
    else
    {
        // Start an Asyncronous SPI transfer
        // perform SPI operation using driver's ASYNC API
        // Completed on calling SPI Callback

        // if CS is to be controlled by the driver, set the GPIO
        if (palSpi->ChipSelect >= 0)
        {
            // assert pin based on CS active level
            CPU_GPIO_SetPinState(palSpi->ChipSelect, (GpioPinValue)sdev.ChipSelectActive);
        }

        // this is a Async operation
        // perform SPI operation using driver's ASYNC API
        if (palSpi->WriteSize != 0 && palSpi->ReadSize != 0)
        {
            // Transmit+Receive
            if (wrc.fullDuplex)
            {
                // Full duplex
                // single operation, clear flag
                palSpi->SequentialTxRx = false;

                // Uses the largest buffer size as transfer size
                NF_SpiDriver_Transfer(
                    palSpi->Handle,
                    palSpi->WriteBuffer,
                    palSpi->ReadBuffer,
                    palSpi->WriteSize > palSpi->ReadSize ? palSpi->WriteSize : palSpi->ReadSize,
                    SpiTransferCompleteCallback);
            }
            else
            {
                // flag that an Rx is required after the Tx operation completes
                palSpi->SequentialTxRx = true;

                // start send operation
                if (busConfigIsHalfDuplex)
                {
                    // // half duplex operation, set output enable
                    // palSpi->Handle->spi->CR1 |= SPI_CR1_BIDIOE;
                }

                // receive operation will be started in the callback after the above completes
                NF_SpiDriver_Transmit(
                    palSpi->Handle,
                    palSpi->WriteBuffer,
                    palSpi->WriteSize,
                    SpiTransferCompleteCallback);
            }
        }
        else
        {
            // Transmit only or Receive only
            if (palSpi->ReadSize != 0)
            {
                // single operation, clear flag
                palSpi->SequentialTxRx = false;

                // start receive
                NF_SpiDriver_Receive(palSpi->Handle, palSpi->ReadBuffer, palSpi->ReadSize, SpiTransferCompleteCallback);
            }
            else
            {
                // single operation, clear flag
                palSpi->SequentialTxRx = false;

                // start send
                NF_SpiDriver_Transmit(
                    palSpi->Handle,
                    palSpi->WriteBuffer,
                    palSpi->WriteSize,
                    SpiTransferCompleteCallback);
            }
        }

        // Inform caller async operation started
        NANOCLR_SET_AND_LEAVE(CLR_E_BUSY);
    }

    NANOCLR_NOCLEANUP();
}

HRESULT Library_com_sky_nf_dev_spi_native_Com_SkyworksInc_NanoFramework_Devices_Spi_SpiBus::
    NativeTransfer___VOID__I4__SystemSpanByte__SystemSpanByte__BOOLEAN(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    NANOCLR_CHECK_HRESULT(ExecuteTransfer(stack, true));

    NANOCLR_NOCLEANUP();
}

HRESULT Library_com_sky_nf_dev_spi_native_Com_SkyworksInc_NanoFramework_Devices_Spi_SpiBus::
    NativeTransfer___VOID__I4__SZARRAY_U2__SZARRAY_U2__BOOLEAN(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    NANOCLR_CHECK_HRESULT(ExecuteTransfer(stack, false));

    NANOCLR_NOCLEANUP();
}