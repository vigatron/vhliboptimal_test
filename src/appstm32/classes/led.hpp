#pragma once

#include "main.h"


#if defined(TARGET_CMB32F407HDM)

    // LED#0    PC0
    // LED#1    PC1
    // LED#2    PC2
    // LED#3    PC3

    #define     LED_PORT        GPIOC
    #define     LED_PIN         0
    #define     LED_INIT()      __HAL_RCC_GPIOC_CLK_ENABLE()
    #define     LED_ON()        LED_PORT->BSRR = (1<<(LED_PIN+16))
    #define     LED_OFF()       LED_PORT->BSRR = (1<<LED_PIN)

#elif defined(TARGET_STM32F4DISCOVERY)

    // LED#0    PD12    Orange
    // LED#1    PD13    Green
    // LED#2    PD14    Red
    // LED#3    PD15    Blue

    #define     LED_PORT        GPIOD
    #define     LED_PIN         12
    #define     LED_INIT()      __HAL_RCC_GPIOD_CLK_ENABLE()
    #define     LED_ON()        LED_PORT->BSRR = (1<<LED_PIN)
    #define     LED_OFF()       LED_PORT->BSRR = (1<<(LED_PIN+16))

#elif defined(TARGET_WAVESHARECORE7XXI)

    // LED#0    PH4     Green
    #define     LED_PORT        GPIOH
    #define     LED_PIN         4
    #define     LED_INIT()      __HAL_RCC_GPIOH_CLK_ENABLE()
    #define     LED_ON()        LED_PORT->BSRR = (1<<(LED_PIN+16))
    #define     LED_OFF()       LED_PORT->BSRR = (1<<LED_PIN)

#elif defined(TARGET_CMB32H750HDM)

    // CMB32H750HDM         PD3 / PD2 / PCU12
    #define     LED_PORT        GPIOD
    #define     LED_PIN         3
    #define     LED_INIT()      __HAL_RCC_GPIOD_CLK_ENABLE()
    #define     LED_ON()        LED_PORT->BSRR = (1<<(LED_PIN+16))
    #define     LED_OFF()       LED_PORT->BSRR = (1<<LED_PIN)

#else

    #Error "Unknown platform!"

#endif


class VHSYSLED {

    public:

    static void Init() {

        // Барьер памяти (рекомендуется после включения тактирования)
        // __DSB();

        LED_INIT();
        LED_PORT->MODER &= ~(3U << (LED_PIN * 2));
        LED_PORT->MODER |=  (1U << (LED_PIN * 2));
    }

    static void On()    { LED_ON(); }

    static void Off()   { LED_OFF(); }

};
