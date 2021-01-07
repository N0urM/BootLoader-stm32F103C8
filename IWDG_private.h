/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                          */ 
/*****************************************************************************************************************/
#ifndef  IWDG_PRIVATE_H
#define  IWDG_PRIVATE_H

typedef struct{
	volatile u32 KR ;
	volatile u32 PR;
	volatile u32 RLR;
	volatile u32 SR;
 
}IWDG_t ;
#define IWDG ((IWDG_t*) 0x40003000)

#define   DBGMCU_CR       *((u32*)(0xE0042004))

#endif
