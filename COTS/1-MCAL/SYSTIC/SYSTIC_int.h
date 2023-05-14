/*******************************************/
/*SYSTIC Driver
Target: stm32f401
Author :FADY
 Date:2023-03-21*/
/*******************************************/
#ifndef _SYSTIC_INT_H
#define _SYSTIC_INT_H

#define NULL  (void *)0

/*********************************  types  *******************************************************************************/
/***************************************************************************************                                               
* Description :   An Enum Datatype used to return Error status 
*****************************************************************************************/
typedef enum {
    SYSTIC_enuOK = 0,
    SYSTIC_enuNOTOK ,
    SYSTIC_enuInvalidParameter 
}SYSTIC_tenuErrorStatus;
/*********************************  Functions prototype  *******************************************************************************/
//1- start SYS
//2- stop SYS
//3- set cbf
//4- set period ms
//5- set period Ms
//6- enable exception
//7- disable exception
/***************************************************************************************                                               
* Description :  Configure the systic clock and the clock source                      
* Input  : none
* Return:  error statues
*****************************************************************************************/
void SysTick_CFG_ClockSource(void);
/***************************************************************************************                                               
* Description :  strart systic timer                      
* Input  : none
* Return:  error statues
*****************************************************************************************/
SYSTIC_tenuErrorStatus SysTick_Start(void);
/***************************************************************************************                                               
* Description :  stop systic timer                      
* Input  : none
* Return:  error statues
*****************************************************************************************/
SYSTIC_tenuErrorStatus SysTick_Stop(void);
/***************************************************************************************                                               
* Description :  Enable exception for systic                    
* Input  : none
* Return:  error statues
*****************************************************************************************/
SYSTIC_tenuErrorStatus SysTick_EnableException(void);
/***************************************************************************************                                               
* Description :  Disable exception for systic                    
* Input  : none
* Return:  error statues
*****************************************************************************************/
SYSTIC_tenuErrorStatus SysTick_DisableException(void);
/***************************************************************************************                                               
* Description :  set period time in ms                     
* Input  : period time
* Return:  error statues
*****************************************************************************************/
SYSTIC_tenuErrorStatus SysTick_SetPeriod_ms(s64 Cpy_period_ms);
/***************************************************************************************                                               
* Description :  set period time in Ms                     
* Input  : period time
* Return:  error statues
*****************************************************************************************/
SYSTIC_tenuErrorStatus SysTick_SetPeriod_Ms(s64 Cpy_period_Ms);
/***************************************************************************************                                               
* Description :  set cbf                     
* Input  : Address of cbf function
* Return:  error statues
*****************************************************************************************/
void SysTick_Setcbf(void (*cbf)(void));

#endif /*SYSTIC_INT_H*/
