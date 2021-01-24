#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"
#include "GPIO_interface.h"
#include "CRC_interface.h"
#include "IWDG_interface.h"

int main() {

	RCC_voidInitSystemClock();														// Init System Clock
	RCC_voidEnableClock(t_APB2 , RCC_APB2ENR_USART1EN);		// Init Clock for UART1
	RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPAEN);  		// Init Clock PortA
	RCC_voidEnableClock(t_AHB , RCC_AHBENR_FLITFEN);			// Init Clock for Flash Drive
	RCC_voidEnableClock(t_AHB , RCC_AHBENR_CRCEN);				// Init Clocl for CRC module
	
	FPEC_voidFlashInit();																	// Init Flash Driver
	UART1_voidInit();										    							// Init UART1

	/* Configure TX & RX pins for UART */
	GPIO_voidInitPortPinDirection(PORTA  , 9  , 0b1001);      // TX PIN
	GPIO_voidInitPortPinDirection(PORTA  , 10 , 0b0100);	  	// RX PIN

	/* Main BL function */
	BL_voidProcessPayLoadMain();
	while (1)
	{
	}
	return 0;
}
