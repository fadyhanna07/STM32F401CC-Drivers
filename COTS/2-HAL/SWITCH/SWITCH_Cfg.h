/*******************************************/
/*File name: SWITCH_Cfg.h
Author :FADY
/*******************************************/
#ifndef _SWITCH_CFG_H
#define _SWITCH_CFG_H

typedef enum{
    Active_high=0,
    Active_low
}Switch_mode_t;

typedef enum{
    Switch_1=0,
    Switch_2,
    Switch_3,
    Switch_Count
}Switch_name_t;
typedef struct 
{
    u8 Port;
    u8 Pin;
    GPIO_tenuPinSpeed Speed;
    GPIO_tenuPinModeCFG Pin_mode;
    Switch_mode_t Active_Mode;
    Switch_name_t name;

}Switch_cfg_t;

extern const Switch_cfg_t Switch_cfg[Switch_Count]; 
#endif /*SWITCH_CFG_H*/
