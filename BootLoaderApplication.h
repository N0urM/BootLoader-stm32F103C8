/*******************************************************************/
/* Author  : Nourhan Mansour                                       */
/* version : v01                                                   */
/* Date    : 31\12\2020                                            */ 
/*******************************************************************/
#ifndef  BL_APP_H
#define  BL_APP_H

#define APP_PAGE        				5 
#define BL_PAGE         				0
#define CONDITION_PAGE  				63

#define BC_OFFSET           		0x00
#define DATA_LEN_OFFSET     		0x02
#define CRC_OFFSET          		0x04
#define APP_STARTING_ADDRESS		0x08001000
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;


/********************** Public functions ***********************/

/**
  * @name		BL_voidProcessPayLoadMain
	*	@brief  
  * @param  none
  * @retval none
  */
void BL_voidProcessPayLoadMain(void);

u8 BL_u8CheckBranchingCondition(void);
void BL_voidWriteConditionPage(u16 cpyBC , u16 cpy_DataLen , u32 cpy_CRC);
void BL_voidWriteCRC(u32 cpyCRC);
u8 BL_u8ValidateCRCFromFlash(u16 cpyDataLength , u32 cpyCRCValue); 
void BL_voidSoftReset(void);

/********** Private functions **************/

u16 BL_u16ReciveDataLength(void);
void BL_voidRecievePageOfData(u8 * cpyDataStream , u8 cpyDataLength);
u32 BL_u32ReciveCRC(void);
void JumpToApp(void);


#endif