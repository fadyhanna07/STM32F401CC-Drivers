/*******************************************/
/*LCD Driver
Target: ATMEGA32
Author :FADY
 Date:2023-03-29 */ 
/*******************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_int.h"
#include "LCD_Cfg.h"
#include "LCD_int.h"
/*********************************  types  *******************************************************************************/

/********************************* Global Variables  *******************************************************************************/
LCD_status_t LCD_status = LCD_Idle ;
char * Data_Buffer = NULL;
u8 Init_done = 0;
u8 char_idx = 0 ;
User_Req_t User_Req ;
/********************************* Static Functions   *******************************************************************************/
static LCD_tenuErrorStatus LCD_enuWriteData(){
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
    if(Data_Buffer[char_idx] != '\0' && User_Req == Req_Write){
    /*Send disable pulse*/
    GPIO_WritePinValue(LCD_Pins_cfg.Enable.Port,LCD_Pins_cfg.Enable.Pin,GPIO_PIN_LOW);
    /*Set RS pin to high for data*/
    GPIO_WritePinValue(LCD_Pins_cfg.RS.Port,LCD_Pins_cfg.RS.Pin,GPIO_PIN_HIGH);
    /*Set RW pin to low for write*/
    GPIO_WritePinValue(LCD_Pins_cfg.ReadWrite.Port,LCD_Pins_cfg.ReadWrite.Pin,GPIO_PIN_LOW);
    /*Set Data to data pins*/
    for (u8 i = 0; i < 8; i++)
    {
        GPIO_WritePinValue(LCD_Pins_cfg.Data[i].Port,LCD_Pins_cfg.Data[i].Pin,GET_BIT(Data_Buffer[char_idx],i));
    }
    /*Send enable pulse*/
    GPIO_WritePinValue(LCD_Pins_cfg.Enable.Port,LCD_Pins_cfg.Enable.Pin,GPIO_PIN_HIGH);
    char_idx++;
    }
    else if (Data_Buffer[char_idx] == '\0')
    {
        /*Send disable pulse*/
        GPIO_WritePinValue(LCD_Pins_cfg.Enable.Port,LCD_Pins_cfg.Enable.Pin,GPIO_PIN_LOW);
        LCD_status = LCD_Idle ;
        User_Req = Req_NoREq;

    }
    else{/*  */}
    return Loc_enuErrorStatus;
}

/**********************************************************************************************/

static LCD_tenuErrorStatus LCD_enuSendCommand(u8 command){
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
    /*Send disable pulse*/
    GPIO_WritePinValue(LCD_Pins_cfg.Enable.Port,LCD_Pins_cfg.Enable.Pin,GPIO_PIN_LOW);
    /*Set RS pin to low for command*/
    GPIO_WritePinValue(LCD_Pins_cfg.RS.Port,LCD_Pins_cfg.RS.Pin,GPIO_PIN_LOW);
    /*Set RW pin to low for write*/
    GPIO_WritePinValue(LCD_Pins_cfg.ReadWrite.Port,LCD_Pins_cfg.ReadWrite.Pin,GPIO_PIN_LOW);
    /*Set Command to data pins*/
    for (u8 i = 0; i < 8; i++)
    {
        GPIO_WritePinValue(LCD_Pins_cfg.Data[i].Port,LCD_Pins_cfg.Data[i].Pin,GET_BIT(command,i));
    }
    /*Send enable pulse*/
    GPIO_WritePinValue(LCD_Pins_cfg.Enable.Port,LCD_Pins_cfg.Enable.Pin,GPIO_PIN_HIGH);
    return Loc_enuErrorStatus;
}
/**********************************************************************************************/
static LCD_tenuErrorStatus LCD_enuClaerDisplay(u8 command){
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
    LCD_enuSendCommand(command);
    LCD_status = LCD_Idle;
    return Loc_enuErrorStatus;
}
/*********************************  Functions Implementation  *******************************************************************************/
LCD_tenuErrorStatus LCD_enuInit()
{
	LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
    u8 temp_command = 0;
    static u8 init_state = 0;
    switch (init_state)
    {
    case 0:

    	    GPIO_Init(&LCD_Pins_cfg.Enable);
    	    GPIO_Init(&LCD_Pins_cfg.RS);
    	    GPIO_Init(&LCD_Pins_cfg.ReadWrite);
    	    for (u8 i = 0; i < 8; i++)
    	       {
    	    	GPIO_Init(&LCD_Pins_cfg.Data[i]);
    	       }
    	//Function set command: mode (bit 4), num of lines (bit 3) and font size (bit 2)
    temp_command |= (LCD_Operation_cfg.font << 2) | (LCD_Operation_cfg.numOfLines << 3) | (LCD_Operation_cfg.mode << 4) |(1<<5);
    LCD_enuSendCommand(temp_command);
    init_state++;
        break;
    case 1:             ///*Display on off control: (display) enable (bit 2), (disable) cursor (bit 1), (no) blink cursor (bit 0)*/
        temp_command |= (LCD_Operation_cfg.blink << 0) | (LCD_Operation_cfg.curser << 1) | 12;
        LCD_enuSendCommand(temp_command);
        init_state++;
        break;
    case 2:             //clear display
        LCD_enuSendCommand(1);
        init_state++;
        break;    
    case 3:             //init done
        Init_done = 1;
        break;
    }
    return Loc_enuErrorStatus;
}

/**************************************************************************************/
LCD_tenuErrorStatus LCD_enuGoToXY(u8 pos_x ,u8 pos_y )
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
    u8 temp_command = 0;
    if(pos_x == 0)
    {
        temp_command = pos_y;
    }
    else if (pos_x == 1)
    {
        temp_command = pos_y + 0x40;
    }
    else{ Loc_enuErrorStatus = LCD_enuNOTOK;}
    LCD_enuSendCommand(temp_command + 128);
     return Loc_enuErrorStatus;
}
/****************************************************************************************/
LCD_tenuErrorStatus LCD_enuWriteStringAsync(char * str )
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
    if(str == NULL)
    {
        Loc_enuErrorStatus = LCD_enuNULLPOINTER;
    }
   else if(LCD_status == LCD_Busy)
    {
        Loc_enuErrorStatus = LCD_enuBusy;
    }
    else if (LCD_status == LCD_Idle)
    {
    	char_idx =0;
        LCD_status = LCD_Busy;
       // LCD_enuSendCommand(1);
        Data_Buffer = str;
        User_Req = Req_Write;
    }
    else{}
    return Loc_enuErrorStatus;
}
/*************************************************************************************************/
LCD_tenuErrorStatus LCD_enuClearDisplayAsync()
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
    if(LCD_status == LCD_Busy)
    {
        Loc_enuErrorStatus = LCD_enuBusy;
    }
     else if (LCD_status == LCD_Idle)
    {
        LCD_status = LCD_Busy;
        User_Req = Req_Clear;
    }
    else{}
    return Loc_enuErrorStatus;

}
/********************************************************************************************/
void LCD_Task(void){
    if(Init_done != 1)
    {
        LCD_enuInit();
    }
    else if (User_Req == Req_Write)
    {
        LCD_enuWriteData();
    }
    else if (User_Req == Req_Clear)
    {
        LCD_enuClaerDisplay(1);
    }
    else{/* */}
}
