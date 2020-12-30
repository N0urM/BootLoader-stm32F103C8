/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 8/8/2020                                    */
/* Vesion: 1.1                                         */
/* File  : RCC_config.h                                */
/*******************************************************/ 
#ifndef     RCC_CONFIG_H
#define     RCC_CONFIG_H


/*  enable Microcontroller output clock for the selected source 
    Values: 
        MCO_NOCLK
        MCO_SYSCLK
        MCO_HSI
        MCO_HSE
        MCO_PLL
*/
#define MICRO_OUTPUT_CLOCK      MCO_NOCLK            

// Clock Source: HSI - HSE_RC - HSE_XTAL 
#define CLOCK_SRC               HSE_XTAL
// Clock PLL: 1:Enable   -   0:Disable
#define CLOCK_PLL              	0

#if CLOCK_SRC == HSI
    /*
        HSI Trim:
        default value is 16  
        +/-1 step = 40KHZ
        Min value = 0
        Max value = 31 
    */
    #define TRIM_VALUE  16
#elif CLOCK_SRC == HSE_RC ||  CLOCK_SRC == HSE_XTAL 
    /**
     * Choose to 1 enable Security , 0 to diable 
    */
    #define CSSON   0
#endif

#if CLOCK_PLL == 1
    /* Options: 
        RCC_PLL_HSI_DIV2
        RCC_PLL_HSE_DIV2
        RCC_PLL_HSE
    */
    #define PLL_SRC     RCC_PLL_HSE_DIV2
    /* Choose multiplier
        integer value:  2 ~ 16 
        Warning: result clock MUST NOT exceed 72MHZ
    */
    #define PLL_MUL     2
#endif

#endif  // End Of File
