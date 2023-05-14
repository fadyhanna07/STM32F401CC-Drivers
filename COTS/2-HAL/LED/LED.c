/*******************************************/
/*File name: LED.c 
Author :FADY
/*******************************************/
#include "../../4-LIB/STD_TYPES.h"
#include "../../4-LIB/BIT_MATH.h"
#include "../../1-MCAL/GPIO/GPIO_int.h"
#include "LED_Cfg.h"
#include "LED_int.h"
/******************************************  Functions Implementation  ************************************************************/

void Led_init(void){
    GPIO_CFG_t GPIO_CFG ;
    for( u8 idx=0;idx < Led_Count;idx++)
    {
        GPIO_CFG.Mode = GPIO_OUTPUT_PP;
        GPIO_CFG.Port = Led_cfg[idx].Port;
        GPIO_CFG.Port = Led_cfg[idx].Pin;
        GPIO_CFG.Port = Led_cfg[idx].Speed;
        GPIO_Init(&GPIO_CFG);
    }
}

void Led_set_state(Led_name_t led_name,Led_state_t led_state)
{
    GPIO_WritePinValue(Led_cfg[led_name].Port,Led_cfg[led_name].Pin,(led_state ^ Led_cfg[led_name].Active_Mode));
}

void Led_toggle(Led_name_t led_name)
{
    u8 error_status;
    u8 current_val = GPIO_GetPinValue(Led_cfg[led_name].Port,Led_cfg[led_name].Pin,& error_status);
    GPIO_WritePinValue(Led_cfg[led_name].Port,Led_cfg[led_name].Pin,(1 ^ current_val));
}

