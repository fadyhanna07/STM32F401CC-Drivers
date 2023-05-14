#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_int.h"
#include "app2.h"


void Task2(void){
	GPIO_CFG_t pin_cgf1;
		pin_cgf1.Mode = GPIO_OUTPUT_PP;
		pin_cgf1.Speed = GPIO_Speed_VeryHigh;
		pin_cgf1.Port = GPIO_PORTA;
		pin_cgf1.Pin = 1;
u8 error_status ;
    GPIO_Init(&pin_cgf1);
    u8 val = GPIO_GetPinValue(GPIO_PORTA,1,&error_status);
    GPIO_WritePinValue(GPIO_PORTA,1,(val ^ GPIO_PIN_HIGH));
}
