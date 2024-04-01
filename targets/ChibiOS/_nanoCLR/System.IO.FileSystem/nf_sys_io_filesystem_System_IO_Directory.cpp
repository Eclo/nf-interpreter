//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <nf_sys_io_filesystem.h>
#include <hal_littlefs.h>

extern SYSTEMTIME GetDateTimeFromStat(time_t *time);

static int CountEntries(lfs_t *fsDrive, const char *folderPath, bool isDirectory);
static HRESULT BuildPathsArray(lfs_t *fsDrive, const char *folderPath, CLR_RT_HeapBlock &storageItem, bool isDirectory);
static HRESULT GetItemsHandler(CLR_RT_StackFrame &stack, bool isDirectory);

void CombinePaths(char *outpath, const char *path1, const char *path2)
{
    strcat(outpath, path1);

    // Add "\" to path if required
    if (outpath[hal_strlen_s(outpath) - 1] != '\\')
    {
        strcat(outpath, "\\");
    }
    strcat(outpath, path2);
}

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

// TODO: add this when Windows.Storage APIs are removed
// int32_t GetInternalDriveIndex(char *drive)
// {
//     if (memcmp(drive, INTERNAL_DRIVE0_LETTER, sizeof(INTERNAL_DRIVE0_LETTER) - 1) == 0)
//     {
//         return 0;
//     }
//     if (memcmp(drive, INTERNAL_DRIVE1_LETTER, sizeof(INTERNAL_DRIVE1_LETTER) - 1) == 0)
//     {
//         return 1;
//     }

//     HAL_AssertEx();

//     return -1;
// }
extern int32_t GetInternalDriveIndex(char *drive);

#endif // NF_FEATURE_USE_LITTLEFS

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::ExistsNative___STATIC__BOOLEAN__STRING(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    int32_t driveIndex;
    char workingDrive[DRIVE_LETTER_LENGTH];
    lfs_dir_t *lfsDir = NULL;
    lfs_t *fsDrive = NULL;

    const char *workingPath = stack.Arg0().RecoverString();
    // check for null argument
    FAULT_ON_NULL_ARG(workingPath);

    // copy the first 2 letters of the path for the drive
    // path is 'D:\folder\file.txt', so we need 'D:'
    memcpy(workingDrive, workingPath, DRIVE_LETTER_LENGTH);

    // get littlefs drive index...
    driveIndex = GetInternalDriveIndex(workingDrive);
    //... and pointer to the littlefs instance
    fsDrive = hal_lfs_get_fs_from_index(driveIndex);

    // enough to check if the directory can be opened
    stack.SetResult_Boolean(lfs_dir_open(lfs, lfsDir, workingPath) == LFS_ERR_OK);

    // need to close the directory
    lfs_dir_close(fsDrive, lfsDir);

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::MoveNative___STATIC__VOID__STRING__STRING(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    int32_t driveIndexSrc = 0;
    int32_t driveIndexDest = 0;
    int32_t operationResult;
    char workingDriveSrc[DRIVE_LETTER_LENGTH];
    lfs_t *fsDriveSrc = NULL;

    const char *filePathSrc = stack.Arg0().RecoverString();
    const char *filePathDest = stack.Arg1().RecoverString();

    FAULT_ON_NULL_ARG(filePathSrc);
    FAULT_ON_NULL_ARG(filePathDest);

    // copy the first 2 letters of the path for the drive
    // path is 'D:\folder\file.txt', so we need 'D:'
    memcpy(workingDriveSrc, filePathSrc, DRIVE_LETTER_LENGTH);

    // get littlefs drive index...
    driveIndexSrc = GetInternalDriveIndex(workingDriveSrc);

    // littlefs can only move folders within the same drive
    if (driveIndexSrc != driveIndexDest)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    //... and pointer to the littlefs instance
    fsDriveSrc = hal_lfs_get_fs_from_index(driveIndexSrc);

    operationResult = lfs_rename(fsDriveSrc, filePathSrc, filePathDest);

    if (operationResult == LFS_ERR_NOTEMPTY)
    {
        // directory not empty, cannot delete
        NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_EMPTY);
    }
    else if (operationResult == LFS_ERR_NOENT)
    {
        // directory doesn't exist
        NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_FOUND);
    }
    else if (operationResult != LFS_ERR_OK)
    {
        // failed to move the directory
        NANOCLR_SET_AND_LEAVE(CLR_E_FAIL);
    }

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::DeleteNative___STATIC__VOID__STRING(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    int32_t driveIndex;
    int32_t operationResult;
    char workingDrive[DRIVE_LETTER_LENGTH];
    lfs_t *fsDrive = NULL;

    const char *workingPath = stack.Arg0().RecoverString();
    FAULT_ON_NULL_ARG(workingPath);

    // copy the first 2 letters of the path for the drive
    // path is 'D:\folder\file.txt', so we need 'D:'
    memcpy(workingDrive, workingPath, DRIVE_LETTER_LENGTH);

    // get littlefs drive index...
    driveIndex = GetInternalDriveIndex(workingDrive);

    //... and pointer to the littlefs instance
    fsDrive = hal_lfs_get_fs_from_index(driveIndex);

    // delete folder
    operationResult = lfs_remove(fsDrive, workingPath);

    if (operationResult == LFS_ERR_NOTEMPTY)
    {
        // directory not empty, cannot delete
        NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_EMPTY);
    }
    else if (operationResult == LFS_ERR_NOENT)
    {
        // directory doesn't exist
        NANOCLR_SET_AND_LEAVE(CLR_E_DIRECTORY_NOT_FOUND);
    }
    else if (operationResult != LFS_ERR_OK)
    {
        // failed to delete the directory
        NANOCLR_SET_AND_LEAVE(CLR_E_FAIL);
    }

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::GetDirectoriesNative___STATIC__SZARRAY_STRING__STRING(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    NANOCLR_CHECK_HRESULT(GetItemsHandler(stack, true));

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::GetFilesNative___STATIC__SZARRAY_STRING__STRING(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    NANOCLR_CHECK_HRESULT(GetItemsHandler(stack, false));

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::CreateNative___STATIC__VOID__STRING(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    int32_t driveIndex;
    int32_t operationResult;
    char workingDrive[DRIVE_LETTER_LENGTH];
    lfs_t *fsDrive = NULL;

    const char *workingPath = stack.Arg0().RecoverString();
    FAULT_ON_NULL_ARG(workingPath);

    // copy the first 2 letters of the path for the drive
    // path is 'D:\folder\file.txt', so we need 'D:'
    memcpy(workingDrive, workingPath, DRIVE_LETTER_LENGTH);

    // get littlefs drive index...
    driveIndex = GetInternalDriveIndex(workingDrive);

    //... and pointer to the littlefs instance
    fsDrive = hal_lfs_get_fs_from_index(driveIndex);

    // create directory
    operationResult = lfs_mkdir(fsDrive, workingPath);

    if (operationResult == LFS_ERR_EXIST)
    {
        // folder already exists
        NANOCLR_SET_AND_LEAVE(CLR_E_PATH_ALREADY_EXISTS);
    }
    else if (operationResult != LFS_ERR_OK)
    {
        // failed to create the directory
        NANOCLR_SET_AND_LEAVE(CLR_E_FAIL);
    }

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

static int CountEntries(lfs_t *fsDrive, const char *folderPath, bool isDirectory)
{
    uint16_t count = 0;

    uint32_t operationResult;
    lfs_dir_t *lfsDir = NULL;
    lfs_info info;

    // open directory
    operationResult = lfs_dir_open(fsDrive, lfsDir, folderPath);

    if (operationResult != LFS_ERR_OK)
    {
        return operationResult;
    }

    // count entries
    while (lfs_dir_read(fsDrive, lfsDir, &info) > 0)
    {
        if (isDirectory && info.type == LFS_TYPE_DIR)
        {
            // directory entry
            count++;
        }
        else
        {
            // file entry
            count++;
        }
    }

    // close directory
    lfs_dir_close(fsDrive, lfsDir);

    return count;
}

static HRESULT BuildPathsArray(lfs_t *fsDrive, const char *folderPath, CLR_RT_HeapBlock &storageItem, bool isDirectory)
{
    NANOCLR_HEADER();

    char *stringBuffer = NULL;

    uint32_t operationResult;
    lfs_dir_t *lfsDir = NULL;
    lfs_info info;
    CLR_RT_HeapBlock *pathEntry;

    // open directory
    operationResult = lfs_dir_open(fsDrive, lfsDir, folderPath);

    if (operationResult != LFS_ERR_OK)
    {
        return operationResult;
    }

    // get a pointer to the first object in the array (which is of type <String>)
    pathEntry = (CLR_RT_HeapBlock *)storageItem.DereferenceArray()->GetFirstElement();

    // allocate memory for buffers
    stringBuffer = (char *)platform_malloc(LFS_NAME_MAX + 1);

    // sanity check for successful malloc
    if (stringBuffer == NULL)
    {
        // failed to allocate memory
        NANOCLR_SET_AND_LEAVE(CLR_E_OUT_OF_MEMORY);
    }

    // list entries
    while (lfs_dir_read(fsDrive, lfsDir, &info) > 0)
    {
        if (isDirectory && info.type == LFS_TYPE_DIR)
        {
            // directory entry

            // compose file path
            CombinePaths(stringBuffer, folderPath, info.name);

            // set file full path in array of strings
            NANOCLR_CHECK_HRESULT(CLR_RT_HeapBlock_String::CreateInstance(*pathEntry, stringBuffer));
        }
        else
        {
            // file entry

            // compose file path
            CombinePaths(stringBuffer, folderPath, info.name);

            // set file full path in array of strings
            NANOCLR_CHECK_HRESULT(CLR_RT_HeapBlock_String::CreateInstance(*pathEntry, stringBuffer));
        }

        // move the file array pointer to the next item in the array
        pathEntry++;
    }

    NANOCLR_CLEANUP();

    if (stringBuffer != NULL)
    {
        platform_free(stringBuffer);
    }

    // close directory
    lfs_dir_close(fsDrive, lfsDir);

    NANOCLR_CLEANUP_END();
}

static HRESULT GetItemsHandler(CLR_RT_StackFrame &stack, bool isDirectory)
{
    NANOCLR_HEADER();

    int32_t entriesCount;
    int32_t driveIndex;
    char workingDrive[DRIVE_LETTER_LENGTH];
    lfs_t *fsDrive = NULL;

    CLR_RT_HeapBlock &top = stack.PushValue();
    CLR_RT_HeapBlock *storageItem;

    const char *workingPath = stack.Arg0().RecoverString();
    FAULT_ON_NULL_ARG(workingPath);

    // copy the first 2 letters of the path for the drive
    // path is 'D:\folder\file.txt', so we need 'D:'
    memcpy(workingDrive, workingPath, DRIVE_LETTER_LENGTH);

    // get littlefs drive index...
    driveIndex = GetInternalDriveIndex(workingDrive);

    //... and pointer to the littlefs instance
    fsDrive = hal_lfs_get_fs_from_index(driveIndex);

    entriesCount = CountEntries(fsDrive, workingPath, isDirectory);

    if (entriesCount != LFS_ERR_OK)
    {
        // failed to change drive
        NANOCLR_SET_AND_LEAVE(CLR_E_VOLUME_NOT_FOUND);
    }

    // create an array of files paths <String>
    NANOCLR_CHECK_HRESULT(
        CLR_RT_HeapBlock_Array::CreateInstance(top, (CLR_UINT32)entriesCount, g_CLR_RT_WellKnownTypes.m_String));

    if (entriesCount > 0)
    {
        // get a pointer to the first object in the array
        storageItem = (CLR_RT_HeapBlock *)top.DereferenceArray()->GetFirstElement();

        // 2nd pass fill directory path names
        NANOCLR_CHECK_HRESULT(BuildPathsArray(fsDrive, workingPath, *storageItem, isDirectory))
    }

    NANOCLR_NOCLEANUP();
}

#endif // NF_FEATURE_USE_LITTLEFS

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::GetLogicalDrivesNative___STATIC__SZARRAY_STRING(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    uint32_t driveCount = 0;
    char workingDrive[sizeof(DRIVE_PATH_LENGTH)];

    CLR_RT_HeapBlock *driveEntry;
    CLR_RT_HeapBlock &top = stack.PushValue();

    // is the littlefs file system available and mounted?
    if (lfsFileSystemReady)
    {
        // get littlefs instances count
        driveCount = hal_lfs_get_instances_count();
    }

    // start composing the reply
    // create an array of files paths <String> for count drives
    NANOCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance(top, driveCount, g_CLR_RT_WellKnownTypes.m_String));

    // get a pointer to the first object in the array
    driveEntry = (CLR_RT_HeapBlock *)top.DereferenceArray()->GetFirstElement();

    for (uint16_t driveIterator = 0; driveIterator < driveCount; driveIterator++)
    {
        // littlefs is mounted

        // fill the folder name and path
        switch (driveIterator)
        {
            case 0:
                memcpy(workingDrive, INTERNAL_DRIVE0_PATH, DRIVE_PATH_LENGTH);
                break;

            case 1:
                memcpy(workingDrive, INTERNAL_DRIVE1_PATH, DRIVE_PATH_LENGTH);
                break;

            default:
                HAL_AssertEx();
                NANOCLR_SET_AND_LEAVE(CLR_E_FAIL);
        }

        // create an instance of <String>
        CLR_RT_HeapBlock_String::CreateInstance(*driveEntry, workingDrive);

        // move pointer to the next drive item
        driveEntry++;
    }

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nf_sys_io_filesystem_System_IO_Directory::GetLastWriteTimeNative___STATIC__SystemDateTime__STRING(
    CLR_RT_StackFrame &stack)
{
    (void)stack;

    NANOCLR_HEADER();

#if defined(NF_FEATURE_USE_LITTLEFS) && (NF_FEATURE_USE_LITTLEFS == TRUE)

    // not supported in this platform
    NANOCLR_SET_AND_LEAVE(CLR_E_NOT_SUPPORTED);

#else

    stack.NotImplementedStub();

#endif

    NANOCLR_NOCLEANUP();
}
