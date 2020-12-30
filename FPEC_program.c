/********************************************************/
/* Author : Nourhan Mansour                             */
/* Date   : 11/11/2020                                  */
/* Version: 2.0                                         */
/* File   : FPEC_program.c                              */
/********************************************************/

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers

// 3- include driver files
#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"

void FPEC_voidInit() {
	// Unlock flash memory

	/**************************
	 The key values are:
	 RDPRT key = 0x00A5
	 KEY1 = 0x45670123
	 KEY2 = 0xCDEF89AB
	 **************************/
	FPEC_KEYR = 0x45670123;
	FPEC_KEYR = 0xCDEF89AB;

}

void FPEC_UnlockOptionBytes(){
	/**************************
	 The key values are:
	 RDPRT key = 0x00A5
	 KEY1 = 0x45670123
	 KEY2 = 0xCDEF89AB
	 **************************/
	FPEC_OPTKEYR  = 0x45670123;
	FPEC_OPTKEYR  = 0xCDEF89AB;

}

void FPEC_voidLock() {
	/*
	 When SET: FPEC and FLASH_CR are locked
	 This bit is reset by hardware after
	 detecting the unlock sequence.
	 */
	SET_BIT(FPEC_CR , FLASH_CR_LOCK);
}

void FPEC_voidLockOptionBytes()
{
    /* Software Reset */
    CLR_BIT(FPEC_CR , FLASH_CR_OPTWRE);
}

u16 FPEC_u32ReadData(u16 * cpy_address) {
	u16 val = *((volatile u16 *) cpy_address);
	return val;

}

void FPEC_voidWriteData(u16 * cpy_address, u16 * cpy_data, u8 cpy_length) {
	u16 * dataPtr = cpy_data;
	u8 i;
	// data write (half word)
	// Set PG bit
	SET_BIT(FPEC_CR, FLASH_CR_PG);
	for (i = 0; i < cpy_length; i++) {
		// Write Data
		*((volatile u16*) (cpy_address)) = *dataPtr;
		cpy_address++;
		dataPtr++;
		// wait BSY flag
		while ( GET_BIT (FPEC_SR , FLASH_SR_BSY) == 1)
			;
		/* EOP */
		SET_BIT(FPEC_SR, FLASH_SR_EOP);
		CLR_BIT(FPEC_CR, FLASH_CR_PER);
	}
	// Disable Programming
	CLR_BIT(FPEC_CR, FLASH_CR_PG);

}

void FPEC_voidEraseDataPage(u8 cpy_page) {
	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC_CR ,FLASH_CR_LOCK) == 1) {
		FPEC_KEYR = 0x45670123;
		FPEC_KEYR = 0xCDEF89AB;
	}
	/* Wait Busy Flag */
	while (GET_BIT(FPEC_SR,FLASH_SR_BSY) == 1)
		;

	// SET PER bit
	SET_BIT(FPEC_CR, FLASH_CR_PER);

	// select Page to erase in AR register
	FPEC_AR = (u32) (cpy_page * 1024) + 0x08000000;

	// Set STRT bit
	SET_BIT(FPEC_CR, FLASH_CR_STRT);

	// Wait for BSY bit
	while ( GET_BIT (FPEC_SR , FLASH_SR_BSY) == 1)
		;
	/* EOP */
	SET_BIT(FPEC_SR, FLASH_SR_EOP);
	CLR_BIT(FPEC_CR, FLASH_CR_PER);

	// Disable Erase
	CLR_BIT(FPEC_CR, FLASH_CR_PER);

}

void FPEC_voidEraseAllFlash() {
	// Set the MER bit in the FLASH_CR register
	SET_BIT(FPEC_CR, FLASH_CR_MER);
	// Set the STRT bit in the FLASH_CR register
	SET_BIT(FPEC_CR, FLASH_CR_STRT);
	// Wait for the BSY bit to be reset
	while ( GET_BIT (FPEC_SR , FLASH_SR_BSY) == 1)
		;
	// Read all the pages and verify
	SET_BIT(FPEC_SR, FLASH_SR_EOP);
	CLR_BIT(FPEC_CR, FLASH_CR_PER);
	// Disable Erase
	CLR_BIT(FPEC_CR, FLASH_CR_PER);

}

void FPEC_voidEraseRange(u8 cpy_startPage, u8 cpy_endPage)
{
	if (cpy_endPage > cpy_startPage && cpy_endPage <= MAX_PAGE_NO) {
		u8 i;
		for (i = cpy_startPage; i <= cpy_endPage; i++) {
			FPEC_voidEraseDataPage(i);
		}
	}
}


u8 FPEC_CheckForErrors()
{
    if(GET_BIT (FPEC_SR , FLASH_SR_WRPRTERR))
        return WRITE_PROTECTION_ERROR;
    if (GET_BIT (FPEC_SR , FLASH_SR_PGERR))
        return PROGRAMMING_ERROR;
    return SUCCESSFULLL_OPERATION;
}
