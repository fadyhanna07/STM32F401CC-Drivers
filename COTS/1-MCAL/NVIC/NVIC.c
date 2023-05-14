/*******************************************/
/*NVIC Driver
Target: stm32f401
Author :FADY
 Date:2023-03-11 */ 
/*******************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NVIC_int.h"

#define    NVIC_STIR    0xE000EF00
typedef struct 
{
  u32 NVIC_ISER[8]; //set enable interrupt
  u32 Reserved[24];
  u32 NVIC_ICER[8]; //Clear enable interrupt
  u32 Reserved2[24];
  u32 NVIC_ISPR[8]; //set Pending
  u32 Reserved3[24];
  u32 NVIC_ICPR[8]; //Clear Pending
  u32 Reserved4[24];
  u32 NVIC_IAPR[8]; //Active (read only)
  u32 Reserved5[56];
  u8 NVIC_IPR[240]; //Set Priority
}NVIC_Registers_t;
static volatile NVIC_Registers_t *const NVIC = ( volatile NVIC_Registers_t *const) 0xE000E100;

/******************************************  Functions Implementation  ************************************************************/
NVIC_tenuErrorStatus NVIC_EnableIRQ(u8 IRQn)
{
    NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;
    if (IRQn < 0 || IRQn > 239)
    {
        Loc_enuErrorStatus == NVIC_enuNOTOK;
    }
    else {
        volatile u32 Temp_Reg = NVIC->NVIC_ISER[(IRQn / 32)];
        SET_BIT(Temp_Reg,(IRQn % 32));
        NVIC->NVIC_ISER[(IRQn / 32)] = Temp_Reg;
    }
    return Loc_enuErrorStatus;
}
NVIC_tenuErrorStatus NVIC_DisableIRQ(u8 IRQn)
{
      NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;
    if (IRQn < 0 || IRQn > 239)
    {
        Loc_enuErrorStatus == NVIC_enuNOTOK;
    }
    else {
        volatile u32 Temp_Reg = NVIC->NVIC_ICER[(IRQn / 32)];
        SET_BIT(Temp_Reg,(IRQn % 32));
        NVIC->NVIC_ICER[(IRQn / 32)] = Temp_Reg;
    }
    return Loc_enuErrorStatus
}

NVIC_tenuErrorStatus NVIC_SetPendingIRQ (u8 IRQn)
{
     NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;
    if (IRQn < 0 || IRQn > 239)
    {
        Loc_enuErrorStatus == NVIC_enuNOTOK;
    }
    else {
        volatile u32 Temp_Reg = NVIC->NVIC_ISPR[(IRQn / 32)];
        SET_BIT(Temp_Reg,(IRQn % 32));
        NVIC->NVIC_ISPR[(IRQn / 32)] = Temp_Reg;
    }
    return Loc_enuErrorStatus
}

u8 NVIC_GetPendingIRQ (u8 IRQn , u8 * Add_u8ErrorStatus)
{
    NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;
    u8 Pending_IRQ = -1;
    if (IRQn < 0 || IRQn > 239)
    {
        Loc_enuErrorStatus == NVIC_enuNOTOK;
    }
    else {
        volatile u32 Temp_Reg = NVIC->NVIC_ISPR[(IRQn / 32)];
        Pending_IRQ = GET_BIT(Temp_Reg,(IRQn % 32));       
    }
    *Add_u8ErrorStatus = Loc_enuErrorStatus;
    return Pending_IRQ;
}
NVIC_tenuErrorStatus NVIC_ClearPendingIRQ (u8 IRQn)
{
      NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;
    if (IRQn < 0 || IRQn > 239)
    {
        Loc_enuErrorStatus == NVIC_enuNOTOK;
    }
    else {
        volatile u32 Temp_Reg = NVIC->NVIC_ICPR[(IRQn / 32)];
        SET_BIT(Temp_Reg,(IRQn % 32));
        NVIC->NVIC_ICPR[(IRQn / 32)] = Temp_Reg;
    }
    return Loc_enuErrorStatus
}

NVIC_tenuErrorStatus NVIC_SetPriority(u8 IRQn, u8 priority)
{
    NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;
   // volatile u32 * priority_pos =  (&(NVIC->NVIC_IPR[IRQn / 4])) + ( IRQn % 4);
    if (IRQn < 0 || IRQn > 239 || priority < 0 )
    {
        Loc_enuErrorStatus == NVIC_enuNOTOK;
    }
    else {
       NVIC->NVIC_IPR[IRQn] = priority;
    }
}
u8 NVIC_GetPriority(u8 IRQn, u8 * Add_u8ErrorStatus)
{
     NVIC_tenuErrorStatus Loc_enuErrorStatus = NVIC_enuOK;
    u8 Priority = -1;
    if (IRQn < 0 || IRQn > 239)
    {
        Loc_enuErrorStatus == NVIC_enuNOTOK;
    }
    else {
        Priority =  NVIC->NVIC_IPR[IRQn];
    }
    * Add_u8ErrorStatus = Loc_enuErrorStatus;
    return Priority;
}
u8 NVIC_GetActive(u8 IRQn, u8 * Add_u8ErrorStatus)
{
    
}

