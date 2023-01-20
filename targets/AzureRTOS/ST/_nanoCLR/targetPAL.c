//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <stm32f7xx_hal.h>

GPIO_TypeDef *gpioPort[] = {
    GPIOA,
    GPIOB
#ifdef GPIOC
    ,
    GPIOC
#endif
#ifdef GPIOD
    ,
    GPIOD
#endif
#ifdef GPIOE
    ,
    GPIOE
#endif
#ifdef GPIOF
    ,
    GPIOF
#endif
#ifdef GPIOG
    ,
    GPIOG
#endif
#ifdef GPIOH
    ,
    GPIOH
#endif
#ifdef GPIOI
    ,
    GPIOI
#endif
#ifdef GPIOJ
    ,
    GPIOJ
#endif
#ifdef GPIOK
    ,
    GPIOK
#endif
};
