/*******************************************/
/*File name: LED_int.h
Author :FADY
/*******************************************/
#ifndef _LED_INT_H
#define _LED_INT_H

#include "LED_Cfg.h"
/*********************************  types  *******************************************************************************/
typedef enum{
    Led_OFF=0,
    Led_ON
}Led_state_t;
/*********************************  Functions prototype  *******************************************************************************/
/***************************************************************************************                                               
* Description :  init the Led configration                   
* Input  : none
* Return:  none
*****************************************************************************************/
void Led_init(void);
/***************************************************************************************                                               
* Description :  Set the led state (on - off)                  
* Input  : [Led name - Led state]
* Return:  none
*****************************************************************************************/
void Led_set_state(Led_name_t led_name,Led_state_t led_state);
/***************************************************************************************                                               
* Description :  toggle led                  
* Input  : [Led name ]
* Return:  none
*****************************************************************************************/
void Led_toggle(Led_name_t led_name);
#endif /*LED_INT_H*/
