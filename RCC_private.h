/******************************************************/ 
/* Author: Nourhan Mansour                            */
/* Date  : 8/8/2020                                   */
/* Vesion: 1.1                                        */
/* File  : RCC_private.h                              */
/******************************************************/ 
#ifndef     RCC_PRIVATE_H
#define     RCC_PRIVATE_H

/*************** Registers definitions ****************/
#define  RCC_CR             *((volatile u32 *) 0x40021000)
#define  RCC_CFGR           *((volatile u32 *) 0x40021004)
#define  RCC_CIR            *((volatile u32 *) 0x40021008)
#define  RCC_APB2RSTR       *((volatile u32 *) 0x4002100c)
#define  RCC_APB1RSTR       *((volatile u32 *) 0x40021010)
#define  RCC_AHBENR         *((volatile u32 *) 0x40021014)
#define  RCC_APB2ENR        *((volatile u32 *) 0x40021018)
#define  RCC_APB1ENR        *((volatile u32 *) 0x4002101c)
#define  RCC_BDCR           *((volatile u32 *) 0x40021020)
#define  RCC_CSR            *((volatile u32 *) 0x40021024)
#define  RCC_AHBSTR         *((volatile u32 *) 0x40021028)


// Clock source definitions 
#define HSI         0
#define HSE_RC      1
#define HSE_XTAL    2

// PLL options 
#define RCC_PLL_HSI_DIV2    0
#define RCC_PLL_HSE_DIV2    1
#define RCC_PLL_HSE         2

// MCO Definitons
#define     MCO_NOCLK       0b000
#define     MCO_SYSCLK      0b100   
#define     MCO_HSI         0b101
#define     MCO_HSE         0b110   
#define     MCO_PLL         0b111

/************* bits naming ***************************/


/************* Clock Control Register ****************/
#define RCC_CR_HSION    0
#define RCC_CR_HSIRDY   1

#define RCC_CR_HSITRIM0 3
#define RCC_CR_HSITRIM1 4
#define RCC_CR_HSITRIM2 5
#define RCC_CR_HSITRIM3 6
#define RCC_CR_HSITRIM4 7

#define RCC_CR_HSICAL0  8
#define RCC_CR_HSICAL1  9
#define RCC_CR_HSICAL2  10
#define RCC_CR_HSICAL3  11
#define RCC_CR_HSICAL4  12
#define RCC_CR_HSICAL5  13
#define RCC_CR_HSICAL6  14
#define RCC_CR_HSICAL7  15

#define RCC_CR_HSEON    16
#define RCC_CR_HSERDY   17
#define RCC_CR_HSEPYB   18
#define RCC_CR_CSSON    19

#define RCC_CR_PLLON    24
#define RCC_CR_PLLRDY   25

#define RCC_CR_PLL2ON   26
#define RCC_CR_PLL2RDY  27

#define RCC_CR_PLL3ON   28
#define RCC_CR_PLL3RDY  29


/************* Clock Configuration Register *************/
#define RCC_CFGR_SW0     0
#define RCC_CFGR_SW1     1   

#define RCC_CFGR_SWS0    2
#define RCC_CFGR_SWS1    3

#define RCC_CFGR_HPRE0   4
#define RCC_CFGR_HPRE1   5
#define RCC_CFGR_HPRE2   6
#define RCC_CFGR_HPRE3   7

#define RCC_CFGR_PPRE10  8
#define RCC_CFGR_PPRE11  9
#define RCC_CFGR_PPRE12  10

#define RCC_CFGR_PPRE20  11
#define RCC_CFGR_PPRE21  12
#define RCC_CFGR_PPRE22  13

#define RCC_CFGR_ADCPRE0 14
#define RCC_CFGR_ADCPRE1 15


#define RCC_CFGR_PLLSRC   16
#define RCC_CFGR_PLLXTPRE 17


#define RCC_CFGR_PLLMUL0 18
#define RCC_CFGR_PLLMUL1 19
#define RCC_CFGR_PLLMUL2 20
#define RCC_CFGR_PLLMUL3 21

#define RCC_CFGR_OTGFSPRE 22

#define RCC_CFGR_MCO0   24
#define RCC_CFGR_MCO1   25
#define RCC_CFGR_MCO2   26
#define RCC_CFGR_MCO3   27

#endif  // End Of File
