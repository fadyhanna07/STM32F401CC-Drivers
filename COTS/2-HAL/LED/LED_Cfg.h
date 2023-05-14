/*******************************************/
/*File name: LED_Cfg.h
Author :FADY
/*******************************************/
#ifndef _LED_CFG_H
#define _LED_CFG_H

typedef enum{
    Active_high=0,
    Active_low
}Led_mode_t;

typedef enum{
    Led_Alarm=0,
    Led_Stop,
    Led_Warning,
    Led_Count
}Led_name_t;
typedef struct 
{
    u8 Port;
    u8 Pin;
    GPIO_tenuPinSpeed Speed;
    Led_mode_t Active_Mode;
    Led_name_t name;

}Led_cfg_t;

extern const Led_cfg_t Led_cfg[Led_Count]; 
#endif /*LED_CFG_H*/
