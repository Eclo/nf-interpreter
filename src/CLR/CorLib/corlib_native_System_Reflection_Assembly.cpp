//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//
#include "CorLib.h"

HRESULT Library_corlib_native_System_Reflection_Assembly::get_FullName___STRING(CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

    // The defines for maxFULLNAME and parameters for snprintf are currently not validated.
    CLR_RT_Assembly_Instance instance;
    CLR_RT_Assembly *assm;
    char buffer[NANOCLR_MAX_ASSEMBLY_NAME * 2];
    const CLR_RECORD_ASSEMBLY *header;
    CLR_RT_HeapBlock *hbAsm = stack.Arg0().Dereference();

    NANOCLR_CHECK_HRESULT(GetTypeDescriptor(*hbAsm, instance));

    assm = instance.assembly;
    header = assm->header;

    if (hal_strlen_s(assm->name) > NANOCLR_MAX_ASSEMBLY_NAME)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    sprintf(
        buffer,
        "%s, Version=%d.%d.%d.%d",
        assm->name,
        header->version.majorVersion,
        header->version.minorVersion,
        header->version.buildNumber,
        header->version.revisionNumber);

    stack.SetResult_String(buffer);

    NANOCLR_NOCLEANUP();
#undef MAXFULLNAME
}

HRESULT Library_corlib_native_System_Reflection_Assembly::GetType___SystemType__STRING(CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

    CLR_RT_Assembly_Instance assm;
    CLR_RT_TypeDef_Index td;
    CLR_RT_HeapBlock *hbRef;
    CLR_RT_HeapBlock *hbObj;
    const char *szClass = stack.Arg1().RecoverString();
    CLR_RT_HeapBlock *hbAsm = stack.Arg0().Dereference();

    FAULT_ON_NULL(szClass);
    FAULT_ON_NULL(hbAsm);

    NANOCLR_CHECK_HRESULT(GetTypeDescriptor(*hbAsm, assm));

    hbRef = &stack.PushValueAndClear();

    if (g_CLR_RT_TypeSystem.FindTypeDef(szClass, assm.assembly, td))
    {
        NANOCLR_CHECK_HRESULT(g_CLR_RT_ExecutionEngine.NewObjectFromIndex(*hbRef, g_CLR_RT_WellKnownTypes.TypeStatic));

        hbObj = hbRef->Dereference();
        hbObj->SetReflection(td);
    }

    NANOCLR_NOCLEANUP();
}

HRESULT Library_corlib_native_System_Reflection_Assembly::GetTypes___SZARRAY_SystemType(CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

    CLR_RT_Assembly_Instance assm;
    CLR_RT_HeapBlock *hbAsm = stack.Arg0().Dereference();

    NANOCLR_CHECK_HRESULT(GetTypeDescriptor(*hbAsm, assm));

    {
        CLR_RT_Assembly *pASSM = assm.assembly;
        CLR_UINT32 num = pASSM->tablesSize[TBL_TypeDef];
        CLR_RT_HeapBlock &top = stack.PushValue();
        CLR_RT_HeapBlock *hbObj;

        NANOCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance(top, num, g_CLR_RT_WellKnownTypes.TypeStatic));

        if (num)
        {
            CLR_RT_HeapBlock *pArray = (CLR_RT_HeapBlock *)top.DereferenceArray()->GetFirstElement();

            for (CLR_UINT32 i = 0; i < num; i++, pArray++)
            {
                CLR_RT_TypeDef_Index index;
                index.Set(pASSM->assemblyIndex, i);

                NANOCLR_CHECK_HRESULT(
                    g_CLR_RT_ExecutionEngine.NewObjectFromIndex(*pArray, g_CLR_RT_WellKnownTypes.TypeStatic));

                hbObj = pArray->Dereference();
                hbObj->SetReflection(index);
            }
        }
    }

    NANOCLR_NOCLEANUP();
}

HRESULT Library_corlib_native_System_Reflection_Assembly::GetVersion___VOID__BYREF_I4__BYREF_I4__BYREF_I4__BYREF_I4(
    CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

    CLR_RT_StackFrame *caller = stack.Caller();
    if (caller == nullptr)
    {
        NANOCLR_SET_AND_LEAVE(S_OK);
    }
    else
    {
        CLR_RT_Assembly_Instance assm;
        CLR_RT_HeapBlock *hbAsm = stack.Arg0().Dereference();

        NANOCLR_CHECK_HRESULT(GetTypeDescriptor(*hbAsm, assm));

        const CLR_RECORD_VERSION &version = assm.assembly->header->version;

        // we do not check for the reference not to be NULL because this is an internal method
        stack.Arg1().Dereference()->NumericByRef().s4 = version.majorVersion;
        stack.Arg2().Dereference()->NumericByRef().s4 = version.minorVersion;
        stack.Arg3().Dereference()->NumericByRef().s4 = version.buildNumber;
        stack.Arg4().Dereference()->NumericByRef().s4 = version.revisionNumber;
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_corlib_native_System_Reflection_Assembly::GetManifestResourceNames___SZARRAY_STRING(
    CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

    CLR_RT_Assembly_Instance assm;
    CLR_RT_HeapBlock *hbAsm = stack.Arg0().Dereference();

    NANOCLR_CHECK_HRESULT(GetTypeDescriptor(*hbAsm, assm));

    {
        CLR_RT_Assembly *pAssm = assm.assembly;
        CLR_RT_HeapBlock &result = stack.PushValue();

        NANOCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance(
            result,
            pAssm->tablesSize[TBL_ResourcesFiles],
            g_CLR_RT_WellKnownTypes.String));

        {
            CLR_RT_HeapBlock *pArray = (CLR_RT_HeapBlock *)result.Array()->GetFirstElement();

            for (int indexResourceFile = 0; indexResourceFile < pAssm->tablesSize[TBL_ResourcesFiles];
                 indexResourceFile++)
            {
                const CLR_RECORD_RESOURCE_FILE *resourceFile = pAssm->GetResourceFile(indexResourceFile);

                NANOCLR_CHECK_HRESULT(
                    CLR_RT_HeapBlock_String::CreateInstance(*pArray, pAssm->GetString(resourceFile->name)));

                pArray++;
            }
        }
    }

    NANOCLR_NOCLEANUP();
}

HRESULT Library_corlib_native_System_Reflection_Assembly::GetExecutingAssembly___STATIC__SystemReflectionAssembly(
    CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

    CLR_RT_HeapBlock &top = stack.PushValueAndClear();
    CLR_RT_HeapBlock *hbObj;

    CLR_RT_StackFrame *caller = stack.Caller();
    if (caller == nullptr)
        NANOCLR_SET_AND_LEAVE(S_OK);

    {
        CLR_RT_Assembly_Index index;
        index.Set(caller->MethodCall().assembly->assemblyIndex);

        NANOCLR_CHECK_HRESULT(g_CLR_RT_ExecutionEngine.NewObjectFromIndex(top, g_CLR_RT_WellKnownTypes.Assembly));

        hbObj = top.Dereference();
        hbObj->SetReflection(index);
    }

    NANOCLR_NOCLEANUP();
}

HRESULT Library_corlib_native_System_Reflection_Assembly::
    LoadInternal___STATIC__SystemReflectionAssembly__STRING__BOOLEAN__I4__I4__I4__I4(CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

#if defined(NANOCLR_APPDOMAINS)
    CLR_RT_AppDomain *appDomain = g_CLR_RT_ExecutionEngine.GetCurrentAppDomain();
#endif
    CLR_RT_HeapBlock *pArgs = &stack.Arg0();
    CLR_RT_HeapBlock *hbObj;
    CLR_RT_Assembly *assembly;
    const char *szAssembly;
    CLR_RT_Assembly_Index index;
    bool fVersion;
    CLR_INT16 maj, min, build, rev;
    CLR_RT_HeapBlock &top = stack.PushValueAndClear();

    szAssembly = pArgs[0].RecoverString();
    FAULT_ON_NULL(szAssembly);
    fVersion = pArgs[1].NumericByRef().u1 != 0;
    maj = pArgs[2].NumericByRef().s4;
    min = pArgs[3].NumericByRef().s4;
    build = pArgs[4].NumericByRef().s4;
    rev = pArgs[5].NumericByRef().s4;

    if (fVersion && (maj == -1 || min == -1 || build == -1 || rev == -1))
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    if (fVersion)
    {
        CLR_RECORD_VERSION ver;

        ver.majorVersion = (CLR_UINT16)maj;
        ver.minorVersion = (CLR_UINT16)min;
        ver.buildNumber = (CLR_UINT16)build;
        ver.revisionNumber = (CLR_UINT16)rev;

        assembly = g_CLR_RT_TypeSystem.FindAssembly(szAssembly, &ver, true);
        FAULT_ON_NULL_HR(assembly, CLR_E_INVALID_PARAMETER);
    }
    else
    {
        assembly = g_CLR_RT_TypeSystem.FindAssembly(szAssembly, nullptr, false);
        FAULT_ON_NULL_HR(assembly, CLR_E_INVALID_PARAMETER);
    }

#if defined(NANOCLR_APPDOMAINS)
    NANOCLR_CHECK_HRESULT(appDomain->LoadAssembly(assembly));
#endif
    index.Set(assembly->assemblyIndex);

    NANOCLR_CHECK_HRESULT(g_CLR_RT_ExecutionEngine.NewObjectFromIndex(top, g_CLR_RT_WellKnownTypes.Assembly));

    hbObj = top.Dereference();
    hbObj->SetReflection(index);

    NANOCLR_CLEANUP();

    // Avoid exception handling in common case.  Just return NULL on failure.
    // Managed code decides to throw the exception or not.
    hr = S_OK;

    NANOCLR_CLEANUP_END();
}

HRESULT Library_corlib_native_System_Reflection_Assembly::Load___STATIC__SystemReflectionAssembly__SZARRAY_U1(
    CLR_RT_StackFrame &stack)
{
    NATIVE_PROFILE_CLR_CORE();
    NANOCLR_HEADER();

    CLR_RT_HeapBlock_Array *array = nullptr;
    CLR_RT_Assembly *assm = nullptr;
    CLR_RT_HeapBlock *hbObj;
    CLR_RECORD_ASSEMBLY *header;
    CLR_RT_Assembly_Index assemblyIndex;
    CLR_RT_HeapBlock hbTimeout;

    CLR_INT64 *timeoutTicks;
    bool eventResult = true;

    array = stack.Arg0().DereferenceArray();
    FAULT_ON_NULL(array);

    header = (CLR_RECORD_ASSEMBLY *)array->GetFirstElement();

    // !! need to cast to CLR_INT64 otherwise it wont setup a proper timeout
    hbTimeout.SetInteger((CLR_INT64)2 * CLR_RT_Thread::c_TimeQuantum_Milliseconds * TIME_CONVERSION__TO_MILLISECONDS);

    // setup timeout
    NANOCLR_CHECK_HRESULT(stack.SetupTimeoutFromTicks(hbTimeout, timeoutTicks));

    // parsing step only required in the first step
    if (stack.m_customState == 1)
    {
        if (header->GoodAssembly())
        {
            NANOCLR_CHECK_HRESULT(CLR_RT_Assembly::CreateInstance(header, assm));

            assm->file = array;

            g_CLR_RT_TypeSystem.Link(assm);

            NANOCLR_CHECK_HRESULT(g_CLR_RT_TypeSystem.ResolveAll());
            NANOCLR_CHECK_HRESULT(g_CLR_RT_TypeSystem.PrepareForExecution());

            CLR_RT_MethodDef_Index idx;
            idx.Set(assm->assemblyIndex, 0);

            if (assm->FindNextStaticConstructor(idx))
            {
                // need to execute static constructors
                g_CLR_RT_ExecutionEngine.SpawnStaticConstructor(g_CLR_RT_ExecutionEngine.m_cctorThread);

                // bump custom state so the read value above is pushed only once
                stack.m_customState = 2;
            }
            else
            {
                // no need to execute static constructors
                eventResult = false;
            }

            // push assembly index onto the eval stack
            stack.PushValueU4(assm->assemblyIndex);
        }
        else
        {
            NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
        }
    }

    // get assembly index from the eval stack
    assemblyIndex.Set(stack.m_evalStack[1].NumericByRef().u4);

    assm = g_CLR_RT_TypeSystem.m_assemblies[assemblyIndex.Assembly() - 1];

    while (eventResult)
    {
        if (assm->flags & CLR_RT_Assembly::StaticConstructorsExecuted)
        {
            // static constructors executed, we are good here
            break;
        }

        // non-blocking wait allowing other threads to run while we wait for the Tx operation to complete
        NANOCLR_CHECK_HRESULT(
            g_CLR_RT_ExecutionEngine.WaitEvents(stack.m_owningThread, *timeoutTicks, Event_NoEvent, eventResult))

        // check for failure
        if (!eventResult)
        {
            // can't happen!
            NANOCLR_SET_AND_LEAVE(CLR_E_FAIL);
        }
    }

    // pop assembly index from stack
    stack.PopValue();

    // pop timeout heap block from stack
    stack.PopValue();

    NANOCLR_CHECK_HRESULT(
        g_CLR_RT_ExecutionEngine.NewObjectFromIndex(stack.PushValue(), g_CLR_RT_WellKnownTypes.Assembly));

    hbObj = stack.TopValue().Dereference();
    hbObj->SetReflection(assemblyIndex);

    NANOCLR_CLEANUP();

    if (FAILED(hr) && hr != CLR_E_THREAD_WAITING)
    {
        if (assm)
        {
            assm->DestroyInstance();
        }
    }

    NANOCLR_CLEANUP_END();
}

//--//

HRESULT Library_corlib_native_System_Reflection_Assembly::GetTypeDescriptor(
    CLR_RT_HeapBlock &arg,
    CLR_RT_Assembly_Instance &inst)
{
    NATIVE_PROFILE_CLR_CORE();
    return CLR_RT_ReflectionDef_Index::Convert(arg, inst) ? S_OK : CLR_E_NULL_REFERENCE;
}
