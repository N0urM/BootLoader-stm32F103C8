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
#include "IWDG_interface.h"

#include "BootLoaderApplication.h"


void JumpToApp(void)
{
	#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = APP_STARTING_ADDRESS;

	addr_to_call = *(Function_t*)(APP_STARTING_ADDRESS + 4);
	addr_to_call();
}

void BL_voidProcessPayLoadMain(void)
{

	volatile u16 local_u16datalen=0;
	volatile u16 local_u16RecievedData =0;
	volatile u16 CRCValLOW = 0;
	volatile u16 CRCValHigh = 0;
	volatile u32 local_u32CRCValue=0;
	volatile u8 local_u8DataStream[1024]={0};
	
	//check branching condition 
	if (BL_u8CheckBranchingCondition() == 'A')	// App exists and no update available
	{
		// Read CRC and dataLen from Flash
		local_u16datalen = FPEC_u16ReadHalfWord(CONDITION_PAGE , DATA_LEN_OFFSET);
		CRCValLOW  = FPEC_u16ReadHalfWord(CONDITION_PAGE , CRC_OFFSET);
    	CRCValHigh = FPEC_u16ReadHalfWord(CONDITION_PAGE , CRC_OFFSET+0x02); 	
		local_u32CRCValue = CRCValLOW + (u32)(CRCValHigh<<16);
		
		// Validate CRC Value of data
		if (BL_u8ValidateCRCFromFlash(local_u16datalen , local_u32CRCValue))	
		{
			JumpToApp();														// If validation sucess, jump to app.
		}
		else 
		{
			// Change Branch condition 
			BL_voidWriteConditionPage('B' , local_u16datalen , local_u32CRCValue);

		}
	}
	else 																				// Add doesn't exist or update available
	{

		// Erase App Area
		FPEC_voidEraseAppArea();
	
		// Recive new Data Length
		local_u16datalen = BL_u16ReciveDataLength();
		
		// Recive new data CRC Value 
		local_u32CRCValue = BL_u32ReciveCRC();
		
		// Recieve a chunk of data, write, and repeat till end.
		while(local_u16datalen - local_u16RecievedData > 1023)
		{
				BL_voidRecievePageOfData(local_u8DataStream , 1024);
				FPEC_voidFlashWrite(local_u8DataStream , APP_PAGE , 1024 , local_u16RecievedData );
				local_u16RecievedData +=1024;
		}
		
		// Recieve last chunck 
		BL_voidRecievePageOfData(local_u8DataStream , (local_u16datalen - local_u16RecievedData) );
		FPEC_voidFlashWrite(local_u8DataStream , APP_PAGE , (local_u16datalen - local_u16RecievedData)  , local_u16RecievedData );

		// Validate CRC 
		if(BL_u8ValidateCRCFromFlash(local_u16datalen , local_u32CRCValue))
		{	
				// Change Branch condition 
				BL_voidWriteConditionPage('A' , local_u16datalen , local_u32CRCValue);
		}
		else 
		{
				// Change Branch condition 
				BL_voidWriteConditionPage('B' , local_u16datalen , local_u32CRCValue);
		}
	
	}// END IF

	BL_voidSoftReset();							// Soft reset.

}// END FUNCTION

u8 BL_u8CheckBranchingCondition(void)
{
    u16 BC_memo;
    u8 BC_return;  
    BC_memo = FPEC_u16ReadHalfWord(CONDITION_PAGE , 0);
    switch (BC_memo)
    {
    case 0x1111:
      BC_return = 'A';
      break;
    case 0x2222:
      BC_return = 'B';
      break;
    default: 
      /* Error Shouldn't be here */ 
      BC_return = 'F';  // MEMO NOT WRITTEN 
      break;
    }
    return BC_return;
}

void BL_voidWriteConditionPage(u16 cpyBC , u16 cpy_DataLen , u32 cpy_CRC)
{
    // 'A' : App
    // 'B' : BootLoader

	volatile u8 Data[2];
	volatile u16 local_CRCLOW  = (u16) (cpy_CRC & 0xFFFF);
	volatile u16 local_CRCHigh = (u16) ((cpy_CRC>>16) & 0xFFFF);		
	
	FPEC_voidFlashPageErase(CONDITION_PAGE);

    switch (cpyBC)
    {
    case 'A':
				Data[0] = 0x11;
				Data[1] = 0x11;
		
        break;
    case 'B':
				Data[0] = 0x22;
				Data[1] = 0x22;
        break;
    default:
				Data[0] = 0xFF;
				Data[1] = 0xFF;
        break;
    }
	FPEC_voidFlashWrite(Data       	   , CONDITION_PAGE , 2 , BC_OFFSET );
    FPEC_voidFlashWrite(&cpy_DataLen   , CONDITION_PAGE , 2 , DATA_LEN_OFFSET );
    FPEC_voidFlashWrite(&local_CRCLOW  , CONDITION_PAGE , 2 , CRC_OFFSET+0x02 );
    FPEC_voidFlashWrite(&local_CRCHigh , CONDITION_PAGE , 2 , CRC_OFFSET);
}

void BL_voidSoftReset(void)
{
  IWDG_voidReset();
}
/***
 * TO DO
 ***/

u8 BL_u8ValidateCRCFromFlash(u16 cpyDataLength , u32 cpyCRCValue)
{
	u32 localu32Data ;
   u16 i;
	u32 localcrc ;
for(i=0;i<cpyDataLength;i+=4 )
{
	localu32Data=FPEC_u32ReadWord(APP_PAGE,i);
	CRC_u32Claculate2(localu32Data);

}

localcrc= CRC_u32GetCrc();
if (cpyCRCValue==localcrc )
{
	return IMAGE_VERIFIED ;
}
else
{
	return IMAGE_NOT_VERIFIED ;
}

}


/********** Private functions **************/

u16 BL_u16ReciveDataLength(void)
{
	u8 dataRecieved[2] = {0};	
	u16 data_ret;
	UART1_voidRecieveSync( 2 , dataRecieved);
	data_ret = (u16)(dataRecieved[0]<<8) + dataRecieved[1];
	return data_ret;

}
u32 BL_u32ReciveCRC(void)
{
	u8 dataRecieved[4] = {0};
	u32 data_ret;
	UART1_voidRecieveSync( 4 , dataRecieved);
	data_ret = (u32)(dataRecieved[0]<<24) + (u32)(dataRecieved[1]<<16) + (u32)(dataRecieved[2]<<8) + (dataRecieved[3]);
	return data_ret;
}

void BL_voidRecievePageOfData(u8 * cpyDataStream , u8 cpyDataLength)
{
		UART1_voidRecieveSync(cpyDataLength  , cpyDataStream);
}  
