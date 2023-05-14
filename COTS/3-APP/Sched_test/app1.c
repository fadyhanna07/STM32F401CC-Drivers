#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_int.h"
#include "app1.h"


void Task1(void){
	GPIO_CFG_t pin_cgf;
		pin_cgf.Mode = GPIO_OUTPUT_PP;
		pin_cgf.Speed = GPIO_Speed_VeryHigh;
		pin_cgf.Port = GPIO_PORTA;
		pin_cgf.Pin = 0;
    u8 error_status ;
    GPIO_Init(&pin_cgf);
    u8 val = GPIO_GetPinValue(GPIO_PORTA,0,&error_status);
    GPIO_WritePinValue(GPIO_PORTA,0,(val ^ GPIO_PIN_HIGH));
}
