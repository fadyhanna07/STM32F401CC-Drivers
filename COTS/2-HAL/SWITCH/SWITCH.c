/*******************************************/
/*File name: SWITCH.c 
Author :FADY
/*******************************************/
#include "../../4-LIB/STD_TYPES.h"
#include "../../4-LIB/BIT_MATH.h"
#include "../../1-MCAL/GPIO/GPIO_int.h"
#include "SWITCH_Cfg.h"
#include "SWITCH_int.h"
/******************************************  Functions Implementation  ************************************************************/
Switch_state_t Switch_state[Switch_Count];
void Switch_init(void){
    GPIO_CFG_t GPIO_CFG[Switch_Count] ;
    for( u8 idx=0;idx < Switch_Count;idx++)
    {
        GPIO_CFG.Mode = Switch_cfg[idx].Pin_mode;
        GPIO_CFG.Port = Switch_cfg[idx].Port;
        GPIO_CFG.Port = Switch_cfg[idx].Pin;
        GPIO_CFG.Port = Switch_cfg[idx].Speed;
        GPIO_Init(&GPIO_CFG);
    }
}
/*********************************************************************************************/
Switch_state_t Switch_Get_state(Switch_name_t switch_name)
{
    return Switch_state[switch_name];
}
/*********************************************************************************************/
void Switch_Task(void)
{
    static u8 Counter[Switch_Count];
    static u8 Prev[Switch_Count];
    u8 Current;
    u8 error_status[Switch_Count];
    for(u8 idx=0;idx < Switch_Count; idx++)
    {
        Current =  GPIO_GetPinValue(Switch_cfg[idx].Port,Switch_cfg[idx].Pin,error_status + idx);
        if(Current == Prev[idx])
        {
            Counter[idx]++;
        }
        else{
            Counter[idx]=0;
        }
        if(Counter[idx]==5)
        {
            Switch_state[idx] = Current ^ Switch_cfg[idx].Active_Mode;
            Counter[idx] = 0;
        }
        else{}
        Prev[idx] =Current; 
    }

}
