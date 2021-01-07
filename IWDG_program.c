/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                          */ 
/*****************************************************************************************************************/
 #include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "IWDG_interface.h"
#include "IWDG_private.h"
#include "IWDG_config.h"


void IWDG_voidReset()
{
	// write value  0x5555  to modify vale of prescaler and relaod counter
	IWDG->KR= 0x5555 ;
	
	//write values 
	IWDG->PR=0x0;
	IWDG->RLR=0x000;
	
	//write key of reload 
	IWDG->KR= 0xAAAA ;
	
	//start counter 
	IWDG->KR =0xCCCC ;

	SET_BIT(DBGMCU_CR,8);
	
}
