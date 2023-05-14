/*******************************************/
/*File name: SWITCH_Cfg.c 
Author :FADY
/*******************************************/
#include "../../4-LIB/STD_TYPES.h"
#include "../../4-LIB/BIT_MATH.h"
#include "../../1-MCAL/GPIO/GPIO_int.h"
#include "SWITCH_Cfg.h"

const Switch_cfg_t Switch_cfg[Switch_Count]={
    [Switch_1]= {.Port=GPIO_PORTA,
                  .Pin = 0,
                  .Speed = GPIO_Speed_VeryHigh,
                  .Pin_mode = GPIO_INPUT_PU,
                  .name = Switch_1,
                  .Active_Mode = Active_low},
    [Switch_2]= {.Port=GPIO_PORTA,
                  .Pin = 1,
                  .Speed = GPIO_Speed_VeryHigh,
                  .Pin_mode = GPIO_INPUT_PU,
                  .name = Switch_2,
                  .Active_Mode = Active_low},
    [Switch_3]= {.Port=GPIO_PORTA,
                  .Pin = 2,
                  .Speed = GPIO_Speed_VeryHigh,
                  .Pin_mode = GPIO_INPUT_PU,
                  .name = Switch_3,
                  .Active_Mode = Active_low}
}