/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                    */ 
/*****************************************************************************************************************/
#ifndef _FPEC_INTERFACE_H
#define _FPEC_INTERFACE_H







void FPEC_voidFlashWrite(u16 *Copy_u16Data ,u32 Copy_u32Address , u8 Copy_u8DataByteLength);
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);
void FPEC_voidEraseAppArea(void);
void FPEC_voidFlashLock();
//void FPEC_voidWriteProtection(u8 Copy_u8FristPageNum);
//u8 FPEC_u8GetWriteProtectionState(Copy_u8PageNum);



#endif
