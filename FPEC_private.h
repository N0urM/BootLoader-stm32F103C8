/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 13/10/2020                                  */
/* Version: 1.0                                         */
/* File   : FPEC_private.h                              */
/********************************************************/ 
#ifndef FPEC_PRIVATE_H
#define FPEC_PRIVATE_H

#define FPEC          	0x40022000

#define FPEC_ACR		*((volatile u32 *) (FPEC + 0x00))
#define FPEC_KEYR		*((volatile u32 *) (FPEC + 0x04))
#define FPEC_OPTKEYR	*((volatile u32 *) (FPEC + 0x08))
#define FPEC_SR			*((volatile u32 *) (FPEC + 0x0C))
#define FPEC_CR			*((volatile u32 *) (FPEC + 0x10))
#define FPEC_AR			*((volatile u32 *) (FPEC + 0x14))
#define FPEC_OBR		*((volatile u32 *) (FPEC + 0x18))
#define FPEC_WRPR		*((volatile u32 *) (FPEC + 0x1C))



#define FLASH_CR_PG         0
#define FLASH_CR_PER        1
#define FLASH_CR_MER        2
#define FLASH_CR_OPTPG      4
#define FLASH_CR_OPTER      5
#define FLASH_CR_STRT       6
#define FLASH_CR_LOCK       7
#define FLASH_CR_OPTWRE     9
#define FLASH_CR_ERRIE      10
#define FLASH_CR_EOPIE      12

#define FLASH_SR_BSY        0
#define FLASH_SR_PGERR      2
#define FLASH_SR_WRPRTERR   4
#define FLASH_SR_EOP        5


#endif // End Of File
