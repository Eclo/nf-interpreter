//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "nano_gg_adc_native.h"
#include "nano_gg_adc_native_target.h"

#define ADC_IMPOSSIBLE_CLOCK 90000000UL

#if GECKO_USE_ADC0
ADC_Init_TypeDef adc0Init;
bool adc0Initialized = false;
#endif
#if GECKO_USE_ADC1
ADC_Init_TypeDef adc1Init;
bool adc1Initialized = false;
#endif

NF_PAL_GECKO_ADC_CONTINUOUS_SCAN *ContinuousScanOperation;

// add typedef for AdcConfiguration to ease access and improve readability
typedef Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcConfiguration AdcConfiguration;

extern void ParseAdcChannelConfig(CLR_RT_HeapBlock *channelConfiguration, void *adcInit);

// helper function to take care of init and config ADC, if not already done
HRESULT OpenAdcChannel(int32_t channelNumber, CLR_RT_HeapBlock *adcConfiguration, ADC_TypeDef *adcDriver)
{
    NANOCLR_HEADER();

    NF_PAL_ADC_PORT_PIN_CHANNEL adcChannelDefinition;
    CMU_Clock_TypeDef adcClock;
    ADC_Init_TypeDef *adcInit = NULL;
    bool *adcInitialized = NULL;

    // sanity check for existing configuration
    if (channelNumber >= AdcChannelCount)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    // grab ADC channel definition
    adcChannelDefinition = AdcPortPinConfig[channelNumber];

    // we should remove from the build the ADC options that aren't implemented
    // plus we have to use the default to catch invalid ADC Ids
    switch (adcChannelDefinition.adcIndex)
    {

#if GECKO_USE_ADC0
        case 0:
            adcDriver = ADC0;
            adcClock = cmuClock_ADC0;
            adcInit = &adc0Init;
            adcInitialized = &adc0Initialized;
            break;
#endif

#if GECKO_USE_ADC1
        case 1:
            adcDriver = ADC1;
            adcClock = cmuClock_ADC1;
            adcInit = &adc1Init;
            adcInitialized = &adc1Initialized;
            break;
#endif

        default:
            NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    // is this ADC already initialized?
    if (
#if GECKO_USE_ADC0
        (adcDriver == ADC0 && !adcInitialized)
#endif
#if GECKO_USE_ADC0 && GECKO_USE_ADC1
        ||
#endif
#if GECKO_USE_ADC1
        (adcDriver == ADC1 && !adcInitialized)
#endif
    )
    {
        // init with default values
        *adcInit = ADC_INIT_DEFAULT;

        // now map the AdcConfiguration object to the native structure
        adcInit->ovsRateSel =
            (ADC_OvsRateSel_TypeDef)adcConfiguration[AdcConfiguration::FIELD___oversampleRate].NumericByRef().s4;

#if defined(_ADC_CTRL_LPFMODE_MASK)
        adcInit->lpfMode =
            (ADC_LPFilter_TypeDef)adcConfiguration[AdcConfiguration::FIELD___lowpassFilterMode].NumericByRef().s4;
#endif

        adcInit->warmUpMode =
            (ADC_Warmup_TypeDef)adcConfiguration[AdcConfiguration::FIELD___warmUpMode].NumericByRef().s4;
        adcInit->tailgate = (bool)adcConfiguration[AdcConfiguration::FIELD___tailgating].NumericByRef().u1;

        // Enable ADC clock
        CMU_ClockEnable(cmuClock_HFPER, true);
        CMU_ClockEnable(adcClock, true);

        // init to max possible ADC clock
        adcInit->prescale = ADC_PrescaleCalc(ADC_IMPOSSIBLE_CLOCK, 0);
        // let the drivers compute the appropriate value for the reference clock
        adcInit->timebase = ADC_TimebaseCalc(0);

#if defined(_ADC_CTRL_ADCCLKMODE_MASK)
        adcInit->em2ClockConfig = adcEm2ClockOnDemand;
#endif

        // init ADC
        ADC_Init(adcDriver, adcInit);

        // set ADC initialized flag
        *adcInitialized = true;
    }

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::NativeInit___VOID(
    CLR_RT_StackFrame &stack)
{
    (void)stack;

    NANOCLR_HEADER();

    // all required initialization for ADC is handled in OpenChannel call

    NANOCLR_NOCLEANUP_NOLABEL();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::NativeOpenChannel___VOID__I4(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    CLR_RT_HeapBlock *adcConfiguration;
    int32_t channelNumber;
    ADC_TypeDef *adcDriver;

    // get a pointer to the managed object instance and check that it's not NULL
    CLR_RT_HeapBlock *pThis = stack.This();
    FAULT_ON_NULL(pThis);

    // get a pointer to the managed AdcConfiguration object instance
    adcConfiguration = pThis[FIELD___adcConfiguration].Dereference();

    // Get channel from argument
    channelNumber = stack.Arg1().NumericByRef().s4;

    // take care of configuring ADC, if not already done
    NANOCLR_CHECK_HRESULT(OpenAdcChannel(channelNumber, adcConfiguration, adcDriver));

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::NativeGetChannelCount___I4(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    // Return value to the managed application
    stack.SetResult_I4(AdcChannelCount);

    NANOCLR_NOCLEANUP_NOLABEL();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::
    NativeIsChannelModeSupported___BOOLEAN__I4(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    int mode = stack.Arg1().NumericByRef().s4;

    // Only support Single ended mode for now
    stack.SetResult_Boolean((mode == (int)AdcChannelMode_SingleEnded));

    NANOCLR_NOCLEANUP_NOLABEL();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::
    NativeGetSupportedResolutionsInBits___SZARRAY_nanoFrameworkGiantGeckoAdcSampleResolution(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    CLR_RT_HeapBlock *adcSampleResolution;
    CLR_RT_TypeDef_Index adcSampleResolutionTypeDef;
    CLR_RT_HeapBlock *hbObj;
    CLR_RT_HeapBlock &top = stack.PushValue();

    uint16_t resolutionsCount = 0;

#if defined(_ADC_SINGLECTRL_RES_12BIT)
    resolutionsCount++;
#endif
#if defined(_ADC_SINGLECTRL_RES_8BIT)
    resolutionsCount++;
#endif
#if defined(_ADC_SINGLECTRL_RES_6BIT)
    resolutionsCount++;
#endif
#if defined(_ADC_SINGLECTRL_RES_OVS)
    resolutionsCount++;
#endif

    // start composing the reply
    // find <SampleResolution> type definition, don't bother checking the result as it exists for sure
    g_CLR_RT_TypeSystem.FindTypeDef("SampleResolution", "nanoFramework.GiantGecko.Adc", adcSampleResolutionTypeDef);

    // create an array of <SampleResolution>
    NANOCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance(top, resolutionsCount, adcSampleResolutionTypeDef));

    if (resolutionsCount > 0)
    {
        // get a pointer to the first object in the array (which is of type <SampleResolution>)
        adcSampleResolution = (CLR_RT_HeapBlock *)top.DereferenceArray()->GetFirstElement();

        // create an instance of <SampleResolution>
        NANOCLR_CHECK_HRESULT(
            g_CLR_RT_ExecutionEngine.NewObjectFromIndex(*adcSampleResolution, adcSampleResolutionTypeDef));

#if defined(_ADC_SINGLECTRL_RES_12BIT)
        hbObj = adcSampleResolution->Dereference();
        hbObj->SetInteger((CLR_INT32)adcRes12Bit);
        hbObj->PerformBoxingIfNeeded();

        // move pointer to the next resolution item
        adcSampleResolution++;
#endif

#if defined(_ADC_SINGLECTRL_RES_8BIT)
        hbObj = adcSampleResolution->Dereference();
        hbObj->SetInteger((CLR_INT32)adcRes8Bit);
        hbObj->PerformBoxingIfNeeded();

        // move pointer to the next resolution item
        adcSampleResolution++;
#endif

#if defined(_ADC_SINGLECTRL_RES_6BIT)
        hbObj = adcSampleResolution->Dereference();
        hbObj->SetInteger((CLR_INT32)adcResOVS);
        hbObj->PerformBoxingIfNeeded();

        // move pointer to the next resolution item
        adcSampleResolution++;
#endif

#if defined(_ADC_SINGLECTRL_RES_6BIT)
        // dereference the object in order to reach its fields
        hbObj = adcSampleResolution->Dereference();
        hbObj->SetInteger((CLR_INT32)adcRes6Bit);
        hbObj->PerformBoxingIfNeeded();
#endif
    }

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::
    NativeStartContinuousConversion___VOID__SZARRAY_I4__I4(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    uint32_t averageCount;
    uint32_t channelIndex = 0;
    int32_t channelNumber;
    ADC_InitScan_TypeDef channelInitScan = ADC_INITSCAN_DEFAULT;
    ADC_TypeDef *adcDriver = NULL;

    NF_PAL_ADC_PORT_PIN_CHANNEL adcChannelDefinition;

    CLR_RT_HeapBlock_Array *adcChannelsToScan;
    CLR_RT_HeapBlock *adcConfiguration;

    // get a pointer to the managed object instance and check that it's not NULL
    CLR_RT_HeapBlock *pThis = stack.This();
    FAULT_ON_NULL(pThis);

    // get the average count
    averageCount = stack.Arg2().NumericByRef().s4;

    // sanity check (need to take at least one sample)
    if (averageCount < 1)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    // get a pointer to the  AdcChannelConfiguration object instance
    ParseAdcChannelConfig(pThis[FIELD___adcChannelConfiguration].Dereference(), &channelInitScan);
    // enable FIFO overflow to overwrite old data
    channelInitScan.fifoOverwrite = true;

    // get a pointer to the managed AdcConfiguration object instance
    adcConfiguration = pThis[FIELD___adcConfiguration].Dereference();

    // loop through all channels
    adcChannelsToScan = (CLR_RT_HeapBlock_Array *)stack.Arg1().DereferenceArray();

    // sanity check (need to have at least one channel)
    if (adcChannelsToScan->m_numOfElements < 1)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_INVALID_PARAMETER);
    }

    // alloc memory for the scan operation
    ContinuousScanOperation =
        (NF_PAL_GECKO_ADC_CONTINUOUS_SCAN *)platform_malloc(sizeof(NF_PAL_GECKO_ADC_CONTINUOUS_SCAN));

    // sanity check
    if (ContinuousScanOperation == NULL)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_OUT_OF_MEMORY);
    }

    // alloc memory for the data buffer
    ContinuousScanOperation->dataBuffer =
        (uint32_t *)platform_malloc(adcChannelsToScan->m_numOfElements * averageCount * sizeof(uint32_t));

    // sanity check
    if (ContinuousScanOperation->dataBuffer == NULL)
    {
        NANOCLR_SET_AND_LEAVE(CLR_E_OUT_OF_MEMORY);
    }

    // clear the data buffer
    memset(
        ContinuousScanOperation->dataBuffer,
        0,
        adcChannelsToScan->m_numOfElements * averageCount * sizeof(uint32_t));

    // store the number of channels
    ContinuousScanOperation->channelCount = adcChannelsToScan->m_numOfElements;
    // store the average count
    ContinuousScanOperation->averageCount = averageCount;

    while (channelIndex < ContinuousScanOperation->channelCount)
    {
        channelNumber = ((CLR_RT_HeapBlock *)adcChannelsToScan->GetElement(channelIndex++))->NumericByRefConst().s4;

        // take care of configuring ADC, if not already done
        NANOCLR_CHECK_HRESULT(OpenAdcChannel(channelNumber, adcConfiguration, adcDriver));

        // grab ADC channel definition
        adcChannelDefinition = AdcPortPinConfig[channelNumber];

        // select ADC input
        ADC_ScanSingleEndedInputAdd(&channelInitScan, adcScanInputGroup0, adcChannelDefinition.posSel);
    }

    // set scan data valid level (DVL) to 2
    adcDriver->SCANCTRLX |= (ContinuousScanOperation->channelCount - 1) << _ADC_SCANCTRLX_DVL_SHIFT;

    // clear ADC Scan FIFO
    adcDriver->SCANFIFOCLEAR = ADC_SCANFIFOCLEAR_SCANFIFOCLEAR;

    // start ADC scan
    ADC_InitScan(adcDriver, &channelInitScan);

    // clearn and enable Scan interrupts
    ADC_IntClear(adcDriver, ADC_IEN_SCAN);
    ADC_IntEnable(adcDriver, ADC_IEN_SCAN);

    // Enable ADC Interrupts
    NVIC_ClearPendingIRQ(ADC0_IRQn);
    NVIC_EnableIRQ(ADC0_IRQn);

    // done here: update flag
    pThis[FIELD___continuousSamplingStarted].NumericByRef().u1 = (CLR_UINT8) true;

    NANOCLR_CLEANUP();

    // clean up if needed
    if (FAILED(hr))
    {
        // free memory for the scan operation
        if (ContinuousScanOperation != NULL)
        {
            if (ContinuousScanOperation->dataBuffer != NULL)
            {
                platform_free(ContinuousScanOperation->dataBuffer);
            }

            platform_free(ContinuousScanOperation);

            ContinuousScanOperation = NULL;
        }
    }

    NANOCLR_CLEANUP_END();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::NativeStopContinuousConversion___VOID(
    CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    // get a pointer to the managed object instance and check that it's not NULL
    CLR_RT_HeapBlock *pThis = stack.This();
    FAULT_ON_NULL(pThis);

    // disable ADC Interrupt
    NVIC_DisableIRQ(ADC0_IRQn);

    // clear memory for the scan operation
    platform_free(ContinuousScanOperation->dataBuffer);
    platform_free(ContinuousScanOperation);
    ContinuousScanOperation = NULL;

    // all good, update flag
    pThis[FIELD___continuousSamplingStarted].NumericByRef().u1 = (CLR_UINT8) false;

    NANOCLR_NOCLEANUP();
}

HRESULT Library_nano_gg_adc_native_nanoFramework_GiantGecko_Adc_AdcController::
    NativeGetLastContinuousSamples___SZARRAY_I4(CLR_RT_StackFrame &stack)
{
    NANOCLR_HEADER();

    uint64_t samplesAccumulator = 0;

    CLR_RT_HeapBlock_Array *sampleArray;
    CLR_RT_HeapBlock &top = stack.PushValue();

    // create an array of <int>
    NANOCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance(
        top,
        ContinuousScanOperation->channelCount,
        g_CLR_RT_WellKnownTypes.m_Int32));

    sampleArray = top.DereferenceArray();

    for (uint32_t channelIndex = 0; channelIndex < ContinuousScanOperation->channelCount; channelIndex++)
    {
        // // Read data from ADC
        // data = ADC_DataIdScanGet(ADC0, &id);

        // ContinuousScanOperation
        //     ->dataBuffer[i * ContinuousScanOperation->averageCount + ContinuousScanOperation->currentIndex] = data;

        // compute average
        // 1. accumulate samples
        for (uint32_t sampleIndex = 0; sampleIndex < ContinuousScanOperation->averageCount; sampleIndex++)
        {
            samplesAccumulator +=
                ContinuousScanOperation->dataBuffer[channelIndex * ContinuousScanOperation->averageCount + sampleIndex];
        }

        // 2. set array element with the average
        ((CLR_RT_HeapBlock *)sampleArray->GetElement(channelIndex))
            ->SetInteger((CLR_INT32)(samplesAccumulator / ContinuousScanOperation->averageCount));
    }

    NANOCLR_NOCLEANUP();
}

// IRQ handler for ADC0
void ADC0_IRQHandler(void)
{
    uint32_t data, i, scanId;

    // Get ADC results
    for (i = 0; i < ContinuousScanOperation->channelCount; i++)
    {
        // Read data from ADC
        data = ADC_DataIdScanGet(ADC0, &scanId);

        ContinuousScanOperation
            ->dataBuffer[i * ContinuousScanOperation->averageCount + ContinuousScanOperation->currentIndex] = data;
    }

    // increment the index
    ContinuousScanOperation->currentIndex++;

    // check index
    if (ContinuousScanOperation->currentIndex == ContinuousScanOperation->averageCount)
    {
        // reset index
        ContinuousScanOperation->currentIndex = 0;
    }

    // Start next ADC conversion
    ADC_Start(ADC0, adcStartScan);
}
