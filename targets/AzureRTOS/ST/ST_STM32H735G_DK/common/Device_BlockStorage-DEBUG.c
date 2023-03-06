//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <nanoHAL_Types.h>
#include <nanoPAL_BlockStorage.h>

// 128kB blocks
const BlockRange BlockRange1[] = {
    // 08000000 nanoBooter
    {BlockRange_BLOCKTYPE_BOOTSTRAP, 0, 0},

    ///////////////////////////////////////////////////////////////////////////////////////
    // because this target is using a configuration block need to add the
    // configuration manager files to the CMake and call ConfigurationManager_Initialize()
    // in nanoBooter so the configuration can be managed when in booter mode
    ///////////////////////////////////////////////////////////////////////////////////////
    // 08020000 configuration block
    {BlockRange_BLOCKTYPE_CONFIG, 1, 1},
    ///////////////////////////////////////////////////////////////////////////////////////

    // 08040000 nanoCLR
    {BlockRange_BLOCKTYPE_CODE, 2, 7},
};

const BlockRegionInfo BlockRegions[] = {
    {
        // STM32H72x/3X devices flash has 256 bits width programming
        (BlockRegionAttribute_ProgramWidthIs256bits),
        // start address for block region
        0x08000000,
        // total number of blocks in this region
        8,
        // total number of bytes per block
        0x20000,
        ARRAYSIZE_CONST_EXPR(BlockRange1),
        BlockRange1,
    },
};

const DeviceBlockInfo Device_BlockInfo = {
    // STM32 flash memory is XIP
    (MediaAttribute_SupportsXIP),
    // UINT32 BytesPerSector
    2,
    // UINT32 NumRegions;
    ARRAYSIZE_CONST_EXPR(BlockRegions),
    // const BlockRegionInfo* pRegions;
    (BlockRegionInfo *)BlockRegions,
};

MEMORY_MAPPED_NOR_BLOCK_CONFIG Device_BlockStorageConfig = {
    {
        // BLOCK_CONFIG
        {
            0,     // GPIO_PIN             Pin;
            false, // BOOL                 ActiveState;
        },

        (DeviceBlockInfo *)&Device_BlockInfo, // BlockDeviceinfo
    },

    {
        // CPU_MEMORY_CONFIG
        0,          // UINT8  CPU_MEMORY_CONFIG::ChipSelect;
        true,       // UINT8  CPU_MEMORY_CONFIG::ReadOnly;
        0,          // UINT32 CPU_MEMORY_CONFIG::WaitStates;
        0,          // UINT32 CPU_MEMORY_CONFIG::ReleaseCounts;
        16,         // UINT32 CPU_MEMORY_CONFIG::BitWidth;
        0x08000000, // UINT32 CPU_MEMORY_CONFIG::BaseAddress;
        0x00200000, // UINT32 CPU_MEMORY_CONFIG::SizeInBytes;
        0,          // UINT8  CPU_MEMORY_CONFIG::XREADYEnable
        0,          // UINT8  CPU_MEMORY_CONFIG::ByteSignalsForRead
        0,          // UINT8  CPU_MEMORY_CONFIG::ExternalBufferEnable
    },

    0, // UINT32 ChipProtection;
    0, // UINT32 ManufacturerCode;
    0, // UINT32 DeviceCode;
};

BlockStorageDevice Device_BlockStorage;
