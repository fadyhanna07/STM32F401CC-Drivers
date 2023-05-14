#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_int.h"
#include "app3.h"


void Task3(void){
	GPIO_CFG_t pin_cgf2;
		pin_cgf2.Mode = GPIO_OUTPUT_PP;
		pin_cgf2.Speed = GPIO_Speed_VeryHigh;
		pin_cgf2.Port = GPIO_PORTA;
		pin_cgf2.Pin = 2;
    u8 error_status ;
    GPIO_Init(&pin_cgf2);
    u8 val = GPIO_GetPinValue(GPIO_PORTA,2,&error_status);
    GPIO_WritePinValue(GPIO_PORTA,2,(val ^ GPIO_PIN_HIGH));
}
