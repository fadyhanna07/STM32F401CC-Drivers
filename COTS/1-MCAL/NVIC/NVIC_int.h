/*******************************************/
/*NVIC Driver
Target: stm32f401
Author :FADY
 Date:2023-03-11*/
/*******************************************/
#ifndef _NVIC_INT_H
#define _NVIC_INT_H
/*********************************  types  *******************************************************************************/
/***************************************************************************************                                               
* Description :   An Enum Datatype used to return Error status 
*****************************************************************************************/
typedef enum {
    NVIC_enuOK = 0,
    NVIC_enuNOTOK ,
    NVIC_enuNULLPOINTER 
}NVIC_tenuErrorStatus;

/*********************************  Functions prototype  *******************************************************************************/
/***************************************************************************************                                               
* Description :  Enables an interrupt or exception                    
* Input  : The number of the interrupt request ( 0 --> 239) 
* Return:  error statues
*****************************************************************************************/
NVIC_tenuErrorStatus NVIC_EnableIRQ(u8 IRQn);
/***************************************************************************************                                               
* Description :  Disable an interrupt or exception                    
* Input  : The number of the interrupt request ( 0 --> 239) 
* Return:  error statues
*****************************************************************************************/
NVIC_tenuErrorStatus NVIC_DisableIRQ(u8 IRQn);
/***************************************************************************************                                               
* Description :  Set pending for interrupt or exception                    
* Input  : The number of the interrupt request ( 0 --> 239) 
* Return:  error statues
*****************************************************************************************/
NVIC_tenuErrorStatus NVIC_SetPendingIRQ (u8 IRQn);
/***************************************************************************************                                               
* Description :  Get pending for interrupt or exception                    
* Input  :[ The number of the interrupt request ( 0 --> 239) , Address to return the error statues ] 
* Return:  pending value
*****************************************************************************************/
u8 NVIC_GetPendingIRQ (u8 IRQn , u8 * Add_u8ErrorStatus);
/***************************************************************************************                                               
* Description :  Clear pending for interrupt or exception                    
* Input  : The number of the interrupt request 
* Return:  error statues
*****************************************************************************************/
NVIC_tenuErrorStatus NVIC_ClearPendingIRQ (u8 IRQn);
/***************************************************************************************                                               
* Description :  Set priority for interrupt or exception                    
* Input : [ The number of the interrupt request ( 0 --> 239)  , the level of priority (0 --> 127) ]
* Return:  error statues
*****************************************************************************************/
NVIC_tenuErrorStatus NVIC_SetPriority(u8 IRQn, u8 priority);
/***************************************************************************************                                               
* Description :  Get priority for interrupt or exception                    
* Input : [ The number of the interrupt request ( 0 --> 239)  , Address to return the error statues]
* Return:  error statues
*****************************************************************************************/
u8 NVIC_GetPriority(u8 IRQn, u8 * Add_u8ErrorStatus);
/***************************************************************************************                                               
* Description :  Get Active for interrupt or exception                    
* Input : [ The number of the interrupt request ( 0 --> 239)  , Address to return the error statues]
* Return:  error statues
*****************************************************************************************/
u8 NVIC_GetActive(u8 IRQn, u8 * Add_u8ErrorStatus);
/***************************************************************************************                                               
* Description :  make SW trigger interrupt                    
* Input : The number of the interrupt request ( 0 --> 239)  
* Return:  error statues
*****************************************************************************************/
NVIC_tenuErrorStatus NVIC_SetSWTrigger(u8 IRQn);
#endif /*NVIC_INT_H*/
