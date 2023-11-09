//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include "nanoFramework_Graphics.h"

// clang-format off

static const CLR_RT_MethodHandler method_lookup[] =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::CharWidth___I4__CHAR,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::get_Height___I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::get_AverageWidth___I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::get_MaxWidth___I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::get_Ascent___I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::get_Descent___I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::get_InternalLeading___I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::get_ExternalLeading___I4,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::ComputeExtent___VOID__STRING__BYREF_I4__BYREF_I4__I4,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Font::ComputeTextInRect___VOID__STRING__BYREF_I4__BYREF_I4__I4__I4__I4__I4__U4,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::_ctor___VOID__I4__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::_ctor___VOID__SZARRAY_U1__nanoFrameworkUIBitmapBitmapImageType,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::Flush___VOID,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::Flush___VOID__I4__I4__I4__I4,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::Flush___VOID__I4__I4__I4__I4__I4__I4,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::Clear___VOID,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::SetClippingRectangle___VOID__I4__I4__I4__I4,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::get_Width___I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::get_Height___I4,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawImage___VOID__I4__I4__nanoFrameworkUIBitmap__I4__I4__I4__I4__U2,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::RotateImage___VOID__I4__I4__I4__nanoFrameworkUIBitmap__I4__I4__I4__I4__U2,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::StretchImage___VOID__I4__I4__nanoFrameworkUIBitmap__I4__I4__U2,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::GetBitmap___SZARRAY_U1,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::StretchImage___VOID__I4__I4__I4__I4__nanoFrameworkUIBitmap__I4__I4__I4__I4__U2,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::TileImage___VOID__I4__I4__nanoFrameworkUIBitmap__I4__I4__U2,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::Scale9Image___VOID__I4__I4__I4__I4__nanoFrameworkUIBitmap__I4__I4__I4__I4__U2,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::Dispose___VOID__BOOLEAN,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawChar___VOID__U2__I4__I4__U4__nanoFrameworkUIFont,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawEllipse___VOID__U4__I4__I4__I4__I4__I4__U4__I4__I4__U4__I4__I4__U2,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::MakeTransparent___VOID__U4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawLine___VOID__U4__I4__I4__I4__I4__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawRectangle___VOID__U4__I4__I4__I4__I4__I4__I4__I4__U4__I4__I4__U4__I4__I4__U2,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawRectangle___VOID__I4__I4__I4__I4__I4__U4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::FillGradientRectangle___VOID__I4__I4__I4__I4__U4__I4__I4__U4__I4__I4__U2,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::FillRectangle___VOID__I4__I4__I4__I4__U4__U2,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawRoundRectangle___VOID__I4__I4__I4__I4__I4__I4__I4__U4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::FillRoundRectangle___VOID__I4__I4__I4__I4__I4__I4__U4__U2,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawText___VOID__STRING__nanoFrameworkUIFont__U4__I4__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::SetPixel___VOID__I4__I4__U4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::GetPixelInt___U4__I4__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_Bitmap::DrawTextInRect___BOOLEAN__BYREF_STRING__BYREF_I4__BYREF_I4__I4__I4__I4__I4__U4__U4__nanoFrameworkUIFont,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::get_LongerSide___STATIC__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::get_ShorterSide___STATIC__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::get_ScreenWidth___STATIC__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::get_ScreenHeight___STATIC__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::get_BitsPerPixel___STATIC__I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::get_Orientation___STATIC__nanoFrameworkUIDisplayOrientation,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::Clear___STATIC__VOID,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::Write___STATIC__VOID__U2__U2__U2__U2__SZARRAY_U2,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::Write___STATIC__VOID__STRING__U2__U2__U2__U2__nanoFrameworkUIFont__U4__U4,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::NativeChangeOrientation___STATIC__BOOLEAN__nanoFrameworkUIDisplayOrientation,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::NativeInitSpi___STATIC__U4__nanoFrameworkUISpiConfiguration__nanoFrameworkUIScreenConfiguration__U4,
    Library_nanoFramework_Graphics_nanoFramework_UI_DisplayControl::NativeInitI2c___STATIC__U4__nanoFrameworkUII2cConfiguration__nanoFrameworkUIScreenConfiguration__U4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_Ink::SetInkRegion___STATIC__VOID__U4__I4__I4__I4__I4__I4__I4__I4__nanoFrameworkUIBitmap,
    Library_nanoFramework_Graphics_nanoFramework_UI_Ink::ResetInkRegion___STATIC__VOID,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchCollectorConfiguration::GetTouchPoints___STATIC__VOID__BYREF_I4__SZARRAY_I2__SZARRAY_I2,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchCollectorConfiguration::GetTouchInput___STATIC__VOID__nanoFrameworkUITouchCollectorConfigurationTouchInput__BYREF_I4__BYREF_I4__BYREF_I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchCollectorConfiguration::SetTouchInput___STATIC__VOID__nanoFrameworkUITouchCollectorConfigurationTouchInput__I4__I4__I4,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchEventProcessor::ProcessEvent___nanoFrameworkRuntimeEventsBaseEvent__U4__U4__SystemDateTime,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchPanel::SetCalibration___VOID__I4__SZARRAY_I2__SZARRAY_I2__SZARRAY_I2__SZARRAY_I2,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchPanel::GetCalibrationPointCount___VOID__BYREF_I4,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchPanel::StartCalibration___VOID,
    Library_nanoFramework_Graphics_nanoFramework_UI_TouchPanel::GetCalibrationPoint___VOID__I4__BYREF_I4__BYREF_I4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

const CLR_RT_NativeAssemblyData g_CLR_AssemblyNative_nanoFramework_Graphics =
{
    "nanoFramework.Graphics",
    0x6A3F90DD,
    method_lookup,
    { 100, 0, 0, 10 }
};

// clang-format on
