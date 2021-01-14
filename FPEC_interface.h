/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                    */ 
/*****************************************************************************************************************/
#ifndef _FPEC_INTERFACE_H
#define _FPEC_INTERFACE_H

void FPEC_voidFlashInit(void);
u16 FPEC_u16ReadHalfWord(u8 cpyPage , u8 offset);
void FPEC_voidFlashWrite(u8 * Copy_u8Data ,u8 cpyPage , u8 Copy_u8DataArrayLength , u16 offset);
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);
void FPEC_voidEraseAppArea(void);
void FPEC_voidFlashLock();

u32  FPEC_u32ReadWord(u8 copyPage , u8 offset1);

#endif
