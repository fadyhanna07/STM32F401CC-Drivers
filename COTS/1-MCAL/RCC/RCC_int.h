/*******************************************/
/*RCC Driver
Target: stm32f401
Author :FADY
 Date:2023-02-01*/
/*******************************************/
#ifndef _RCC_INT_H
#define _RCC_INT_H
/***************************************************************************************                                               
* Description :  Voltage reference options  
*      [1] Set system clock
*      [2] Get system clock
       [3] check clock ready or not
       [4] Enable system clock
       [5] Configure PLL P M R Q
       [6] Configure Bus Prescaler
       [7] Enable Peripheral clock
       [8] Disable Peripheral clock
*      
*****************************************************************************************/

/***************************************************************************************                                               
* Description :   Clock system Options 
*      [1] RCC_SYS_CLK_HSE
       [2] RCC_SYS_CLK_HSI
       [3] RCC_SYS_CLK_PLL
*****************************************************************************************/
#define     RCC_SYS_CLK_HSI             0x00000000
#define     RCC_SYS_CLK_HSE             0x00000001
#define     RCC_SYS_CLK_PLL             0x00000002
/***************************************************************************************                                               
* Description :   the available buses in the system
*****************************************************************************************/
#define	    RCC_AHB1    4
#define	    RCC_AHB2    1
#define	    RCC_APB1    10
#define	    RCC_APB2	  13
/***************************************************************************************                                               
* Description :   RCC AHB1 peripheralS
*****************************************************************************************/
#define	    RCC_GPIOA		0
#define	    RCC_GPIOB		1
#define	    RCC_GPIOC		2
#define	    RCC_GPIOD		3
#define	    RCC_GPIOE		4
#define	    RCC_GPIOH		7
#define	    RCC_CRC		12
#define	    RCC_DMA1		21
#define	    RCC_DMA2		22
/***************************************************************************************                                               
* Description :   RCC AHB2 peripheralS
*****************************************************************************************/
#define	 RCC_OTGFS		    7
/***************************************************************************************                                               
* Description :   RCC APB1 peripheralS
*****************************************************************************************/
#define	    RCC_TIM2		0
#define	    RCC_TIM3		1
#define	    RCC_TIM4		2
#define	    RCC_TIM5		3
#define	    RCC_WWDG		11
#define	    RCC_SPI2		14
#define	    RCC_SPI3		15
#define	    RCC_USART2	17
#define	    RCC_I2C1		21
#define	    RCC_I2C2		22
#define	    RCC_I2C3		23
#define	    RCC_PWR		28
/***************************************************************************************                                               
* Description :   RCC APB2 peripheralS
*****************************************************************************************/
#define	    RCC_TIM1		0
#define	    RCC_USART1	4
#define	    RCC_USART6	5
#define	    RCC_ADV1		8
#define	    RCC_SDIO		11
#define	    RCC_SPI1		12
#define	    RCC_SPI4		13
#define	    RCC_SYSCD		14
#define	    RCC_TIM9		16
#define	    RCC_TIM10		17
#define	    RCC_TIM11		18
/***************************************************************************************                                               
* Description :   the System Clk prescaler options (AHP1)
*****************************************************************************************/
#define	RCC_SYSTEM_CLK_NOT_DIVIDED		0b0000
#define 	RCC_SYSTEM_CLK_DIVIDED_2		0b1000
#define 	RCC_SYSTEM_CLK_DIVIDED_4   	 	0b1001
#define 	RCC_SYSTEM_CLK_DIVIDED_8   	 	0b1010
#define 	RCC_SYSTEM_CLK_DIVIDED_16  	 	0b1011
#define 	RCC_SYSTEM_CLK_DIVIDED_64   	0b1100
#define 	RCC_SYSTEM_CLK_DIVIDED_128 	 	0b1101
#define 	RCC_SYSTEM_CLK_DIVIDED_256  	0b1110
#define 	RCC_SYSTEM_CLK_DIVIDED_512  	0b1111
/***************************************************************************************                                               
* Description :   the APB prescaler options  (APB1 & APB2)
*****************************************************************************************/
#define		RCC_AHPCLK_NOT_DIVIDED           0b000
#define		RCC_AHPCLK_DIVIDED_2             0b100
#define		RCC_AHPCLK_DIVIDED_4             0b101
#define		RCC_AHPCLK_DIVIDED_8             0b110
#define		RCC_AHPCLK_DIVIDED_16	     0b111


/*********************************  types  *******************************************************************************/

/***************************************************************************************                                               
* Description :   An Enum Datatype used to return Error status 
*****************************************************************************************/
typedef enum
{
	RCC_enuOK,
	RCC_enuNOTOK,
       RCC_enuCLK_NotRdy,
	RCC_enuInvalid_CLK_Source,
	RCC_enuInvalid_Prepheral,
	RCC_enuInvalid_BUS,
	RCC_enuNullPtr,
	RCC_enuTimeOUT

}RCC_tenuErrorStatus;

/*********************************  Functions prototype  *******************************************************************************/

/***************************************************************************************                                               
* Description :  Select a clock to be the system clock                     
* Input  : Clock system Options (select to be the system clock)
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuSetSysClock (u8 Cpy_u8SysClock);

/***************************************************************************************                                               
* Description :  Get the current system clock                     
* Input  : Pointer to return the current system clock 
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuGetSysClock (u8 * Add_u8SysClock);

/***************************************************************************************                                               
* Description :  Enable any Clock from System clocks                   
* Input  : Clock system Options 
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuEnableSysClock (u8 Cpy_u8SysClock);

/***************************************************************************************                                               
* Description :  check the clock ready or no                    
* Input  : (Clock system Options , Pointer to return the clock is ready or no)
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuCheckSysClock (u8 Cpy_u8SysClock, u8 * Add_u8SysClock);

/***************************************************************************************                                               
* Description :  Configure PLL Sys Clock                   
* Input  : [Source clock [HSI , HSE] ,M , N , P , Q ]
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuConfigurePLL (u8 Cpy_u8SrcClock , u8 Cpy_u8Factor_M , u8 Cpy_u8Factor_N, u8 Cpy_u8Factor_P , u8 Cpy_u8Factor_Q);
/***************************************************************************************                                               
* Description :  Configure Bus Prescaler                  
* Input  : [Bus , prescaler options ]
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuConfigureBusPrescaler (u8 Cpy_u8Bus, u8 Cpy_u8Prescaler);
/***************************************************************************************                                               
* Description :  Enable Peripheral Clock                
* Input  : [Bus , prepheral ]
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePerClock (u8 Cpy_u8Bus, u8 Cpy_u8Peripheral);
/***************************************************************************************                                               
* Description :  Disable Peripheral Clock                
* Input  : [Bus , prepheral ]
* Return:  error statues
*****************************************************************************************/
RCC_tenuErrorStatus RCC_enuDisablePerClock (u8 Cpy_u8Bus, u8 Cpy_u8Peripheral);
#endif /*RCC_INT_H*/
