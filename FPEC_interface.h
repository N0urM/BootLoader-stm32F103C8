/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 11/11/2020                                  */
/* Version: 2.0                                         */
/* File   : FPEC_interface.h                            */
/********************************************************/ 
#ifndef FPEC_INTERFACE_H
#define FPEC_INTERFACE_H


/******************** Public Constants **********************/
#define WRITE_PROTECTION_ERROR      0
#define PROGRAMMING_ERROR           1
#define SUCCESSFULLL_OPERATION      2

/****************** Functions prototypes ********************/

/*************************************************************
    Function Name: FPEC_voidInit
    Description  : Initialize Flash memory to enable data write
    Parameters   : none
    Return value : none
***************************************************************/
void FPEC_voidInit();

/*************************************************************
    Function Name: FPEC_UnlockOptionBytes
    Description  : Perform unlock sequence for option bytes
    Parameters   : none
    Return value : none
***************************************************************/
void FPEC_UnlockOptionBytes();

/*************************************************************
    Function Name: FPEC_voidLock
    Description  : Disable Flash Write Access 
    Parameters   : none
    Return value : none
***************************************************************/
void FPEC_voidLock();

/*************************************************************
    Function Name: FPEC_voidLockOptionBytes
    Description  : Disable Flash Write Access for option Bytes
    Parameters   : none
    Return value : none
***************************************************************/
void FPEC_voidLockOptionBytes();

/*************************************************************
    Function Name: FPEC_u32ReadData
    Description  : Read data from address cpy_address 
    Parameters   : cpy_address: Data ddress in Litte Indian 
    Return value : Word stored in specified address
***************************************************************/
u16 FPEC_u32ReadData(u16 * cpy_address);

/*************************************************************
    Function Name: FPEC_voidWriteData
    Description  : Assign data to a specific address
    Parameters   : cpy_address: start address of data to write
                   cpy_data   : array of data to send  
                   cpy_length : array length 
    Return value : none
***************************************************************/
void FPEC_voidWriteData ( u16 * cpy_address , u16 * cpy_data , u8 cpy_length);

/*************************************************************
    Function Name: FPEC_voidEraseDataPage
    Description  : Reset a page to initial state of all ones 
    Parameters   : cpy_page: pageNo to erase 
                             Page size = 1k 
                             Max No of pages in stm10x = 64
    Return value : none
***************************************************************/
void FPEC_voidEraseDataPage (u8 cpy_Page);

/*************************************************************
    Function Name: FPEC_voidEraseDataPage
    Description  : Specify a range of pages to clear 
    Parameters   : cpy_startPage: Start pageNo to erase 
                   cpy_endPage  : Final pageNo to erase        
    Return value : none
    Notes        : Page size = 1k
                   Max No of pages in stm10x = 64
                   Start page must be less than end page
***************************************************************/
void FPEC_voidEraseRange(u8 cpy_startPage , u8 cpy_endPage);

/*************************************************************
    Function Name: FPEC_voidEraseAllFlash
    Description  : Clear Flash Memory 
    Parameters   : none
    Return value : none
***************************************************************/
void FPEC_voidEraseAllFlash();

/*************************************************************
    Function Name: FPEC_CheckForErrors
    Description  : Check Error Flags in Status register
    Parameters   : none
    Return value : one of 3 values:
                    WRITE_PROTECTION_ERROR
                    PROGRAMMING_ERROR
                    SUCCESSFULLL_OPERATION
***************************************************************/
u8 FPEC_CheckForErrors();


#endif // End Of File
