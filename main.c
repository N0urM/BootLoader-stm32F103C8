#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"
#include "GPIO_interface.h"
#include "CRC_interface.h"
#define MAX_RECIEVED_DATA	2
int main() {

	RCC_voidInitSystemClock();								// Init System Clock
	RCC_voidEnableClock(t_APB2 , RCC_APB2ENR_USART1EN);		// Init Clock for UART1
	RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPAEN);  		// Init Clock PortA
	RCC_voidEnableClock(t_AHB , RCC_AHBENR_FLITFEN);		// Init Clock for Flash Drive

	FPEC_voidFlashInit();										// Init Flash Driver
	UART1_voidInit();										// Init UART

	/* Configure TX & RX pins for UART */
	GPIO_voidInitPortPinDirection(PORTA  , 9  , 0b1001);      // TX PIN
	GPIO_voidInitPortPinDirection(PORTA  , 10 , 0b0100);	  // RX PIN

	/* Test Code */
	UART1_voidTransmitSync( "HELLO WORLD!!!" , 14);
	volatile u8 recievedArr [MAX_RECIEVED_DATA];

	while (1)
	{
			UART1_voidRecieveSync( MAX_RECIEVED_DATA , recievedArr);
			UART1_voidTransmitSync(recievedArr , 2);
	}
	return 0;
}
