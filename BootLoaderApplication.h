/*******************************************************************/
/* Author  : Nourhan Mansour                                       */
/* version : v01                                                   */
/* Date    : 31\12\2020                                            */ 
/*******************************************************************/
#ifndef  BL_APP_H
#define  BL_APP_H

#define APP_PAGE        		5 
#define BL_PAGE         		0
#define CONDITION_PAGE  		63

#define BC_OFFSET           0x00
#define DATA_LEN_OFFSET     0x02
#define CRC_OFFSET          0x04


/********************** Public functions ***********************/

/*****************************************************************
    Function Name: BL_voidProcessPayLoadMain
    Description  : Main function. Recieve Data Length, Recieve Data, 
                   Write on Flash, Acumilate CRC  
    Parameters   : none
    Return value : none
******************************************************************/
void BL_voidProcessPayLoadMain(void);

u8 BL_u8CheckBranchingCondition(void);
void BL_voidWriteBranchingCondition(u16 cpyBC);
void BL_voidWriteCRC(u32 cpyCRC);
void BL_voidValidateCRCFromFlash(u16 cpyDataLength , u32 cpyCRCValue); 
void BL_voidSoftReset(void);

/********** Private functions **************/

u16 BL_u16ReciveDataLength(void);
void BL_voidRecievePageOfData(u8 * cpyDataStream , u8 cpyDataLength);
u32 BL_u32ReciveCRC(void);


#endif