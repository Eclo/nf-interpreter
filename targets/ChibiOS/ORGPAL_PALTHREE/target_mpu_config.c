//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <ch.h>
#include <hal.h>
#include <stm32_registry.h>
#include <hal_nf_community.h>

extern void Target_ExternalMemoryConfigMPU();

void Target_ConfigNonCacheableMemory()
{
    // region
    MPU->RNR = ((uint32_t)MPU_REGION_1);

    // base address
    MPU->RBAR = ((uint32_t)0x20000000U);

    // size and other configs
    MPU->RASR =
        ((uint32_t)MPU_RASR_ATTR_AP_RW_RW | MPU_RASR_ATTR_NON_CACHEABLE | MPU_RASR_ATTR_S | MPU_RASR_SIZE_128K |
         MPU_RASR_ENABLE);
}

void Target_ConfigMPU()
{
    // disable MPU
    HAL_MPU_Disable();

    // config MPU for external memory
    Target_ExternalMemoryConfigMPU();

    // config MPU for non cacheable memory
    Target_ConfigNonCacheableMemory();

    // enable MPU
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
