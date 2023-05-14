/*******************************************/
/*File name: SWITCH_int.h
Author :FADY
/*******************************************/
#ifndef _SWITCH_INT_H
#define _SWITCH_INT_H

#include "SWITCH_Cfg.h"
/*********************************  types  *******************************************************************************/
typedef enum{
    Switch_Released=0,
    Switch_Pressed
}Switch_state_t;
/*********************************  Functions prototype  *******************************************************************************/
/***************************************************************************************                                               
* Description :  init the Switch configration                   
* Input  : none
* Return:  none
*****************************************************************************************/
void Switch_init(void);
/***************************************************************************************                                               
* Description :  Get the switch state                  
* Input  : [Switch name ]
* Return:  the switch state
*****************************************************************************************/
Switch_state_t Switch_Get_state(Switch_name_t switch_name);

#endif /*SWITCH_INT_H*/
