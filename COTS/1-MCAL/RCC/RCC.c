/*******************************************/
/*RCC Driver
Target: stm32f401
Author :FADY
 Date:2023-02-01 */ 
/*******************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_int.h"
#include "RCC_Prv.h"

/* some macros refers to bit numbers and Masks used to clear and set reg values */

/*Description :  Waiting time for Clock to be ready */
#define Clk_WaitingTime              30 
/***************************************************************************************                                               
* Description :  Clock security system Control
*  ---> [Enable , Disable]
*****************************************************************************************/
#define     RCC_CSS_Clear			    0xFFF7FFFF  
#define     RCC_CSS_ON				    0x00080000
/***************************************************************************************                                               
* Description : Control available system clocks
*****************************************************************************************/
#define     RCC_HSE_CRYSTA_ON           0x00010000
#define     RCC_HSE_RC_ON               0x00050000
#define     RCC_HSI_ON                  0x00000001
#define     RCC_PLL_ON                  0x01000000
  /*this mask to clear the sys clk source */
#define RCC_SYS_CLK_CLR_MASK          0xFFFFFFFC  
/***************************************************************************************                                               
* Description :  check Clock system is ready or no (Options) 
*****************************************************************************************/
#define RCC_HSE_Ready                17       
#define RCC_HSI_Ready                1       
#define RCC_PLL_Ready                25
/**************************************************************************** 
* Description :  Masks to clear PLL Factors bits
*****************************************************************************************/
#define RCC_PLLCFG_CLR_MASK		   0xF0FC8000
/**************************************************************************** 
* Description :  Masks of PLL Factors positions
*****************************************************************************************/
#define RCC_FACTOR_Q_POS	24
#define RCC_FACTOR_P_POS	16
#define RCC_FACTOR_N_POS	6
#define RCC_FACTOR_M_POS	0
#define RCC_PLLSRC_POS	  22
/**************************************************************************** 
* Description :  Masks to clear PLL Factors bits
*****************************************************************************************/
#define RCC_AHP_CLR_MASK		   0xFFFFFF0F
#define RCC_APB1_CLR_MASK		   0xFFFFE3FF
#define RCC_APB2_CLR_MASK		   0xFFFF1FFF
/**************************************************   Functions Implementaion  *********************************************************/
RCC_tenuErrorStatus RCC_enuSetSysClock (u8 Cpy_u8SysClock)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
  u32 Loc_u32TempReg = 0;
  u8 Loc_u8SysClock_ready = 0;
switch (Cpy_u8SysClock)
  {
    case RCC_SYS_CLK_HSI :
       Loc_u8SysClock_ready = RCC_HSI_Ready;
       break;
    case RCC_SYS_CLK_HSE :
       Loc_u8SysClock_ready = RCC_HSE_Ready;
       break;
    case RCC_SYS_CLK_PLL :
       Loc_u8SysClock_ready = RCC_PLL_Ready;
       break;

  }
if(GET_BIT(RCC_CR,Loc_u8SysClock_ready) == 0)
  {
    Loc_enuErrorStatus = RCC_enuCLK_NotRdy;
  }
else 
  {
    Loc_u32TempReg = RCC_CFGR;
    Loc_u32TempReg &= RCC_SYS_CLK_CLR_MASK;
    Loc_u32TempReg |= Cpy_u8SysClock;
    RCC_CFGR = Loc_u32TempReg;
  }
return Loc_enuErrorStatus;
}
/**********************************  GetSysClock  **************************************************/
RCC_tenuErrorStatus RCC_enuGetSysClock (u8 * Add_u8SysClock)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
  if(Add_u8SysClock == NULL )
  {
    Loc_enuErrorStatus = RCC_enuNullPtr;
  }
  else
  {
  *Add_u8SysClock =( (GET_BIT(RCC_CFGR,2)) | (GET_BIT(RCC_CFGR,3) << 1));
  }
 return Loc_enuErrorStatus;
}
/**************************************  EnableSysClock  ***********************************************/
RCC_tenuErrorStatus RCC_enuEnableSysClock (u8 Cpy_u8SysClock)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
  u32 Loc_u32TempReg = 0;
  u8 Loc_u8Timeout = Clk_WaitingTime;
  u8 Loc_u8SysClock_ON = 0;
  u8 Loc_u8SysClock_ready = 0;
  // this switch case used to know which sysclock the user want to enable 
switch (Cpy_u8SysClock)
  {
    case RCC_SYS_CLK_HSE :
      Loc_u8SysClock_ON = RCC_HSE_CRYSTA_ON;
      Loc_u8SysClock_ready = RCC_HSE_Ready;
      break;
    case RCC_SYS_CLK_HSI :
      Loc_u8SysClock_ON = RCC_HSI_ON;
      Loc_u8SysClock_ready = RCC_HSI_Ready;
      break;
    case RCC_SYS_CLK_PLL :
      Loc_u8SysClock_ON = RCC_PLL_ON;
      Loc_u8SysClock_ready = RCC_PLL_Ready;
      break;
  }
  
  Loc_u32TempReg = RCC_CR;
  Loc_u32TempReg |= Loc_u8SysClock_ON;
  RCC_CR = Loc_u32TempReg;
  while(GET_BIT(RCC_CR,Loc_u8SysClock_ready)  == 0 && --Loc_u8Timeout >0);
  if (Loc_u8Timeout == 0)
  {
    Loc_enuErrorStatus = RCC_enuTimeOUT;
  }
  else {Loc_enuErrorStatus = RCC_enuOK;}
return Loc_enuErrorStatus;
}
/**********************************  CheckSysClock ready or no  ********************************************************************/
RCC_tenuErrorStatus RCC_enuCheckSysClock (u8 Cpy_u8SysClock, u8 * Add_u8SysClock)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
   u8 Loc_u8SysClock_ready = 0;
  switch (Cpy_u8SysClock)
  {
    case RCC_SYS_CLK_HSI :
       Loc_u8SysClock_ready = RCC_HSI_Ready;
       break;
    case RCC_SYS_CLK_HSE :
       Loc_u8SysClock_ready = RCC_HSE_Ready;
       break;
    case RCC_SYS_CLK_PLL :
       Loc_u8SysClock_ready = RCC_PLL_Ready;
       break;

  }
  if(GET_BIT(RCC_CR,Loc_u8SysClock_ready) == 0)
  {
    Loc_enuErrorStatus = RCC_enuCLK_NotRdy;
  }
  else {Loc_enuErrorStatus = RCC_enuOK;}
return Loc_enuErrorStatus;
}
/******************************************  ConfigurePLL  *************************************************/
RCC_tenuErrorStatus RCC_enuConfigurePLL (u8 Cpy_u8SrcClock , u8 Cpy_u8Factor_M , u8 Cpy_u8Factor_N, u8 Cpy_u8Factor_P , u8 Cpy_u8Factor_Q)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
  u32 Loc_u32TempReg = RCC_PLLCFGR;
  Loc_u32TempReg &= RCC_PLLCFG_CLR_MASK;
  Loc_u32TempReg |= ((Cpy_u8Factor_M << RCC_FACTOR_M_POS) | (Cpy_u8Factor_N << RCC_FACTOR_N_POS) | (Cpy_u8Factor_P << RCC_FACTOR_P_POS) | (Cpy_u8Factor_Q << RCC_FACTOR_Q_POS));
  RCC_PLLCFGR = Loc_u32TempReg;
  if(Cpy_u8SrcClock == RCC_SYS_CLK_HSI)
  {
    CLR_BIT(RCC_PLLCFGR,RCC_PLLSRC_POS);
  }
  else if(Cpy_u8SrcClock == RCC_SYS_CLK_HSE)
  {
    SET_BIT(RCC_PLLCFGR,RCC_PLLSRC_POS);
  }
  else 
  {
    Loc_enuErrorStatus = RCC_enuInvalid_CLK_Source;
  }
return Loc_enuErrorStatus;
}
/*******************************************  ConfigureBusPrescaler  *************************************************************/
RCC_tenuErrorStatus RCC_enuConfigureBusPrescaler (u8 Cpy_u8Bus, u8 Cpy_u8Prescaler)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
  u32 Loc_u32TempReg = RCC_CFGR;
  switch (Cpy_u8Bus)
  {
  case RCC_AHB1:
    Loc_u32TempReg &= RCC_AHP_CLR_MASK;
    Loc_u32TempReg |= (Cpy_u8Prescaler << RCC_AHB1);
    RCC_CFGR = u32 Loc_u32TempReg;
    break;
  case RCC_APB1:
    Loc_u32TempReg &= RCC_APB1_CLR_MASK;
    Loc_u32TempReg |= (Cpy_u8Prescaler << RCC_APB1);
    RCC_CFGR = u32 Loc_u32TempReg;
    break;
  case RCC_APB2:
    Loc_u32TempReg &= RCC_APB2_CLR_MASK;
    Loc_u32TempReg |= (Cpy_u8Prescaler << RCC_APB2);
    RCC_CFGR = u32 Loc_u32TempReg;
    break;
  
  default: Loc_enuErrorStatus = RCC_enuInvalid_BUS; 
    break;
  }
  return Loc_enuErrorStatus;
}
/***************************************  EnablePerClock  ********************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePerClock (u8 Cpy_u8Bus, u8 Cpy_u8Peripheral)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
 switch (Cpy_u8Bus)
  {
  case RCC_AHB1: SET_BIT(RCC_AHB1ENR,Cpy_u8Peripheral);   break;
  case RCC_APB1: SET_BIT(RCC_APB1ENR,Cpy_u8Peripheral);   break;
  case RCC_APB2: SET_BIT(RCC_APB2ENR,Cpy_u8Peripheral);   break;
  default: Loc_enuErrorStatus = RCC_enuInvalid_BUS;       break;
  }
  return Loc_enuErrorStatus;
}
/***************************************  DisablePerClock  **********************************************************/
RCC_tenuErrorStatus RCC_enuDisablePerClock (u8 Cpy_u8Bus, u8 Cpy_u8Peripheral)
{
  RCC_tenuErrorStatus Loc_enuErrorStatus = RCC_enuOK; 
 switch (Cpy_u8Bus)
  {
  case RCC_AHB1: CLR_BIT(RCC_AHB1ENR,Cpy_u8Peripheral);   break;
  case RCC_APB1: CLR_BIT(RCC_APB1ENR,Cpy_u8Peripheral);   break;
  case RCC_APB2: CLR_BIT(RCC_APB2ENR,Cpy_u8Peripheral);   break;
  default: Loc_enuErrorStatus = RCC_enuInvalid_BUS;       break;
  }
  return Loc_enuErrorStatus;
}
