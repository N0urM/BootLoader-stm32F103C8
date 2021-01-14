/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                        */ 
/*****************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CRC_interface.h"
#include "CRC_private.h"
#include "CRC_config.h"


u32 CRC_u32Claculate(u32 Copy_u32Data)
{
	 CRC->CRC_DR = Copy_u32Data ;
      return CRC->CRC_DR ;	 
}


void CRC_u32Claculate2(u32 Copy_u32Data)
{
	 CRC->CRC_DR = Copy_u32Data ;

}
u32 CRC_u32GetCrc()
{
	return CRC->CRC_DR ;

}
void CRC_voidReset()
{
	CRC->CRC_CR=CRC_RESET ;
}
