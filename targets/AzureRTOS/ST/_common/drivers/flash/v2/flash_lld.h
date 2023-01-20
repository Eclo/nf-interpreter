//
// Copyright (c) .NET Foundation and Contributors
// Portions Copyright (c) 2016 STMicroelectronics. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef FLASH_LLD_H
#define FLASH_LLD_H

#include <stm32f7xx_hal.h>

#define FLASH_ERASED_WORD 0x0FFFFFFFFU

// FLASHEx_Sectors FLASH Sectors
/*-------------------------------------- STM32F42xxx/STM32F43xxx/STM32F469xx ------------------------------------*/
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||                    \
    defined(STM32F469xx) || defined(STM32F479xx)

#define FLASH_SECTOR_0  ((uint32_t)0U)  /*!< Sector Number 0   */
#define FLASH_SECTOR_1  ((uint32_t)1U)  /*!< Sector Number 1   */
#define FLASH_SECTOR_2  ((uint32_t)2U)  /*!< Sector Number 2   */
#define FLASH_SECTOR_3  ((uint32_t)3U)  /*!< Sector Number 3   */
#define FLASH_SECTOR_4  ((uint32_t)4U)  /*!< Sector Number 4   */
#define FLASH_SECTOR_5  ((uint32_t)5U)  /*!< Sector Number 5   */
#define FLASH_SECTOR_6  ((uint32_t)6U)  /*!< Sector Number 6   */
#define FLASH_SECTOR_7  ((uint32_t)7U)  /*!< Sector Number 7   */
#define FLASH_SECTOR_8  ((uint32_t)8U)  /*!< Sector Number 8   */
#define FLASH_SECTOR_9  ((uint32_t)9U)  /*!< Sector Number 9   */
#define FLASH_SECTOR_10 ((uint32_t)10U) /*!< Sector Number 10  */
#define FLASH_SECTOR_11 ((uint32_t)11U) /*!< Sector Number 11  */
#define FLASH_SECTOR_12 ((uint32_t)12U) /*!< Sector Number 12  */
#define FLASH_SECTOR_13 ((uint32_t)13U) /*!< Sector Number 13  */
#define FLASH_SECTOR_14 ((uint32_t)14U) /*!< Sector Number 14  */
#define FLASH_SECTOR_15 ((uint32_t)15U) /*!< Sector Number 15  */
#define FLASH_SECTOR_16 ((uint32_t)16U) /*!< Sector Number 16  */
#define FLASH_SECTOR_17 ((uint32_t)17U) /*!< Sector Number 17  */
#define FLASH_SECTOR_18 ((uint32_t)18U) /*!< Sector Number 18  */
#define FLASH_SECTOR_19 ((uint32_t)19U) /*!< Sector Number 19  */
#define FLASH_SECTOR_20 ((uint32_t)20U) /*!< Sector Number 20  */
#define FLASH_SECTOR_21 ((uint32_t)21U) /*!< Sector Number 21  */
#define FLASH_SECTOR_22 ((uint32_t)22U) /*!< Sector Number 22  */
#define FLASH_SECTOR_23 ((uint32_t)23U) /*!< Sector Number 23  */

#define ADDR_FLASH_SECTOR_0  ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1  ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2  ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3  ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4  ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5  ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6  ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7  ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */
#define ADDR_FLASH_SECTOR_8  ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbyte */
#define ADDR_FLASH_SECTOR_9  ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbyte */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbyte */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */
#define ADDR_FLASH_SECTOR_12 ((uint32_t)0x08100000) /* Base @ of Sector 12, 16 Kbyte */
#define ADDR_FLASH_SECTOR_13 ((uint32_t)0x08104000) /* Base @ of Sector 13, 16 Kbyte */
#define ADDR_FLASH_SECTOR_14 ((uint32_t)0x08108000) /* Base @ of Sector 14, 16 Kbyte */
#define ADDR_FLASH_SECTOR_15 ((uint32_t)0x0810C000) /* Base @ of Sector 15, 16 Kbyte */
#define ADDR_FLASH_SECTOR_16 ((uint32_t)0x08110000) /* Base @ of Sector 16, 64 Kbyte */
#define ADDR_FLASH_SECTOR_17 ((uint32_t)0x08120000) /* Base @ of Sector 17, 128 Kbyte */
#define ADDR_FLASH_SECTOR_18 ((uint32_t)0x08140000) /* Base @ of Sector 18, 128 Kbyte */
#define ADDR_FLASH_SECTOR_19 ((uint32_t)0x08160000) /* Base @ of Sector 19, 128 Kbyte */
#define ADDR_FLASH_SECTOR_20 ((uint32_t)0x08180000) /* Base @ of Sector 20, 128 Kbyte */
#define ADDR_FLASH_SECTOR_21 ((uint32_t)0x081A0000) /* Base @ of Sector 21, 128 Kbyte */
#define ADDR_FLASH_SECTOR_22 ((uint32_t)0x081C0000) /* Base @ of Sector 22, 128 Kbyte */
#define ADDR_FLASH_SECTOR_23 ((uint32_t)0x081E0000) /* Base @ of Sector 23, 128 Kbyte */

#endif /* STM32F427xx || STM32F437xx || STM32F429xx|| STM32F439xx || STM32F469xx || STM32F479xx */
/*-----------------------------------------------------------------------------------------------------*/

/*--------------------------------------- STM32F40xxx/STM32F41xxx -------------------------------------*/
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||                    \
    defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define FLASH_SECTOR_0  ((uint32_t)0U)  /*!< Sector Number 0   */
#define FLASH_SECTOR_1  ((uint32_t)1U)  /*!< Sector Number 1   */
#define FLASH_SECTOR_2  ((uint32_t)2U)  /*!< Sector Number 2   */
#define FLASH_SECTOR_3  ((uint32_t)3U)  /*!< Sector Number 3   */
#define FLASH_SECTOR_4  ((uint32_t)4U)  /*!< Sector Number 4   */
#define FLASH_SECTOR_5  ((uint32_t)5U)  /*!< Sector Number 5   */
#define FLASH_SECTOR_6  ((uint32_t)6U)  /*!< Sector Number 6   */
#define FLASH_SECTOR_7  ((uint32_t)7U)  /*!< Sector Number 7   */
#define FLASH_SECTOR_8  ((uint32_t)8U)  /*!< Sector Number 8   */
#define FLASH_SECTOR_9  ((uint32_t)9U)  /*!< Sector Number 9   */
#define FLASH_SECTOR_10 ((uint32_t)10U) /*!< Sector Number 10  */
#define FLASH_SECTOR_11 ((uint32_t)11U) /*!< Sector Number 11  */

#define ADDR_FLASH_SECTOR_0  ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1  ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2  ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3  ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4  ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5  ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6  ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7  ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8  ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9  ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx || STM32F412Zx || STM32F412Vx || STM32F412Rx ||     \
          STM32F412Cx */
/*-----------------------------------------------------------------------------------------------------*/

/*--------------------------------------------- STM32F401xC -------------------------------------------*/
#if defined(STM32F401xC)

#define FLASH_SECTOR_0 ((uint32_t)0U) /*!< Sector Number 0   */
#define FLASH_SECTOR_1 ((uint32_t)1U) /*!< Sector Number 1   */
#define FLASH_SECTOR_2 ((uint32_t)2U) /*!< Sector Number 2   */
#define FLASH_SECTOR_3 ((uint32_t)3U) /*!< Sector Number 3   */
#define FLASH_SECTOR_4 ((uint32_t)4U) /*!< Sector Number 4   */
#define FLASH_SECTOR_5 ((uint32_t)5U) /*!< Sector Number 5   */

#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */

#endif /* STM32F401xC */
/*-----------------------------------------------------------------------------------------------------*/

/*--------------------------------------------- STM32F410xx -------------------------------------------*/
#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define FLASH_SECTOR_0 ((uint32_t)0U) /*!< Sector Number 0   */
#define FLASH_SECTOR_1 ((uint32_t)1U) /*!< Sector Number 1   */
#define FLASH_SECTOR_2 ((uint32_t)2U) /*!< Sector Number 2   */
#define FLASH_SECTOR_3 ((uint32_t)3U) /*!< Sector Number 3   */
#define FLASH_SECTOR_4 ((uint32_t)4U) /*!< Sector Number 4   */
#endif                                /* STM32F410Tx || STM32F410Cx || STM32F410Rx */
/*-----------------------------------------------------------------------------------------------------*/

/*---------------------------------- STM32F401xE/STM32F411xE/STM32F446xx ------------------------------*/
#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)

#define FLASH_SECTOR_0 ((uint32_t)0U) /*!< Sector Number 0   */
#define FLASH_SECTOR_1 ((uint32_t)1U) /*!< Sector Number 1   */
#define FLASH_SECTOR_2 ((uint32_t)2U) /*!< Sector Number 2   */
#define FLASH_SECTOR_3 ((uint32_t)3U) /*!< Sector Number 3   */
#define FLASH_SECTOR_4 ((uint32_t)4U) /*!< Sector Number 4   */
#define FLASH_SECTOR_5 ((uint32_t)5U) /*!< Sector Number 5   */
#define FLASH_SECTOR_6 ((uint32_t)6U) /*!< Sector Number 6   */
#define FLASH_SECTOR_7 ((uint32_t)7U) /*!< Sector Number 7   */

#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */

#endif /* STM32F401xE || STM32F411xE || STM32F446xx */
/*-----------------------------------------------------------------------------------------------------*/

/*---------------------------------- STM32F7xx ------------------------------*/
#if defined(STM32F756xx) || defined(STM32F746xx) || defined(STM32F745xx) || defined(STM32F765xx) ||                    \
    defined(STM32F767xx) || defined(STM32F769xx) || defined(STM32F777xx) || defined(STM32F779xx) ||                    \
    defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F732xx) || defined(STM32F733xx)

#define FLASH_SECTOR_0 ((uint32_t)0U) /*!< Sector Number 0   */
#define FLASH_SECTOR_1 ((uint32_t)1U) /*!< Sector Number 1   */
#define FLASH_SECTOR_2 ((uint32_t)2U) /*!< Sector Number 2   */
#define FLASH_SECTOR_3 ((uint32_t)3U) /*!< Sector Number 3   */
#define FLASH_SECTOR_4 ((uint32_t)4U) /*!< Sector Number 4   */
#define FLASH_SECTOR_5 ((uint32_t)5U) /*!< Sector Number 5   */
#define FLASH_SECTOR_6 ((uint32_t)6U) /*!< Sector Number 6   */
#define FLASH_SECTOR_7 ((uint32_t)7U) /*!< Sector Number 7   */

#if (FLASH_SECTOR_TOTAL == 24)
#define FLASH_SECTOR_8  ((uint32_t)8U)  /*!< Sector Number 8   */
#define FLASH_SECTOR_9  ((uint32_t)9U)  /*!< Sector Number 9   */
#define FLASH_SECTOR_10 ((uint32_t)10U) /*!< Sector Number 10  */
#define FLASH_SECTOR_11 ((uint32_t)11U) /*!< Sector Number 11  */
#define FLASH_SECTOR_12 ((uint32_t)12U) /*!< Sector Number 12  */
#define FLASH_SECTOR_13 ((uint32_t)13U) /*!< Sector Number 13  */
#define FLASH_SECTOR_14 ((uint32_t)14U) /*!< Sector Number 14  */
#define FLASH_SECTOR_15 ((uint32_t)15U) /*!< Sector Number 15  */
#define FLASH_SECTOR_16 ((uint32_t)16U) /*!< Sector Number 16  */
#define FLASH_SECTOR_17 ((uint32_t)17U) /*!< Sector Number 17  */
#define FLASH_SECTOR_18 ((uint32_t)18U) /*!< Sector Number 18  */
#define FLASH_SECTOR_19 ((uint32_t)19U) /*!< Sector Number 19  */
#define FLASH_SECTOR_20 ((uint32_t)20U) /*!< Sector Number 20  */
#define FLASH_SECTOR_21 ((uint32_t)21U) /*!< Sector Number 21  */
#define FLASH_SECTOR_22 ((uint32_t)22U) /*!< Sector Number 22  */
#define FLASH_SECTOR_23 ((uint32_t)23U) /*!< Sector Number 23  */
#else
// need to define here a 'dummy'' SECTOR_11, for F7 series this required when FLASH_SECTOR_TOTAL is 8
#define FLASH_SECTOR_11 ((uint32_t)11U) /*!< Sector Number 11  */
#endif                                  /* FLASH_SECTOR_TOTAL == 24 */

// the following is assuming DUAL BANK is not used
#define ADDR_FLASH_SECTOR_0  ((uint32_t)0x08000000) /* Base address of Sector 0, 32 Kbytes */
#define ADDR_FLASH_SECTOR_1  ((uint32_t)0x08008000) /* Base address of Sector 1, 32 Kbytes */
#define ADDR_FLASH_SECTOR_2  ((uint32_t)0x08010000) /* Base address of Sector 2, 32 Kbytes */
#define ADDR_FLASH_SECTOR_3  ((uint32_t)0x08018000) /* Base address of Sector 3, 32 Kbytes */
#define ADDR_FLASH_SECTOR_4  ((uint32_t)0x08020000) /* Base address of Sector 4, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5  ((uint32_t)0x08040000) /* Base address of Sector 5, 256 Kbytes */
#define ADDR_FLASH_SECTOR_6  ((uint32_t)0x08080000) /* Base address of Sector 6, 256 Kbytes */
#define ADDR_FLASH_SECTOR_7  ((uint32_t)0x080C0000) /* Base address of Sector 7, 256 Kbytes */
#define ADDR_FLASH_SECTOR_8  ((uint32_t)0x08100000) /* Base address of Sector 8, 256 Kbytes */
#define ADDR_FLASH_SECTOR_9  ((uint32_t)0x08140000) /* Base address of Sector 9, 256 Kbytes */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x08180000) /* Base address of Sector 10, 256 Kbytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x081C0000) /* Base address of Sector 11, 256 Kbytes */

#endif // efined(STM32F756xx) || defined(STM32F746xx) || defined(STM32F745xx) || defined(STM32F767xx) || .... etc

/////////////////
// sector address
/////////////////

#if defined(STM32F746xx) || defined(STM32F745xx)

#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000) /* Base address of Sector 0, 32 Kbytes */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08008000) /* Base address of Sector 1, 32 Kbytes */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08010000) /* Base address of Sector 2, 32 Kbytes */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x08018000) /* Base address of Sector 3, 32 Kbytes */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08020000) /* Base address of Sector 4, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08040000) /* Base address of Sector 5, 256 Kbytes */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08080000) /* Base address of Sector 6, 256 Kbytes */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x080C0000) /* Base address of Sector 7, 256 Kbytes */

#elif defined(STM32F767xx)

// this is assuming that we DO NOT work with dual bank
#define ADDR_FLASH_SECTOR_0  ((uint32_t)0x08000000) /* Base address of Sector 0, 32 Kbytes */
#define ADDR_FLASH_SECTOR_1  ((uint32_t)0x08008000) /* Base address of Sector 1, 32 Kbytes */
#define ADDR_FLASH_SECTOR_2  ((uint32_t)0x08010000) /* Base address of Sector 2, 32 Kbytes */
#define ADDR_FLASH_SECTOR_3  ((uint32_t)0x08018000) /* Base address of Sector 3, 32 Kbytes */
#define ADDR_FLASH_SECTOR_4  ((uint32_t)0x08020000) /* Base address of Sector 4, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5  ((uint32_t)0x08040000) /* Base address of Sector 5, 256 Kbytes */
#define ADDR_FLASH_SECTOR_6  ((uint32_t)0x08080000) /* Base address of Sector 6, 256 Kbytes */
#define ADDR_FLASH_SECTOR_7  ((uint32_t)0x080C0000) /* Base address of Sector 7, 256 Kbytes */
#define ADDR_FLASH_SECTOR_8  ((uint32_t)0x08100000) /* Base address of Sector 8, 256 Kbytes */
#define ADDR_FLASH_SECTOR_9  ((uint32_t)0x08140000) /* Base address of Sector 9, 256 Kbytes */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x08180000) /* Base address of Sector 10, 256 Kbytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x081C0000) /* Base address of Sector 11, 256 Kbytes */

#elif defined(STM32F769xx)

// this is assuming that we DO NOT work with dual bank
#define ADDR_FLASH_SECTOR_0  ((uint32_t)0x08000000) /* Base @ of Sector 0, 32 Kbyte */
#define ADDR_FLASH_SECTOR_1  ((uint32_t)0x08008000) /* Base @ of Sector 1, 32 Kbyte */
#define ADDR_FLASH_SECTOR_2  ((uint32_t)0x08010000) /* Base @ of Sector 2, 32 Kbyte */
#define ADDR_FLASH_SECTOR_3  ((uint32_t)0x08018000) /* Base @ of Sector 3, 32 Kbyte */
#define ADDR_FLASH_SECTOR_4  ((uint32_t)0x08020000) /* Base @ of Sector 4, 128 Kbyte */
#define ADDR_FLASH_SECTOR_5  ((uint32_t)0x08040000) /* Base @ of Sector 5, 256 Kbyte */
#define ADDR_FLASH_SECTOR_6  ((uint32_t)0x08080000) /* Base @ of Sector 6, 256 Kbyte */
#define ADDR_FLASH_SECTOR_7  ((uint32_t)0x080C0000) /* Base @ of Sector 7, 256 Kbyte */
#define ADDR_FLASH_SECTOR_8  ((uint32_t)0x08100000) /* Base @ of Sector 8, 256 Kbyte */
#define ADDR_FLASH_SECTOR_9  ((uint32_t)0x08140000) /* Base @ of Sector 9, 256 Kbyte */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x08180000) /* Base @ of Sector 10, 256 Kbyte */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x081C0000) /* Base @ of Sector 11, 256 Kbyte */

#elif defined(STM32F722xx)

#define ADDR_FLASH_SECTOR_0  ((uint32_t)0x08000000) /* Base address of Sector 0, 32 Kbytes */
#define ADDR_FLASH_SECTOR_1  ((uint32_t)0x08008000) /* Base address of Sector 1, 32 Kbytes */
#define ADDR_FLASH_SECTOR_2  ((uint32_t)0x08010000) /* Base address of Sector 2, 32 Kbytes */
#define ADDR_FLASH_SECTOR_3  ((uint32_t)0x08018000) /* Base address of Sector 3, 32 Kbytes */
#define ADDR_FLASH_SECTOR_4  ((uint32_t)0x08020000) /* Base address of Sector 4, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5  ((uint32_t)0x08040000) /* Base address of Sector 5, 256 Kbytes */
#define ADDR_FLASH_SECTOR_6  ((uint32_t)0x08080000) /* Base address of Sector 6, 256 Kbytes */
#define ADDR_FLASH_SECTOR_7  ((uint32_t)0x080C0000) /* Base address of Sector 7, 256 Kbytes */
#define ADDR_FLASH_SECTOR_8  ((uint32_t)0x08100000) /* Base address of Sector 8, 256 Kbytes */
#define ADDR_FLASH_SECTOR_9  ((uint32_t)0x08140000) /* Base address of Sector 9, 256 Kbytes */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x08180000) /* Base address of Sector 10, 256 Kbytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x081C0000) /* Base address of Sector 11, 256 Kbytes */

#elif defined(STM32F723xx)

#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */

#endif

// sanity check for definition of flash sector, sector0 exists on any target, so we are good checking for its definition
#ifndef ADDR_FLASH_SECTOR_0
#error>>THE SECTORS ADDRESSES FOR THE TARGET BOARD HAVE NOT BEEN DEFINED, PLEASE ADD THOSE ABOVE AT THE APPROPRIATE LOCATION AND SUBMIT A PR<<
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    void flash_lld_init();
    void flash_lld_readBytes(uint32_t startAddress, uint32_t length, uint8_t *buffer);
    int flash_lld_write(uint32_t startAddress, uint32_t length, const uint8_t *buffer);
    int flash_lld_isErased(uint32_t startAddress, uint32_t length);
    int flash_lld_erase(uint32_t address);
    uint8_t flash_lld_getSector(uint32_t address);

#ifdef __cplusplus
}
#endif

#endif // FLASH_LLD_H