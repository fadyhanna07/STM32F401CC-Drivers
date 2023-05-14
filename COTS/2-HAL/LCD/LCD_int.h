/*******************************************/
/*LCD Driver
Target: ATMEGA32
Author :FADY
 Date:2023-03-29*/
/*******************************************/
#ifndef _LCD_INT_H
#define _LCD_INT_H
#include "LCD_Cfg.h"
/*********************************  types  *******************************************************************************/
/***************************************************************************************                                               
* Description :   An Enum Datatype used to return Error status 
*****************************************************************************************/
typedef enum {
    LCD_enuOK = 0,
    LCD_enuNOTOK ,
    LCD_enuBusy,
    LCD_enuNULLPOINTER 
}LCD_tenuErrorStatus;
typedef enum {
    LCD_Idle = 0,
    LCD_Busy
}LCD_status_t;
typedef enum {
    Req_NoREq = 0,
    Req_Write ,
    Req_Clear
}User_Req_t;
/*********************************  Functions prototype  *******************************************************************************/

/***************************************************************************************                                               
* Description :  Write String on LCD                
* Input  : [ String ]
* Return:  error statues
*****************************************************************************************/
LCD_tenuErrorStatus LCD_enuWriteStringAsync(char * str );
/***************************************************************************************                                               
* Description :  Write Special Char on LCD                
* Input  : [ String ]
* Return:  error statues
*****************************************************************************************/
LCD_tenuErrorStatus LCD_enuWriteSpecialCharAsync(char * str );
/***************************************************************************************                                               
* Description :  Go to x , y position on LCD                
* Input  : [ Position x (0,1)- Position y (0 --> 15)]
* Return:  error statues
*****************************************************************************************/
LCD_tenuErrorStatus LCD_enuGoToXY(u8 pos_x ,u8 pos_y );

/***************************************************************************************                                               
* Description :  Init LCD                
* Input  : none
* Return:  error statues
*****************************************************************************************/
LCD_tenuErrorStatus LCD_enuInit();
/***************************************************************************************                                               
* Description :  Clear LCD Display              
* Input  : none
* Return:  error statues
*****************************************************************************************/
LCD_tenuErrorStatus LCD_enuClearDisplayAsync();
/***************************************************************************************                                               
* Description :  LCD Task to init and then check the data buffer and write on LCD // 2 ms               
* Input  : none
* Return:  none
*****************************************************************************************/
void LCD_Task(void);
#endif /*LCD_INT_H*/
