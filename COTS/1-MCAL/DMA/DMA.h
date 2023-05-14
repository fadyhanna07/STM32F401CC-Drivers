
#ifndef MCAL_DMA_H_
#define MCAL_DMA_H_


typedef enum
{
	DMA_enuOk = 0 ,
	DMA_Stream_En ,
	DMA_Stream_Off,
	DMA_enu_Undifined_Value,
	DMA_enuNullPtr,
}DMA_tenuErrorStatus;

/*Call function back function data type*/
typedef void(*DMA_CallFunction)(void);

typedef enum
{
	DMA1 = 0,
	DMA2
}DMA_ID;
/*
 * User Define Type to checked well before configuring the DMA
 *
 * (DMA_Config_t)
 *
 * */
typedef enum
{
	DMA_Stream0 = 0,
	DMA_Stream1 = 1,
	DMA_Stream2 = 2,
	DMA_Stream3 = 3,
	DMA_Stream4 = 4,
	DMA_Stream5 = 5,
	DMA_Stream6 = 6,
	DMA_Stream7 = 7
}DMA_StreamId;

typedef enum
{
	DMA_Channel0 = 0,
	DMA_Channel1 = 1,
	DMA_Channel2 = 2,
	DMA_Channel3 = 3,
	DMA_Channel4 = 4,
	DMA_Channel5 = 5,
	DMA_Channel6 = 6,
	DMA_Channel7 = 7

}DMA_ChannelId;

typedef enum
{
	DMA_Low = 0,
	DMA_Medium,
	DMA_High,
	DMA_VeryHigh

}DMA_Priority_t;

typedef enum
{
	Byte = 0,
	Half_Word,
	Word,

}DMA_Size_t;

typedef enum
{
	Per_to_Mem = 0,
	Mem_to_Per,
	Mem_to_Mem

}DMA_Direction_t;

typedef enum
{

	DMA_DISABLE = 0,
	DMA_ENABLE
}DMA_State;

typedef enum
{
	Single = 0,
	Inc_4_Beats,
	Inc_8_Beats,
	Inc_16_Beats

}DMA_Burst_t;

/*
 * The struct is made to configure the DMA Channel
 *
 * !! Check all user define types (enum) above for each Mode as use from it
 *
 * !! TO USE IN FUCNTION :: DMA_enuConfiguration
 *
 * */
typedef struct
{
	DMA_StreamId 	Stream;
	DMA_ChannelId 	Channel;
	DMA_Burst_t		Memory_Burst;
	DMA_Burst_t 	Peripheral_Burst;
	DMA_State 		Double_Buffer;
	DMA_Priority_t  Priority_Cfg;
	DMA_Size_t		Memory_Size;
	DMA_Size_t		Peripheral_Size;
	DMA_State	    Mem_Auto_Increment;
	DMA_State 		Per_Auto_Increment;
	DMA_State 		Circular_Mode;
	DMA_Direction_t Data_Direction;

	struct
	{
		DMA_State 	Direct_Mode;
		DMA_State 	Transfer_Err;
		DMA_State 	HalfTransfer;
		DMA_State 	Transfer_Complete;

	}Interrupt;

}DMA_config_t;

/*
 * structure to initialize Channel criterial
 *
 * !! TO USE IN FUNCTION :: DMA_enuCritariaChannel
 *
 * */
typedef struct
{
	DMA_StreamId Stream;
	u32 Peripheral_Address;
	u32 Memory_0_Address;
	u32 Memory_1_Address;
	u16 Block_Length;
}Criteria_t;


/**************Function Declaration**********************/

/*
 * Function Name:	DMA_vidConfiguration
 *
 * Description:		To Configure DMA Channel
 *
 * Parameter:		ConfigPtr (Pointer) to DMA_config_t (User DataType)
 *
 * return:			ErrorStatus
 * 					in range {---DMA_enuNullPtr---}
 *
 * */
extern DMA_tenuErrorStatus DMA_enuConfiguration(DMA_ID DMA, const DMA_config_t* ConfigPtr);

/*
 * Function Name:	DMA_enuCritariaChannel
 *
 * Description:		To Configure the criteria Channel
 *						--> To initialize the source base address
 *						--> To initialize the destination base address
 *						--> to initialize the Block Length
 *
 * Parameter:		CriteriaPtr (Pointer) to Criteria_t (User DataType)
 *
 *
 * return:			ErrorStatus
 * 					in range {---DMA_enuNullPtr---}
 *
 * */
extern DMA_tenuErrorStatus DMA_enuCritariaChannel(DMA_ID DMA, const Criteria_t* CriteriaPtr);


/*
 * Function Name:	DMA_enuRegisterCallFunction
 *
 * Description:		To Initialize the Call Back Function
 *
 *
 * Parameter:		Channel --> in Range{ Channel0, Channel1, Channel2, Channel3, Channel4, Channel5, Channel6, Channel7 }
 * 					Cbf		--> Register the call back function
 *
 *
 * return:			ErrorStatus
 * 					in range {---DMA_enuNullPtr---}
 **/
extern DMA_tenuErrorStatus DMA_enuRegisterCallFunction(DMA_ID DMA, DMA_StreamId Stream, DMA_CallFunction Cbf);


/*
 * Function Name:	DMA_vidStreamState
 *
 * Description:		To open stream on DMA Channel
 *
 * 				!!!	THIS SHOULD BE SET AS LAST THING AFTER YOU FINISH CONFIGURATION
 * 					OR ALL YOUR WRITE WILL BE NEGLECTED --> IN CASE OF ENABLE
 *
 * 				!!! TO RECONFIGURE THE CHANNEL USER MUST SET THE STREAM TO OFF
 *
 *
 * Parameter:		Channel --> in Range{ Channel0, Channel1, Channel2, Channel3, Channel4, Channel5, Channel6, Channel7 }
 * 					Stream --> to configure the state
 *
 * return:			ErrorStatus
 * 					in range {--Variable undifined--}
 *
 * */
extern DMA_tenuErrorStatus DMA_enuStreamState(DMA_ID DMA, DMA_StreamId Stream, DMA_State Condition);



#endif /* DMA_H_ */
