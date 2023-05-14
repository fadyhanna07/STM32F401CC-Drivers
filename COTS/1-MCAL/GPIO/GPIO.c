/*******************************************/
/*GPIO Driver
Target: stm32f401
Author :FADY
 Date:2023-02-24 */ 
/*******************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_int.h"
/***************************************************  Types  **********************************************************/

typedef enum {
    Input=0,
    Output,
    AF,
    Analog
}CFG_Mode_t;
typedef enum {
    PP=0,
    OD
}CFG_OutputType_t;
typedef enum {
    PU=0,
    PD
}CFG_PU_PD_t;

typedef struct 
{
    u32 GPIO_MODER;
    u32 GPIO_OTYPER;
    u32 GPIO_OSPEEDR;
    u32 GPIO_PUPDR;
    u32 GPIO_IDR;
    u32 GPIO_ODR;
    u32 GPIO_BSRR;
    u32 GPIO_LCKR;
    u32 GPIO_AFRL;
    u32 GPIO_AFRH;
}GPIO_Registers_t;
static volatile GPIO_Registers_t *const GPIOA = ( volatile GPIO_Registers_t *const) 0x40020000;
static volatile GPIO_Registers_t *const GPIOB = ( volatile GPIO_Registers_t *const) 0x40020400;
static volatile GPIO_Registers_t *const GPIOC = ( volatile GPIO_Registers_t *const) 0x40020800;
static volatile GPIO_Registers_t *const GPIOD = ( volatile GPIO_Registers_t *const) 0x40020C00;
static volatile GPIO_Registers_t *const GPIOE = ( volatile GPIO_Registers_t *const) 0x40021000;
static volatile GPIO_Registers_t *const GPIOH = ( volatile GPIO_Registers_t *const) 0x40021C00;
/* some macros refers to bit numbers and Masks used to clear and set reg values */
/******************************************  static Functions  ************************************************************/
static volatile GPIO_Registers_t * Difne_Port(u8 port)
{
    volatile GPIO_Registers_t * GPIO_Port = 0;
    switch (port)
    {
    case GPIO_PORTA:
        GPIO_Port = GPIOA;
        break;
    case GPIO_PORTB:
        GPIO_Port = GPIOB;
        break;
        case GPIO_PORTC:
        GPIO_Port = GPIOC;
        break;
        case GPIO_PORTD:
        GPIO_Port = GPIOD;
        break;
        case GPIO_PORTE:
        GPIO_Port = GPIOE;
        break;
        case GPIO_PORTH:
        GPIO_Port = GPIOH;
        break;

    }
return GPIO_Port;
}
// this function configure mode [input - output - AF - Aanlog]
static void CFG_Mode(volatile GPIO_Registers_t *const port,u8 pin,CFG_Mode_t mode)
{
   volatile u32 Temp_Reg_MODER = port->GPIO_MODER;
   volatile u32 Temp_Reg_PUPDR = port->GPIO_PUPDR;
    //configure pin mode
       switch (mode)
       {
       case Input:
        CLR_BIT(Temp_Reg_MODER,(pin<<1));
        CLR_BIT(Temp_Reg_MODER,(pin<<1)+1);
        break;
       case Output:
        SET_BIT(Temp_Reg_MODER,(pin<<1));
        CLR_BIT(Temp_Reg_MODER,(pin<<1)+1);
        break;
       case AF:
        CLR_BIT(Temp_Reg_MODER,(pin<<1));
        SET_BIT(Temp_Reg_MODER,(pin<<1)+1);
        break;
        case Analog:
        SET_BIT(Temp_Reg_MODER,(pin<<1));
        SET_BIT(Temp_Reg_MODER,(pin<<1)+1);
        break;
       }
       port->GPIO_MODER = Temp_Reg_MODER;
    //configure pin as No pull-up, pull-down
       CLR_BIT(Temp_Reg_PUPDR,(pin<<1));
       CLR_BIT(Temp_Reg_PUPDR,(pin<<1)+1);
       port->GPIO_PUPDR = Temp_Reg_PUPDR; 
       
}
// CONFIGURE PIN AS PULL-POSH OR OPEN-DRAIN
static void CFG_OutputType(volatile GPIO_Registers_t *const port,u8 pin,CFG_OutputType_t OutputType)
{
    volatile u32 Temp_Reg_OTYPER = port->GPIO_OTYPER;
    switch (OutputType)
    {
    case PP:
        CLR_BIT(Temp_Reg_OTYPER,pin);
        break;
    case OD:
        SET_BIT(Temp_Reg_OTYPER,pin);
        break;
    }
       
       port->GPIO_OTYPER = Temp_Reg_OTYPER ;
}
// CONFIGURE PIN AS PULL-UP OR PULL-DOWN
static void CFG_PU_PD(volatile GPIO_Registers_t *const port,u8 pin,CFG_PU_PD_t type)
{
   volatile u32 Temp_Reg_PUPDR = port->GPIO_PUPDR;
   switch (type)
   {
   case PU:
    SET_BIT(Temp_Reg_PUPDR,(pin<<1));
    CLR_BIT(Temp_Reg_PUPDR,(pin<<1)+1);
    break;
   case PD:
    CLR_BIT(Temp_Reg_PUPDR,(pin<<1));
    SET_BIT(Temp_Reg_PUPDR,(pin<<1)+1);
    break;
   }
   port->GPIO_PUPDR = Temp_Reg_PUPDR; 
}
// CONFIGURE PIN SPEED
static void CFG_Speed(volatile GPIO_Registers_t *const port,u8 pin,GPIO_tenuPinSpeed speed)
{
    volatile u32 Temp_Reg_OSPEEDR = port->GPIO_OSPEEDR;
    switch (speed)
    {
    case GPIO_Speed_Low:
        CLR_BIT(Temp_Reg_OSPEEDR,(pin<<1));
        CLR_BIT(Temp_Reg_OSPEEDR,(pin<<1)+1);
        break;
    case GPIO_Speed_Medium:
        SET_BIT(Temp_Reg_OSPEEDR,(pin<<1));
        CLR_BIT(Temp_Reg_OSPEEDR,(pin<<1)+1);
        break;
    case  GPIO_Speed_High:
        CLR_BIT(Temp_Reg_OSPEEDR,(pin<<1));
        SET_BIT(Temp_Reg_OSPEEDR,(pin<<1)+1);
        break;
    case  GPIO_Speed_VeryHigh:
        SET_BIT(Temp_Reg_OSPEEDR,(pin<<1));
        SET_BIT(Temp_Reg_OSPEEDR,(pin<<1)+1);
        break;
    }
    port->GPIO_OSPEEDR = Temp_Reg_OSPEEDR ;
}


/******************************************  Functions Implementation  ************************************************************/
GPIO_tenuErrorStatus GPIO_Init(GPIO_CFG_t * Add_GPIO_CFG){
    GPIO_tenuErrorStatus Loc_enuErrorStatus = GPIO_enuOK;
    volatile GPIO_Registers_t * GPIO_Port = NULL;
    if(Add_GPIO_CFG == NULL) {Loc_enuErrorStatus = GPIO_enuNULLPOINTER;}
    else{
    GPIO_Port = Difne_Port(Add_GPIO_CFG->Port);
    switch (Add_GPIO_CFG->Mode)
    {
    case GPIO_OUTPUT_PP:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Output);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,PP);
        break;
    case GPIO_OUTPUT_PP_PU:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Output);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,PP);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PU);
        break;
    case GPIO_OUTPUT_PP_PD:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Output);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,PP);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PD);
        break;
    case GPIO_OUTPUT_OD:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Output);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,OD);
        break;
    case GPIO_OUTPUT_OD_PU:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Output);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,OD);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PU);
        break;
    case GPIO_OUTPUT_OD_PD:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Output);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,OD);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PD);
        break;
    case GPIO_AF_PP:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,AF);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,PP);
        break;
    case GPIO_AF_PP_PU:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,AF);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,PP);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PU);
        break;
    case GPIO_AF_PP_PD:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,AF);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,PP);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PD);
        break;
    case GPIO_AF_OD:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,AF);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,OD);
        break;
    case GPIO_AF_OD_PU:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,AF);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,OD);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PU);
        break;
    case GPIO_AF_OD_PD:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,AF);
        CFG_OutputType(GPIO_Port,Add_GPIO_CFG->Pin,OD);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PD);
        break;
    case GPIO_INPUT_FLOATING:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Input);
        break;
    case GPIO_INPUT_PU:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Input);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PU);
        break;
    case GPIO_INPUT_PD:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Input);
        CFG_PU_PD(GPIO_Port,Add_GPIO_CFG->Pin,PD);
        break;
    case GPIO_ANALOG_INPUT_OUTPUT:
        CFG_Mode(GPIO_Port,Add_GPIO_CFG->Pin,Analog);
        break;
    }
    CFG_Speed(GPIO_Port,Add_GPIO_CFG->Pin,Add_GPIO_CFG->Speed);
}
return Loc_enuErrorStatus;
}
GPIO_tenuErrorStatus GPIO_WritePinValue(u8 Cpy_u8Port, u8 Cpy_u8PinNum, u8 Cpy_u8Pin_Value)
{
    GPIO_tenuErrorStatus Loc_enuErrorStatus = GPIO_enuOK;
    volatile GPIO_Registers_t * GPIO_Port = Difne_Port(Cpy_u8Port);
    if(Cpy_u8Pin_Value == GPIO_PIN_LOW)
    {
        SET_BIT(GPIO_Port->GPIO_BSRR,Cpy_u8PinNum + 16);
    }
    else
    {
        SET_BIT(GPIO_Port->GPIO_BSRR,Cpy_u8PinNum);
    }

    return Loc_enuErrorStatus;
}
u8 GPIO_GetPinValue(u8 Cpy_u8Port, u8 Cpy_u8PinNum,u8 * Add_u8ErrorStatus)
{
    GPIO_tenuErrorStatus Loc_enuErrorStatus = GPIO_enuOK;
    volatile GPIO_Registers_t * GPIO_Port = Difne_Port(Cpy_u8Port);
    *Add_u8ErrorStatus = Loc_enuErrorStatus;
    return GET_BIT(GPIO_Port->GPIO_IDR,Cpy_u8PinNum);
}
GPIO_tenuErrorStatus GPIO_WritePortValue(u8 Cpy_u8Port, u16 Cpy_u16Port_Value)
{
    GPIO_tenuErrorStatus Loc_enuErrorStatus = GPIO_enuOK;
    volatile GPIO_Registers_t * GPIO_Port = Difne_Port(Cpy_u8Port);
    GPIO_Port->GPIO_ODR = Cpy_u16Port_Value ;
    return Loc_enuErrorStatus;
}
GPIO_tenuErrorStatus GPIO_CFGLock(u8 Cpy_u8Port, u16 Cpy_u16Port_Value)
{  
    GPIO_tenuErrorStatus Loc_enuErrorStatus = GPIO_enuOK;
    volatile GPIO_Registers_t * GPIO_Port = Difne_Port(Cpy_u8Port);
    u8 lockcheck=0;
    u32 lock_key = Cpy_u16Port_Value;
    SET_BIT(lock_key,16);
    GPIO_Port->GPIO_LCKR = lock_key;
    CLR_BIT(lock_key,16);
    GPIO_Port->GPIO_LCKR = lock_key;
    SET_BIT(lock_key,16);
    GPIO_Port->GPIO_LCKR = lock_key;
    lockcheck = GET_BIT(GPIO_Port->GPIO_LCKR,16);

    return Loc_enuErrorStatus;

}
