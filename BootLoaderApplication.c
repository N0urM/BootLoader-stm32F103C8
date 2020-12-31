/*******************************************************************/
/* Author  : Nourhan Mansour - Eman Ashraf                         */
/* version : v01                                                   */
/* Date    : 31\12\2020                                            */ 
/*******************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "CRC_interface.h"
#include "UART_interface.h"

#include "BootLoaderApplication.h"

void BL_voidProcessPayLoadMain(){}

u8 BL_u8CheckBranchingCondition(){
    u16 BC_return ; 
    BC_return = FPEC_u16ReadHalfWord(CONDITION_PAGE , 0);
    return BC_return;
}

void BL_voidWriteBranchingCondition(u16 cpyBC)
{
    // 'A' : App
    // 'B' : BootLoader
    u16 CRCValLOW  = FPEC_u16ReadHalfWord(CONDITION_PAGE , CRC_OFFSET);
    u16 CRCValHigh = FPEC_u16ReadHalfWord(CONDITION_PAGE , CRC_OFFSET+0x02); 
    u16 DataLen = FPEC_u16ReadHalfWord(CONDITION_PAGE , DATA_LEN_OFFSET);

    FPEC_voidFlashPageErase(CONDITION_PAGE);

    switch (cpyBC)
    {
    case 'A':
        FPEC_voidFlashWrite('AA' , CONDITION_PAGE , 2 ,BC_OFFSET );
        break;
    case 'B':
        FPEC_voidFlashWrite('BB' , CONDITION_PAGE , 2 ,BC_OFFSET );
        break;
    default:
        FPEC_voidFlashWrite('EE' , CONDITION_PAGE , 2 ,BC_OFFSET );
        break;
    }
    FPEC_voidFlashWrite(DataLen , CONDITION_PAGE , 2 , DATA_LEN_OFFSET );
    FPEC_voidFlashWrite(CRCValLOW , CONDITION_PAGE , 2 , CRC_OFFSET );
    FPEC_voidFlashWrite(CRCValHigh , CONDITION_PAGE , 2 ,CRC_OFFSET+0x02);
}

void BL_voidValidateCRCFromFlash(u16 cpyDataLength , u32 cpyCRCValue){}
void BL_voidSoftReset(){}


/********** Private functions **************/

u16 BL_u16ReciveDataLength(){}
void BL_voidRecievePageOfData(u8 * cpyDataStream){}  // 1024 bytes 
u32 BL_u32ReciveCRC(){}
