/*******************************************/
/*SYSTIC Driver
Target: stm32f401
Author :FADY
 Date:2023-03-21 */ 
/*******************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SYSTIC_Cfg.h"
#include "SYSTIC_int.h"
typedef struct 
{
    u32 STK_CTRL;
    u32 STK_LOAD;
    u32 STK_VAL;
    u32 STK_CALIB;
  
}SYSTIC_Registers_t;
static volatile SYSTIC_Registers_t *const SYSTIC = ( volatile SYSTIC_Registers_t *const) 0xE000E010;
static void (*SYSTICK_callback)(void) = NULL;
/******************************************  Functions Implementation  ************************************************************/
void SysTick_CFG_ClockSource(void)
{
    #if		SysTick_Src_Clk == SysTick_Clk_AHB
			SET_BIT(SYSTIC->STK_CTRL,2);
	#elif   SysTick_Src_Clk == SysTick_Clk_AHB_8
			CLR_BIT(SYSTIC->STK_CTRL,2);
    #endif
}
SYSTIC_tenuErrorStatus SysTick_Start(void)
{
    SYSTIC_tenuErrorStatus Loc_enuErrorStatus = SYSTIC_enuOK;
    u32 TempReg = SYSTIC->STK_CTRL;
    SET_BIT(TempReg,0);
    SYSTIC->STK_CTRL = TempReg ;
    return Loc_enuErrorStatus;
}

SYSTIC_tenuErrorStatus SysTick_Stop(void)
{
    SYSTIC_tenuErrorStatus Loc_enuErrorStatus = SYSTIC_enuOK;
    u32 TempReg = SYSTIC->STK_CTRL;
    CLR_BIT(TempReg,0);
    SYSTIC->STK_CTRL = TempReg ;
    return Loc_enuErrorStatus;
}
SYSTIC_tenuErrorStatus SysTick_EnableException(void)
{
    SYSTIC_tenuErrorStatus Loc_enuErrorStatus = SYSTIC_enuOK;
    u32 TempReg = SYSTIC->STK_CTRL;
    SET_BIT(TempReg,1);
    SYSTIC->STK_CTRL = TempReg ;
    return Loc_enuErrorStatus;
}
SYSTIC_tenuErrorStatus SysTick_DisableException(void)
{
    SYSTIC_tenuErrorStatus Loc_enuErrorStatus = SYSTIC_enuOK;
    u32 TempReg = SYSTIC->STK_CTRL;
    CLR_BIT(TempReg,1);
    SYSTIC->STK_CTRL = TempReg ;
    return Loc_enuErrorStatus;
}
SYSTIC_tenuErrorStatus SysTick_SetPeriod_ms(s64 Cpy_period_ms)
{
    SYSTIC_tenuErrorStatus Loc_enuErrorStatus = SYSTIC_enuOK;
    u32 Max_Tics = 0xffffff;
    s64 Ticks_per_ms = SysTick_Clk_MHZ * 1000;
    s64 Ticks = 0;
    #if		SysTick_Src_Clk == SysTick_Clk_AHB
			Ticks = Cpy_period_ms * Ticks_per_ms;
	#elif   SysTick_Src_Clk == SysTick_Clk_AHB_8
			Ticks = Cpy_period_ms * (Ticks_per_ms/8);
    #endif

    if(Ticks > Max_Tics)
    {
            Loc_enuErrorStatus = SYSTIC_enuInvalidParameter;
    }
    else
    {
        SYSTIC->STK_LOAD = (u32)Ticks;
    }
    return Loc_enuErrorStatus;
}
SYSTIC_tenuErrorStatus SysTick_SetPeriod_Ms(s64 Cpy_period_Ms)
{
    SYSTIC_tenuErrorStatus Loc_enuErrorStatus = SYSTIC_enuOK;
    u32 Max_Tics = 0xffffff;
    s64 Ticks_per_Ms = SysTick_Clk_MHZ ;
    s64 Ticks = 0;
    #if		SysTick_Src_Clk == SysTick_Clk_AHB
			Ticks = Cpy_period_Ms * Ticks_per_Ms;
	#elif   SysTick_Src_Clk == SysTick_Clk_AHB_8
			Ticks = Cpy_period_Ms * (Ticks_per_Ms/8);
    #endif

    if(Ticks > Max_Tics)
    {
            Loc_enuErrorStatus = SYSTIC_enuInvalidParameter;
    }
    else
    {
        SYSTIC->STK_LOAD = (u32)Ticks;
    }
    return Loc_enuErrorStatus;
}
void SysTick_Setcbf(void (*cbf)(void))
{
    SYSTICK_callback = cbf;
}

void __attribute__ ((section(".after_vectors")))
SysTick_Handler (void)
{
 if (SYSTICK_callback != NULL) {
		SYSTICK_callback();
	}
}
