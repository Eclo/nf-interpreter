//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#ifndef NF_FILEX_H_
#define NF_FILEX_H_

#include <nanoHAL_v2.h>
#include <target_fx_user.h>
#include <fx_api.h>

#ifdef __cplusplus
extern "C"
{
#endif

    uint32_t NF_FileX_Init(void);
    void NF_FileX_UnInit(void);

    void FileXThread_entry(uint32_t parameter);

#ifdef __cplusplus
}
#endif

#endif // NF_FILEX_H_
