/*******************************************/
/*File name: LED_Cfg.c 
Author :FADY
/*******************************************/
#include "../../4-LIB/STD_TYPES.h"
#include "../../4-LIB/BIT_MATH.h"
#include "../../1-MCAL/GPIO/GPIO_int.h"
#include "LED_Cfg.h"

const Led_cfg_t Led_cfg[Led_Count]={
    [Led_Alarm]= {.Port=GPIO_PORTA,
                  .Pin = 0,
                  .Speed = GPIO_Speed_VeryHigh,
                  .name = Led_Alarm,
                  .Active_Mode = Active_high},
    [Led_Stop]= {.Port=GPIO_PORTA,
                  .Pin = 1,
                  .Speed = GPIO_Speed_VeryHigh,
                  .name = Led_Stop,
                  .Active_Mode = Active_high},
    [Led_Warning]= {.Port=GPIO_PORTA,
                  .Pin = 2,
                  .Speed = GPIO_Speed_VeryHigh,
                  .name = Led_Warning,
                  .Active_Mode = Active_high}
}