
#include "STD_TYPES.h"
#include "Bit_Math.h"


#include "DMA.h"


#define Channel_POS           25
#define Memory_Burst_POS      23
#define Peripheral_Burst_POS  21
#define Double_Buffer_POS     18
#define Priority_Cfg_POS      16
#define Memory_Size_POS       13
#define Circular_Mode_POS     11
#define Data_Direction_POS    10
#define Transfer_Complete_POS 9
#define HalfTransfer_POS      8
#define Transfer_Err_POS      6
#define Direct_Mode_POS       4

#define CLR_MASK			0xF

/*******************typedef************************/

/*Register Address*/
typedef struct
{
	u32	LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;

	struct
	{
		u32 SxCR;
		u32 SxNDTR;
		u32 SxPAR;
		u32 SxM0AR;
		u32 SxM1AR;
		u32 SxFCR;

	}Cfg_Reg[8];

}DMA_tRegister;


#define DMA1_REGISTER	((DMA_tRegister*)0x40026000)

#define DMA2_REGISTER	((DMA_tRegister*)0x40026400)



/**************Private Value******************/
static DMA_CallFunction CallFunction[2][8];


/********************Function definition************************/

DMA_tenuErrorStatus DMA_enuConfiguration(DMA_ID DMA, const DMA_config_t* ConfigPtr)
{
	DMA_tenuErrorStatus Loc_enuErrorStatus = DMA_enuOk;

	u32 Loc_u32TempRegister = 0;

	if(ConfigPtr)
	{
		if(DMA == DMA1)
		{
			Loc_u32TempRegister = ConfigPtr->Channel << 25 | ConfigPtr->Memory_Burst << 23 | ConfigPtr->Peripheral_Burst << 21 |
					ConfigPtr->Double_Buffer << 18 | ConfigPtr->Priority_Cfg << 16 | ConfigPtr->Memory_Size << 13 |
					ConfigPtr->Peripheral_Size << 11 | ConfigPtr->Mem_Auto_Increment << 10 | ConfigPtr->Per_Auto_Increment << 9 |
					ConfigPtr->Circular_Mode << 8 |  ConfigPtr->Data_Direction << 6 | ConfigPtr->Interrupt.Transfer_Complete << 4 |
					ConfigPtr->Interrupt.HalfTransfer << 3 | ConfigPtr->Interrupt.Transfer_Err << 2 |
					ConfigPtr->Interrupt.Direct_Mode << 1;
			CLR_BIT(DMA1_REGISTER->Cfg_Reg[ConfigPtr->Stream].SxCR,0);
			/*Store the configuration in the register*/
			DMA1_REGISTER->Cfg_Reg[ConfigPtr->Stream].SxCR = Loc_u32TempRegister;
		}


		else if(DMA == DMA2)
		{
			Loc_u32TempRegister = ConfigPtr->Channel << 25 | ConfigPtr->Memory_Burst << 23 | ConfigPtr->Peripheral_Burst << 21 |
					ConfigPtr->Double_Buffer << 18 | ConfigPtr->Priority_Cfg << 16 | ConfigPtr->Memory_Size << 13 |
					ConfigPtr->Peripheral_Size << 11 | ConfigPtr->Mem_Auto_Increment << 10 | ConfigPtr->Per_Auto_Increment << 9 |
					ConfigPtr->Circular_Mode << 8 |  ConfigPtr->Data_Direction << 6 | ConfigPtr->Interrupt.Transfer_Complete << 4 |
					ConfigPtr->Interrupt.HalfTransfer << 3 | ConfigPtr->Interrupt.Transfer_Err << 2 |
					ConfigPtr->Interrupt.Direct_Mode << 1;
			CLR_BIT(DMA2_REGISTER->Cfg_Reg[ConfigPtr->Stream].SxCR,0);
			/*Store the configuration in the register*/
			DMA2_REGISTER->Cfg_Reg[ConfigPtr->Stream].SxCR = Loc_u32TempRegister;
			//DMA2_REGISTER->Cfg_Reg[ConfigPtr->Stream].SxCR |= (1<<0);
		}

		else
		{
			Loc_enuErrorStatus = DMA_enu_Undifined_Value;
		}
	}

	else
	{
		Loc_enuErrorStatus = DMA_enuNullPtr;
	}

	return Loc_enuErrorStatus;

}




DMA_tenuErrorStatus DMA_enuCritariaChannel(DMA_ID DMA, const Criteria_t* CriteriaPtr)
{
	DMA_tenuErrorStatus Loc_enuErrorStatus = DMA_enuOk;

	if(CriteriaPtr)
	{
		if(DMA == DMA1)
		{
			CLR_BIT(DMA1_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxCR,0);
			DMA1_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxPAR = CriteriaPtr->Peripheral_Address;
			DMA1_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxM0AR = CriteriaPtr->Memory_0_Address;
			DMA1_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxM1AR = CriteriaPtr->Memory_1_Address;
			DMA1_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxNDTR = CriteriaPtr->Block_Length;
			SET_BIT(DMA1_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxCR,0);
		}

		else if(DMA == DMA2)
		{
			CLR_BIT(DMA2_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxCR,0);
			DMA2_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxPAR = CriteriaPtr->Peripheral_Address;
			DMA2_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxM0AR = CriteriaPtr->Memory_0_Address;
			DMA2_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxM1AR = CriteriaPtr->Memory_1_Address;
			DMA2_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxNDTR = CriteriaPtr->Block_Length;
			SET_BIT(DMA2_REGISTER->Cfg_Reg[CriteriaPtr->Stream].SxCR,0);

		}

		else
		{
			Loc_enuErrorStatus = DMA_enu_Undifined_Value;
		}
	}

	else
	{
		Loc_enuErrorStatus = DMA_enuNullPtr;
	}

	return Loc_enuErrorStatus;
}



DMA_tenuErrorStatus DMA_enuRegisterCallFunction(DMA_ID DMA, DMA_StreamId Stream, DMA_CallFunction Cbf)
{
	DMA_tenuErrorStatus Loc_enuErrorStatus = DMA_enuOk;

	if(Cbf)
	{

		CallFunction[DMA][Stream] = Cbf;
	}
	else
	{
		Loc_enuErrorStatus = DMA_enuNullPtr;
	}

	return Loc_enuErrorStatus;
}


DMA_tenuErrorStatus DMA_enuStreamState(DMA_ID DMA, DMA_StreamId Stream, DMA_State Condition)
{
	DMA_tenuErrorStatus Loc_enuErrorStatus = DMA_Stream_En;

	if(Stream > 7)
	{
		Loc_enuErrorStatus = DMA_enu_Undifined_Value;
	}


	switch (DMA)
	{
	case DMA1:
		DMA1_REGISTER->Cfg_Reg[Stream].SxCR |= Condition;
		break;

	case DMA2:
		DMA2_REGISTER->Cfg_Reg[Stream].SxCR |= Condition;
		break;

	default:
		Loc_enuErrorStatus = DMA_enu_Undifined_Value;
		break;

	}

	return Loc_enuErrorStatus;

}



void DMA1_Stream0_IRQHandler(void)
{
	if((DMA1_REGISTER->LISR >> 5 & 1) == 1)
	{
		if(CallFunction[DMA_Stream0])
		{
			DMA1_REGISTER->LIFCR &= ~(1 << 5);
			CallFunction[DMA1][DMA_Stream0]();
		}
	}
	else
	{
		//Include Error
	}

}

void DMA1_Stream1_IRQHandler(void)
{
	if((DMA1_REGISTER->LISR >> 5 & 1) == 1)
	{
		if(CallFunction[DMA_Stream0])
		{
			DMA1_REGISTER->LIFCR &= ~(1 << 5);
			CallFunction[DMA1][DMA_Stream0]();
		}
	}
	else
	{
		//Include Error
	}
}

void DMA1_Stream2_IRQHandler(void)
{

}

void DMA1_Stream3_IRQHandler(void)
{

}

void DMA1_Stream4_IRQHandler(void)
{

}



void DMA1_Stream6_IRQHandler(void)
{

}

void DMA1_Stream7_IRQHandler(void)
{

}


/*****DMA2 Handler**************/

void DMA2_Stream7_IRQHandler(void)
{
	if((DMA2_REGISTER->HISR >> 27 & 1) == 1)
	{
		if(CallFunction[DMA_Stream7])
		{
			DMA2_REGISTER->HIFCR |= 1 << 27;
			CallFunction[DMA2][DMA_Stream7]();
		}
	}
	else
	{
		//Include Error
	}
}

void DMA2_Stream6_IRQHandler(void)
{
	if((DMA2_REGISTER->HISR >> 21 & 1) == 1)
	{
		if(CallFunction[DMA_Stream6])
		{
			DMA2_REGISTER->HIFCR |= 1 << 21;
			CallFunction[DMA2][DMA_Stream6]();
		}
	}
	else
	{
		//Include Error
	}
}

void DMA2_Stream2_IRQHandler(void)
{
	if((DMA2_REGISTER->LISR >> 21 & 1) == 1)
	{
		if(CallFunction[DMA_Stream2])
		{
			DMA2_REGISTER->LIFCR |= 1 << 21;
			CallFunction[DMA2][DMA_Stream2]();
		}
	}
	else
	{
		//Include Error
	}
}
void DMA2_Stream5_IRQHandler(void)
{
	if((DMA2_REGISTER->HISR >> 11 & 1) == 1)
	{
		if(CallFunction[DMA_Stream5])
		{
			DMA2_REGISTER->HIFCR |= 1 << 11;
			CallFunction[DMA2][DMA_Stream5]();
		}
	}
	else
	{
		//Include Error
	}

}






