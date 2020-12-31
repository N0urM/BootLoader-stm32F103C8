/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                        */ 
/*****************************************************************************************************************/
#ifndef CRC_PRIVATE_H
#define  CRC_PRIVATE_H




typedef struct{
	volatile u32 CRC_DR ;
	volatile u32 CRC_IDR;
	volatile u32 CRC_CR;
 
}CRC_t ;
#define CRC  ((CRC_t*) 0x40023000)



#endif

