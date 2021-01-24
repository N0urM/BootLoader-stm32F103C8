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
#define APP_STARTING_ADDRESS		0x08001400

#define IMAGE_VERIFIED      1
#define	IMAGE_NOT_VERIFIED  0


/********************** Public functions ***********************/

/**
  * @name		BL_voidProcessPayLoadMain
	*	@brief  main function for Condition check, image download, image verification and jump.
  * @param  none
  * @retval none
  */
void BL_voidProcessPayLoadMain(void);


/**
  * @name		BL_voidWriteConditionPage
	*	@brief  Set the brancing condition to 'A':app or 'B':bootloader along with 
						other page info. 
	* @param  cpyBC: Branching condition values: 'A' or 'B'
						cpy_DataLen: Store image length
						cpy_CRC: Store Image CRC32-MPEG value
  * @retval none
  */
void BL_voidWriteConditionPage(u16 cpyBC , u16 cpy_DataLen , u32 cpy_CRC);


/**
  * @name		BL_u8CheckBranchingCondition
	*	@brief  Get the current branchig condition value
  * @param  none
  * @retval Branching condiiton value
  */
u8 BL_u8CheckBranchingCondition(void);

/**
  * @name		BL_u8ValidateCRCFromFlash
	*	@brief  Calculate CRC value for the image and compare iwth stored value
  * @param  cpyDataLength: Image length
						cpyCRCValue: Value sttored currently in flash or sent by the OTA side
	* @retval boolean: IMAGE_NOT_VERIFIED or IMAGE_VERIFIED
  */
u8 BL_u8ValidateCRCFromFlash(u16 cpyDataLength , u32 cpyCRCValue);


/**
  * @name		BL_voidSoftReset
	*	@brief  create a soft reset.
  * @param  none
  * @retval none
  */
void BL_voidSoftReset(void);

/********** Private functions **************/

u16 BL_u16ReciveDataLength(void);
u32 BL_u32ReciveCRC(void);
void JumpToApp(void);


#endif