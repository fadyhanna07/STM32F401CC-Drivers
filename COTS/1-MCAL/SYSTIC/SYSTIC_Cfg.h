/*******************************************/
/*SYSTIC Driver
Target: stm32f401
Author :FADY
 Date:2023-03-21*/
/*******************************************/
#ifndef _SYSTIC_CFG_H
#define _SYSTIC_CFG_H

// source clock options
#define SysTick_Clk_AHB     0
#define SysTick_Clk_AHB_8   1
/***************************  confire the SYSTIC clock  **************************************/

#define SysTick_Clk_MHZ         25

/***************************  confire the source clock  **************************************/
#define SysTick_Src_Clk     SysTick_Clk_AHB

#endif /*SYSTIC_CFG_H*/
