/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 24/8/2020                                   */
/* Vesion: 3.0                                         */
/* File  : GPIO_interface.h                            */
/*******************************************************/ 
#ifndef     GPIO_INTERFACE_H
#define     GPIO_INTERFACE_H

/*********** Public data types *************/
typedef enum {
    PORTA,
    PORTB,
    PORTC,
}t_PORT;

/******************* public functions *************************/

/*
    Function Name: GPIO_voidInitPortPinDirection
    Description  : initializa a GPIO pin direction and mode
    Parameters   :  
        port: PORTA,PORTB,PORTC
        pin : 0-15
        mode: input/output selection 
    No return
*/
void GPIO_voidInitPortPinDirection(t_PORT cpy_port , u8 cpy_pin  ,u8 mode);


/*
    Function Name: GPIO_voidInitPortDirection
    Description  : initialize a GPIO port direction and mode
    Parameters   :  
        port: PORTA,PORTB,PORTC
        mode: input/output selection
    No return

*/
void GPIO_voidInitPortDirection (t_PORT cpy_port , u8 mode);

/*
    Function Name: GPIO_voidDeInitPortConfig
    Description  : Reset initialization of a GPIO port direction and mode
    Parameters   :
        port: PORTA,PORTB,PORTC
    No return
*/
void GPIO_voidDeInitPortConfig (t_PORT cpy_port);


#endif  // End Of File
