/*******************************************/
/*GPIO Driver
Target: stm32f401
Author :FADY
 Date:2023-02-24*/
/*******************************************/
#ifndef _GPIO_INT_H
#define _GPIO_INT_H
/*********************************  defines  *******************************************************************************/
/***************************************************************************************                                               
* Description :   GPIO Ports
*****************************************************************************************/
#define GPIO_PORTA  0
#define GPIO_PORTB  1
#define GPIO_PORTC  2
#define GPIO_PORTD  3
#define GPIO_PORTE  4
#define GPIO_PORTH  5
/***************************************************************************************                                               
* Description :   GPIO PIN VALUE
*****************************************************************************************/
#define GPIO_PIN_LOW    0 
#define GPIO_PIN_HIGH   1

#define NULL  (void *)0
/*********************************  types  *******************************************************************************/
/***************************************************************************************                                               
* Description :   An Enum Datatype used to define the Pin Mode
*****************************************************************************************/
typedef enum {
    GPIO_OUTPUT_PP=0,
    GPIO_OUTPUT_PP_PU,
    GPIO_OUTPUT_PP_PD,
    GPIO_OUTPUT_OD,
    GPIO_OUTPUT_OD_PU,
    GPIO_OUTPUT_OD_PD,
    GPIO_AF_PP,
    GPIO_AF_PP_PU,
    GPIO_AF_PP_PD,
    GPIO_AF_OD,
    GPIO_AF_OD_PU,
    GPIO_AF_OD_PD,
    GPIO_INPUT_FLOATING,
    GPIO_INPUT_PU,
    GPIO_INPUT_PD,
    GPIO_ANALOG_INPUT_OUTPUT
}GPIO_tenuPinModeCFG;
/***************************************************************************************                                               
* Description :   Pin Speed Options
*****************************************************************************************/
typedef enum{
    GPIO_Speed_Low=0,
    GPIO_Speed_Medium,
    GPIO_Speed_High,
    GPIO_Speed_VeryHigh
}GPIO_tenuPinSpeed;
/***************************************************************************************                                               
* Description :   An Enum Datatype used to return Error status 
*****************************************************************************************/
typedef enum {
    GPIO_enuOK = 0,
    GPIO_enuNOTOK ,
    GPIO_enuNULLPOINTER 
}GPIO_tenuErrorStatus;

typedef struct GPIO_int_Pin
{
   u8 Port;
   u8 Pin;
   GPIO_tenuPinSpeed Speed;
   GPIO_tenuPinModeCFG Mode;
}GPIO_CFG_t;

/*********************************  Functions prototype  *******************************************************************************/
/***************************************************************************************                                               
* Description :  Initialize the GPIO pin                      
* Input  : address of struct object ( GPIO_CFG_t ) which contain [ Port - Pin - Speed - Mode ]
* Return:  error statues
*****************************************************************************************/
GPIO_tenuErrorStatus GPIO_Init(GPIO_CFG_t * Add_GPIO_CFG);

/***************************************************************************************                                               
* Description :  Write value in the GPIO Pin                      
* Input  :  [ Port - Pin - Pin value (GPIO_PIN_High - GPIO_PIN_Low)]
* Return:  error statues
*****************************************************************************************/
GPIO_tenuErrorStatus GPIO_WritePinValue(u8 Cpy_u8Port, u8 Cpy_u8PinNum, u8 Cpy_u8Pin_Value);

/***************************************************************************************                                               
* Description :  Get the GPIO pin value                      
* Input  :  [ Port - Pin - Address to return the error statues]
* Return:  Pin value
*****************************************************************************************/
u8 GPIO_GetPinValue(u8 Cpy_u8Port, u8 Cpy_u8PinNum,u8 * Add_u8ErrorStatus);

/***************************************************************************************                                               
* Description :  Write value in the GPIO Port                       
* Input  :  [ Port - Port value ]
* Return:  error statues
*****************************************************************************************/
GPIO_tenuErrorStatus GPIO_WritePortValue(u8 Cpy_u8Port, u16 Cpy_u16Port_Value);

/***************************************************************************************                                               
* Description :  configure the lock register in the GPIO Port                       
* Input  :  [ Port - Port value ]
* Return:  error statues
*****************************************************************************************/
GPIO_tenuErrorStatus GPIO_CFGLock(u8 Cpy_u8Port, u16 Cpy_u16Port_Value);
#endif /*GPIO_INT_H*/
