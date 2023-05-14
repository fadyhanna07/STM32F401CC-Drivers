/*******************************************/
/*LCD Driver
Target: ATMEGA32
Author :FADY
 Date:2023-03-29 */ 
/*******************************************/
#include "STD_TYPES.h"
#include "GPIO_int.h"
#include "LCD_Cfg.h"

const LCD_Operation_cfg_t LCD_Operation_cfg = {
    .backlight = Backlight_on,
    .blink = Blink_off,
    .font = Font_7,
    .mode = Mode_8bit,
    .numOfLines = Num_2_lines,
    .curser = Curser_off
};

const LCD_Pins_cfg_t LCD_Pins_cfg = {
    .RS = { GPIO_PORTB , 0 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},
    .ReadWrite = { GPIO_PORTB , 1 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},
    .Enable ={ GPIO_PORTB , 2 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},
    .Data = {
        [0] = { GPIO_PORTA , 0 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},  //D0
        [1] = { GPIO_PORTA , 1 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},  //D1
        [2] = { GPIO_PORTA , 2 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},  //D2
        [3] = { GPIO_PORTA , 3 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},  //D3
        [4] = { GPIO_PORTA , 4 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},  //D4
        [5] = { GPIO_PORTA , 5 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},  //D5
        [6] = { GPIO_PORTA , 6 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP},  //D6
        [7] = { GPIO_PORTA , 7 , GPIO_Speed_VeryHigh , GPIO_OUTPUT_PP}   //D7
        }
};
