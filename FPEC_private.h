/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                          */ 
/*****************************************************************************************************************/
#ifndef _FPEC_PRIVATE_H
#define _FPEC_PRIVATE_H





// Register defintions

typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 AR;
	volatile u32 RESERVED;
	volatile u32 OBR;
	volatile u32 WRPR;
}FPEC_t;
#define FPEC ((FPEC_t*)0x40022000)

typedef struct
{
	volatile u32 RDP ;
	//volatile u32 USER ;
	volatile u32 Data ;
	//volatile u32 Data1 ;
	volatile u32 WRP0  ;
	//volatile u32 WRP1 ;
	//volatile u32 WRP2 ;
	//volatile u32 WRP3 ;
	
}FPEC_OPBt;

 
#define FPECOPB ((FPEC_OPBt*) 0x1FFFF800)
 // bits of registers

// FLASH_SR 
#define    BSY       0
#define    PGERR     2
#define    WRPRTERR  4
#define    EOP       5

// FLASH_CR
#define    PG        0 
#define    PER       1
#define    MER       2
#define    OPTPG     4
#define    OPTER     5
#define    STRT      6
#define    LOCK      7
#define    OPTWRE    9
#define    ERRIE     10
#define    EOPIE     12

#define KEY1   0x45670123
#define KEY2   0xCDEF89AB

#define RDPRT  0x00A5 

#endif
