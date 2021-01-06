/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                          */ 
/*****************************************************************************************************************/

 #include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"


void FPEC_voidFlashInit()
{
		FPEC -> KEYR = KEY1;
		FPEC -> KEYR = KEY2;
		
}

u16 FPEC_u16ReadHalfWord(u8 cpyPage , u8 offset)
{
	volatile u32 local_address = (u32)(cpyPage * 1024) + 0x08000000 + offset;
	volatile u16 val = *((volatile u16 *) local_address);
	return val;
}


void FPEC_voidFlashWrite(u16 Copy_u16Data ,u8 cpyPage , u8 Copy_u8DataByteLength , u8 offset)

{
	u8 Local_u8HWordLength ;
	u8 i ;
	volatile u32 local_u32address =(u32) (cpyPage * 1024) + 0x08000000 + offset;

	// calculate data length  as  half word 
	Local_u8HWordLength= Copy_u8DataByteLength / 2  ;

		// Write Flash Programming 
		SET_BIT(FPEC->CR,PG);

		// Half word operation 
		// check if address contains value 0Xffff or not 
       //if(GET_BIT(FPEC->SR,2)==0){
		*((volatile u16*)local_u32address) = Copy_u16Data;
			// wait busy flag and End of operation
		while (GET_BIT(FPEC->SR,BSY ) == 1);
		// reset EOF BIT by writing 1 
		SET_BIT(FPEC->SR,EOP);
		//clear busy flag 
		CLR_BIT(FPEC->CR,BSY);
	
	
}


void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BSY) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,LOCK) == 1)
	{
		FPEC -> KEYR = KEY1;
		FPEC -> KEYR = KEY2;
	}
	
	/* Page Erase Operation */
	SET_BIT(FPEC->CR,PER);

	/* Write Page address */
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(FPEC->CR,STRT);

	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BSY) == 1);

	/* EOP */
	SET_BIT(FPEC->SR,EOP);
	CLR_BIT(FPEC->CR,PER);
}

void FPEC_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=FIRST_PAGE_NUMBER;i<LAST_PAGE_NUMBER;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}


void FPEC_voidFlashLock(void)
{  
// set lock bit 
	SET_BIT(FPEC->CR,LOCK);
}

void FPEC_voidFlashMassErase()
{
	// check for lock 
	
	if(GET_BIT(FPEC->CR,LOCK)==1){
		FPEC -> KEYR = KEY1;
		FPEC -> KEYR = KEY2;
		
	}
     // set mass earse bit
		SET_BIT (FPEC-> CR , MER);
		// set start bit
        SET_BIT (FPEC-> CR , STRT);
		
	//while (GET_BIT(FPEC->SR,0 ) == 1&& GET_BIT(FPEC->SR,5)==1);
	while (GET_BIT(FPEC->SR,BSY ) == 1);
	// reset EOF BIT by writing 1 
	    SET_BIT(FPEC->SR,EOP);
	//clear busy flag 
		CLR_BIT(FPEC->CR,BSY);
}
