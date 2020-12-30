/********************************************************/ 
/* Author : Nourhan Mansour                             */
/* Date   : 24/9/2020                                   */
/* Version: 2.0                                         */
/* File   : UART_interface.h                            */
/********************************************************/ 
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


/****************** Functions prototypes ********************/

/*************************************************************
    Function Name: UART_voidInit
    Description  : Initialize UART(s) according to config file 
    Parameters   : none
    Return value : none
***************************************************************/
void UART1_voidInit();


/*************************************************************
    Function Name: UART_voidTransmitSync
    Description  : Send array of data through UART CH and halts
                   the processor till finish 
    Parameters   : cpy_ch : Specify which UART channel
                   cpy_arr: array of data to transmit
    Return value : none
***************************************************************/
void UART1_voidTransmitSync(u8 cpy_arr[] , u8 cpy_arrLen);

/*************************************************************
    Function Name: UART_u8RecieveSync
    Description  : Recieve a char of data through UART CH 
                   halt the processor till Recieve complete 
    Parameters   : cpy_ch : Specify which UART channel
    			   cpy_data_length: Length of data to expect in Bytes.
    Return value : byte recieved from UART CH
***************************************************************/
void  UART1_voidRecieveSync( u16 cpy_data_length , u8 * DataRecieved);


/*************************************************************
    Function Name: UART_voidInit
    Description  : DeInitialize UART channels
    Parameters   : none
    Return value : none
***************************************************************/
void UART1_voidDeInit();

#endif // End Of File
