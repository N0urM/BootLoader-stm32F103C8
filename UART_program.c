/********************************************************/
/* Author : Nourhan Mansour                             */
/* Date   : 24/9/2020                                   */
/* Version: 2.0                                         */
/* File   : UART_program.c                              */
/********************************************************/

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers

// 3- include driver files
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"



void UART1_voidInit() {

			// Baud Rate selection 115200
			USART1_BRR = 0x46;

			// Clear configuration bits
			USART1_CR1 = 0;

			// Enable TX - RX
			SET_BIT(USART1_CR1, USART_CR1_TE);
			SET_BIT(USART1_CR1, USART_CR1_RE);

			// Enable UART
			SET_BIT(USART1_CR1, USART_CR1_UE);

			// Clear Status Register
			USART1_SR = 0;

}

void UART1_voidDeInit() {

		// Clear Baud Rate selection
		USART1_BRR = 0;

		// Clear configuration bits
		USART1_CR1 = 0;

		// Clear Status Register
		USART1_SR = 0;

}
void UART1_voidTransmitSync(u8 cpy_arr[] , u8 cpy_arrLen) {
	u16 i = 0;
	while (i != cpy_arrLen) 
	{
		USART1_DR = cpy_arr[i];
		while (GET_BIT (USART1_SR , USART_SR_TC) == 0);
		CLR_BIT(USART1_SR, USART_SR_TC);
		i++;
	}
}

void UART1_voidRecieveSync(u16 cpy_data_length,
		u8 * DataRecieved) {

	u16 local_idx = 0;
	while (local_idx < cpy_data_length) {
		while (GET_BIT (USART1_SR , USART_SR_RXNE) == 0)
			;
		CLR_BIT(USART1_SR, USART_SR_RXNE);
		DataRecieved[local_idx++] = 0xFF & USART1_DR;
	}
}
