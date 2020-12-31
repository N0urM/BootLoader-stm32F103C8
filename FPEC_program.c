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

void FPEC_voidFlashWrite(u16 *Copy_u16Data ,u32 Copy_u32Address , u8 Copy_u8DataByteLength)

{
	u8 Local_u8HWordLength ;
	u8 i ;
	// calculate data length  as  half word 
	Local_u8HWordLength= Copy_u8DataByteLength / 2  ;
	// check for lock 
	
	if(GET_BIT(FPEC->CR,LOCK)==1){
		FPEC_voidFlashInit();
		
	}
	// write Data in flash
	for (i = 0; i< Local_u8HWordLength; i++)
	{
		// Write Flash Programming 
		SET_BIT(FPEC->CR,PG);

		// Half word operation 
		// check if address contains value 0Xffff or not 
       //if(GET_BIT(FPEC->SR,2)==0){
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2 ;
	   
	}
	// wait busy flag and End of operation
	while (GET_BIT(FPEC->SR,BSY ) == 1);
	// reset EOF BIT by writing 1 
	    SET_BIT(FPEC->SR,EOP);
	//clear busy flag 
		CLR_BIT(FPEC->CR,BSY);
	// lock flash 
	FPEC_voidFlashLock();
}


void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	if(GET_BIT(FPEC->CR,LOCK)==1){
		FPEC_voidFlashInit();
		
	}
	
	// set page earse bit 
	SET_BIT(FPEC->CR,PER);
	
	// Write Page address 
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;
	
	
	// set start bit 
	SET_BIT(FPEC->CR,STRT);
	
	while (GET_BIT(FPEC->SR,BSY ) == 1);
	// reset EOF BIT by writing 1 
	    SET_BIT(FPEC->SR,EOP);
	//clear busy flag 
		CLR_BIT(FPEC->CR,BSY);
	// lock flash 
	FPEC_voidFlashLock();
}

void FPEC_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=FIRST_PAGE_NUMBER;i<LAST_PAGE_NUMBER;i++)
	{
		FPEC_voidFlashPageErase(i);
	}
}

/*void FPEC_voidReadProtection()
{
	
	if(GET_BIT(FPEC->CR,LOCK)==1){
		FPEC_voidFlashInit();
		
	}
// check for option bits write enable flag 	
	if(GET_BIT(FPEC->CR,OPTWRE)==0){
		FPEC -> OPTKEYR  = KEY1;
		FPEC -> OPTKEYR  = KEY2;
		
	}
	// enable programming option bytes 
	
	SET_BIT(FPEC->CR,OPTPG);
	 // write protection key to RDP option byte
	FPECOPB -> RDP= 0x00FF ;
	//wait busy flag
	while (GET_BIT(FPEC->SR,BSY ) == 1);
	// verfiy protection is done
	while (GET_BIT(FPEC->OBR,0 ) == 1);
	 // clear flag
		CLR_BIT(FPEC->CR,BSY);
  // clear option byte enable write  flag 
       CLR_BIT(FPEC->CR,OPTWRE);
}
void FPEC_voidRemoveReadProtection()
{
	
	if(GET_BIT(FPEC->CR,LOCK)==1){
		FPEC_voidFlashInit();
		
	}
// check for option bits write enable flag 	
	if(GET_BIT(FPEC->CR,OPTWRE)==0){
		FPEC -> OPTKEYR  = KEY1;
		FPEC -> OPTKEYR  = KEY2;
		
	}
	// enable programming option bytes 
	
	SET_BIT(FPEC->CR,OPTPG);
	 // write protection key to RDP option byte
	FPECOPB -> RDP= RDPRT ;
	//wait busy flag
	while (GET_BIT(FPEC->SR,BSY ) == 1);
	// verfiy protection is done
	while (GET_BIT(FPEC->OBR,0 ) == 1);
	 // clear flag
		CLR_BIT(FPEC->CR,BSY);
		// clear option byte enable write  flag 
       CLR_BIT(FPEC->CR,OPTWRE);
}
void FPEC_voidWriteProtection(u8 Copy_u8FristPageNum)
{


	if(GET_BIT(FPEC->CR,LOCK)==1){
		FPEC_voidFlashInit();
		
	}
// check for option bits write enable flag 	
	if(GET_BIT(FPEC->CR,OPTWRE)==0){
		FPEC -> OPTKEYR  = KEY1;
		FPEC -> OPTKEYR  = KEY2;
		
	}
	// enable programming option bytes 
	
	SET_BIT(FPEC->CR,OPTPG);
	 if( Copy_u8FristPageNum<=32 ){
	 if(Copy_u8FristPageNum<4)
	 {
		  FPECOPB->WRP0=0x1111111E;
	 }
	 else if(Copy_u8FristPageNum<8)
	 {
		 CLR_BIT( FPECOPB->WRP0,1);
	 }
	 else if(Copy_u8FristPageNum<12)
	 {
		 CLR_BIT( FPECOPB->WRP0,2);
	 }
	  else if(Copy_u8FristPageNum<20)
	 {
		  CLR_BIT( FPECOPB->WRP0,4);
	 }
	  else if(Copy_u8FristPageNum<24)
	 {
		  CLR_BIT( FPECOPB->WRP0,5);
	 }
	  else if(Copy_u8FristPageNum<28)
	 {
		  CLR_BIT( FPECOPB->WRP0,6);
	 }
	  else if(Copy_u8FristPageNum<32)
	 {
		  CLR_BIT( FPECOPB->WRP0,7);
	 }
	 }
}
	/* else {
		 if(Copy_u8FristPageNum<36)
	 {
			 CLR_BIT( FPECOPB->WRP1,0);
	 }
	 else if(Copy_u8FristPageNum<40)
	 {
		 CLR_BIT( FPECOPB->WRP1,1);
	 }
	 else if(Copy_u8FristPageNum<44)
	 {
		 
		 CLR_BIT( FPECOPB->WRP1,2);
	 }
	  else if(Copy_u8FristPageNum<48)
	 {
		 
		  CLR_BIT( FPECOPB->WRP1,3);
	 }
	  else if(Copy_u8FristPageNum<52)
	 {
		
		  CLR_BIT( FPECOPB->WRP1,4);
	 }
	  else if(Copy_u8FristPageNum<56)
	 {
		 
		  CLR_BIT( FPECOPB->WRP1,5);
	 }
	  else if(Copy_u8FristPageNum<60)
	 {
		 
		  CLR_BIT( FPECOPB->WRP1,6);
	 }
		 else if(Copy_u8FristPageNum<64)
	 {
		 
			 CLR_BIT( FPECOPB->WRP1,7);
	 }
	
	 }
	   
	  
	 while (GET_BIT(FPEC->SR,BSY ) == 1);
	// verfiy protection is done
	//while( FPEC_u8GetWriteProtectionState(Copy_u8FristPageNum)==1);
	 // clear flag
	 CLR_BIT(FPEC->CR,BSY);
		// clear option byte enable write  flag 
       CLR_BIT(FPEC->CR,OPTWRE);
}
	 u8 FPEC_u8GetWriteProtectionState(Copy_u8PageNum)
	 {
		 u8 status ;
	 if(Copy_u8PageNum<=32){
	 if(Copy_u8PageNum<4)
	 {
		status= GET_BIT( FPEC->WRPR,0);
	 }
	 else if(Copy_u8PageNum<8)
	 {
		status= GET_BIT( FPEC->WRPR,1);
	 }
	 else if(Copy_u8PageNum<12)
	 {
		status= GET_BIT( FPEC->WRPR,2);
	 }
	  else if(Copy_u8PageNum<20)
	 {
		status= GET_BIT( FPEC->WRPR,4);
	 }
	  else if(Copy_u8PageNum<24)
	 {
		status= GET_BIT( FPEC->WRPR,5);
	 }
	  else if(Copy_u8PageNum<28)
	 {
		status= GET_BIT( FPEC->WRPR,6);
	 }
	  else if(Copy_u8PageNum<32)
	 {
		status= GET_BIT( FPEC->WRPR,7);
	 }
	 }
	 else {
		 if(Copy_u8PageNum<36)
	 {
		status= GET_BIT( FPEC->WRPR,8);
	 }
	 else if(Copy_u8PageNum<40)
	 {
		status=  GET_BIT( FPEC->WRPR,9);
	 }
	 else if(Copy_u8PageNum<44)
	 {
		 
		status=  GET_BIT( FPEC->WRPR,10);
	 }
	  else if(Copy_u8PageNum<48)
	 {
		 
		status=  GET_BIT( FPEC->WRPR,11);
	 }
	  else if(Copy_u8PageNum<52)
	 {
		
		status=  GET_BIT( FPEC->WRPR,12);
	 }
	  else if(Copy_u8PageNum<56)
	 {
		 
		 status= GET_BIT( FPEC->WRPR,13);
	 }
	  else if(Copy_u8PageNum<60)
	 {
		 
		 status= GET_BIT( FPEC->WRPR,14);
	 }
		 else if(Copy_u8PageNum<64)
	 {
		 
		 status= GET_BIT( FPEC->WRPR,15);
	 }
	
	 }
	   
	  
		return status;
	}*/
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
	// lock flash 
	FPEC_voidFlashLock();
}
