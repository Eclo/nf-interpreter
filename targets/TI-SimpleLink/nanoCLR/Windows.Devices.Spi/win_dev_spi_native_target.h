//
// Copyright (c) 2017 The nanoFramework project contributors
// See LICENSE file in the project root for full license information.
//


#ifndef _WIN_DEV_SPI_NATIVE_TARGET_H_
#define _WIN_DEV_SPI_NATIVE_TARGET_H_

#include <win_dev_spi_native.h>
#include "Board.h"
#include <ti/drivers/SPI.h>

// struct representing the SPI 
typedef struct
{
    SPI_Handle          masterSpi;
    SPI_Params          spiParams;
    SPI_Transaction*    transactions;
    uint8_t             transactionCount;
} NF_PAL_SPI;

///////////////////////////////////////////
// declaration of the the SPI PAL strucs //
///////////////////////////////////////////
extern NF_PAL_SPI SPI1_PAL;

#endif  //_WIN_DEV_SPI_NATIVE_TARGET_H_
