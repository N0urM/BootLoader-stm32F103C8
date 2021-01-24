/*****************************************************************************************************************/
/* Author  : Eman ashraf                                                                                         */
/* version : v01                                                                                                 */
/* Date    : 11\11\2020                                                                                    */ 
/*****************************************************************************************************************/
#ifndef _FPEC_INTERFACE_H
#define _FPEC_INTERFACE_H

/****************** Functions prototypes ********************/

/*************************************************************
    Function Name: FPEC_voidInit
    Description  : Initialize Flash memory to enable data write
    Parameters   : none
    Return value : none
***************************************************************/
void FPEC_voidFlashInit(void);

/*************************************************************
    Function Name: FPEC_u16ReadHalfWord
    Description  : Read data(16 bits) from page cpyPage 
										at offset cpy_offset
    Parameters   : cpyPage: Data page 
									cpy_offset: data offset
    Return value : Word stored in specified address
***************************************************************/
u16 FPEC_u16ReadHalfWord(u8 cpyPage , u16 cpy_offset);

/*************************************************************
    Function Name: FPEC_u32ReadWord
    Description  : Read data(32 bits) from page cpyPage 
										at offset cpy_offset
    Parameters   : 	cpyPage: Data page 
										cpy_offset: data offset
    Return value : Word stored in specified address
***************************************************************/
u32  FPEC_u32ReadWord(u8 copyPage , u16 offset1);

/*************************************************************
    Function Name: FPEC_voidFlashWrite
    Description  : Assign data to a specific address
    Parameters   : cpyPage: start page of data to write
										offset: start offset at specified page
                   cpy_data: array of data to send  
                   cpy_length: array length 
    Return value : none
***************************************************************/
void FPEC_voidFlashWrite(u8 * Copy_u8Data ,u8 cpyPage , u16 Copy_u8DataArrayLength , u16 offset);

/*************************************************************
    Function Name: FPEC_voidFlashPageErase
    Description  : Reset a page to initial state of all ones 
    Parameters   : Copy_u8PageNumber: pageNo to erase 
                             Page size = 1k 
                             Max No of pages in stm10x = 64
    Return value : none
***************************************************************/
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

/*************************************************************
    Function Name: FPEC_voidEraseAppArea
    Description  : Delete a range of pages specified in the config file 
    Parameters   : none      
    Return value : none
    Notes        : Page size = 1k
                   Max No of pages in stm10x = 64
***************************************************************/
void FPEC_voidEraseAppArea(void);

/*************************************************************
    Function Name: FPEC_voidLock
    Description  : Disable Flash Write Access 
    Parameters   : none
    Return value : none
***************************************************************/
void FPEC_voidFlashLock(void);

#endif
