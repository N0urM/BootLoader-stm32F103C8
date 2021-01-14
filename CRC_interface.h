/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                        */ 
/*****************************************************************************************************************/
#ifndef  CRC_INTERFACE_H
#define  CRC_INTERFACE_H


#define CRC_RESET  1




u32 CRC_u32Claculate(u32 Copy_u32Data);
void CRC_voidReset();
void CRC_u32Claculate2(u32 Copy_u32Data);
u32 CRC_u32GetCrc();

#endif