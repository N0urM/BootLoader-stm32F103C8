/*****************************************************************************************************************/
/* Author  : Eman  / Nourhan                                                                                        */
/* version : v02                                                                                                 */
/* Date    : 12\1\2021                                                                                          */ 
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

u16 FPEC_u16ReadHalfWord(u8 cpyPage , u16 offset)
{
	volatile u32 local_address = (u32)(cpyPage * 1024) + 0x08000000 + offset;
	volatile u16 val = *((volatile u16 *) local_address);
	return val;
}

u32  FPEC_u32ReadWord(u8 copyPage , u16 offset1)
{
	volatile u32 val=0;
	volatile u16 tmp_val ;

	// Use TMP value to manipulate Little indian format.
	tmp_val=FPEC_u16ReadHalfWord( copyPage ,  offset1);
	tmp_val = (u16) ((tmp_val&0xFF)<<8) | (u16) ((tmp_val>>8) & 0xFF);

	val = ((u16)tmp_val & 0xFFFFFFFF);
	val<<=16;
	tmp_val = FPEC_u16ReadHalfWord( copyPage ,  offset1+2);
	tmp_val = (u16) ((tmp_val&0xFF)<<8) | (u16) ((tmp_val>>8) & 0xFF);
	val |= (tmp_val & 0xFFFF);
	return val ;
}


void FPEC_voidFlashWrite(u8 * Copy_u8Data , u8 cpyPage , u16 Copy_u8DataArrayLength , u16 offset)
{
	u16 i ;
	u16 local_u16Data;
	volatile u32 local_u32address =(u32) (cpyPage * 1024) + 0x08000000 + offset;
	
	while (GET_BIT(FPEC->SR,BSY) == 1);
	CLR_BIT(FPEC->CR,PER);
	
	// Write Flash Programming 
	SET_BIT(FPEC->CR,PG);	
	
	for (i=0 ; i<Copy_u8DataArrayLength-1 ; i+=2)
	{	
		// Half word operation 
		local_u16Data = (u16)(( (u16)Copy_u8Data[i] ) + ( (u16)Copy_u8Data[i+1]<<8 )); 
		*((volatile u16*)local_u32address) = local_u16Data;
		local_u32address +=2;
		// wait busy flag and End of operation
		while (GET_BIT(FPEC->SR,BSY ) == 1);
		// reset EOP BIT by writing 1 
		SET_BIT(FPEC->SR, EOP);
	} 
	// Last byte
	if (i<Copy_u8DataArrayLength)
	{
		local_u16Data = (u16)(( (u16)Copy_u8Data[i] ) + ( (u16) 0xFF<<8 )); 
		*((volatile u16*)local_u32address) = local_u16Data;
		local_u32address +=2;
		// wait busy flag and End of operation
		while (GET_BIT(FPEC->SR,BSY ) == 1);
		// reset EOP BIT by writing 1 
		SET_BIT(FPEC->SR, EOP);
	
	}
	
	// Clear progrmming 
	CLR_BIT(FPEC->CR, PG);
}


void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
		/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BSY) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,LOCK) == 1) 
	{
		FPEC->KEYR = KEY1;
		FPEC->KEYR = KEY2;
	}
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,BSY) == 1);

	// SET PER bit
	SET_BIT(FPEC->CR, PER);

	// select Page to erase in AR register
	FPEC->AR = (u32) (Copy_u8PageNumber * 1024) + 0x08000000;

	// Set STRT bit
	SET_BIT(FPEC->CR , STRT);

	// Wait for BSY bit
	while ( GET_BIT (FPEC->SR , BSY) == 1);
	/* EOP */
	SET_BIT(FPEC->SR, EOP);
	CLR_BIT(FPEC->CR, PER);
	
}

void FPEC_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=FIRST_PAGE_NUMBER;i<LAST_PAGE_NUMBER;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}

