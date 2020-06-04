/*
 * ADCKeyboard.c
 *
 *  Created on: 5 maj 2020
 *      Author: h4XX0rZ
 */

#include <Utility_ADCKeyboard.h>
#include "stm32f3xx_hal.h"

#define ADC_DELAY 5				//in ms  BUTTON PUSHED -> DELAY -> READ ADC

uint16_t ADC_Table[] =
{
		370, 220, 	//Button_Cancel || Max, Min value
		650, 450, 	//Button_OK
		900, 700, 	//Button_0
		1100, 960,	//Button_9
		1410, 1210, //Button_8
		1670, 1470,	//Button_7
		1950, 1750, //Button_6
		2240, 2040, //Button_5
		2540, 2340, //Button_4
		2880, 2650, //Button_3
		3200, 3000, //Button_2
		3600, 3400 	//Button_1
};

enum
{
	button_not_pushed = 0,
	button_pushed = 1,
	button_released = 2,
	button_pushed_idle = 3
}ButtonState_TypeDef;

struct
{
	uint8_t button_state;
	uint8_t ADCDelay;
	uint8_t start;
}ADCKeyboard_flags;

struct
{
	uint8_t Buttons;
	uint8_t ADCDelay;
	uint16_t ADC_value;
}ADCKeyboard_DATA;


void ADCKeyboard_Start()
{
	ADCKeyboard_flags.start = 1;
}

void ADCKeyboard_Stop()
{
	ADCKeyboard_flags.start = 0;
}

void ADCKeyboard_tick_it() //1kHz interrput
{
	switch(ADCKeyboard_flags.button_state)
	{
		case button_not_pushed:
		{
			if(GetADC_value() > ADC_Table[1]) ADCKeyboard_flags.button_state = button_pushed;
			break;
		}
		case button_pushed:
		{
			if(ADCKeyboard_DATA.ADCDelay >= ADC_DELAY)
				{
					ADCKeyboard_DATA.ADC_value = GetADC_value();
					ADCKeyboard_SetButton(ADCKeyboard_DATA.ADC_value);
					ADCKeyboard_flags.button_state = button_pushed_idle;
				}
			else {ADCKeyboard_DATA.ADCDelay++;}
			break;
		}
		case button_pushed_idle:
		{
			if(ADC_Table[1] >= GetADC_value()) ADCKeyboard_flags.button_state = button_released;
			break;
		}
		case button_released:
		{
			ADCKeyboard_DATA.ADCDelay = 0;
			ADCKeyboard_flags.ADCDelay = 0;
			ADCKeyboard_DATA.Buttons = Button_NONE;
			ADCKeyboard_flags.button_state = button_not_pushed;
			break;
		}
	}

}

void ADCKeyboard_GetButtonsState(uint8_t *ButtonState)
{

	switch(ADCKeyboard_DATA.Buttons)
	{
		case Button_0: *ButtonState =  Button_0; break;
		case Button_1: *ButtonState =  Button_1; break;
		case Button_2: *ButtonState =  Button_2; break;
		case Button_3: *ButtonState =  Button_3; break;
		case Button_4: *ButtonState =  Button_4; break;
		case Button_5: *ButtonState =  Button_5; break;
		case Button_6: *ButtonState =  Button_6; break;
		case Button_7: *ButtonState =  Button_7; break;
		case Button_8: *ButtonState =  Button_8; break;
		case Button_9: *ButtonState =  Button_9; break;
		case Button_OK: *ButtonState =  Button_OK; break;
		case Button_CANCEL: *ButtonState =  Button_CANCEL; break;
		case Button_NONE: *ButtonState =  Button_NONE; break;
		default: *ButtonState =  Button_NONE; break;
	}
}

void ADCKeyboard_SetButton(uint16_t ADC_value)
{
	if((ADC_Table[0] > ADC_value) && (ADC_value > ADC_Table[1])) ADCKeyboard_DATA.Buttons = Button_CANCEL;
	else if((ADC_Table[2] > ADC_value) && (ADC_value > ADC_Table[3])) ADCKeyboard_DATA.Buttons = Button_OK;
	else if((ADC_Table[4] > ADC_value) && (ADC_value > ADC_Table[5])) ADCKeyboard_DATA.Buttons = Button_0;
	else if((ADC_Table[6] > ADC_value) && (ADC_value > ADC_Table[7])) ADCKeyboard_DATA.Buttons = Button_9;
	else if((ADC_Table[8] > ADC_value) && (ADC_value > ADC_Table[9])) ADCKeyboard_DATA.Buttons = Button_8;
	else if((ADC_Table[10] > ADC_value) && (ADC_value > ADC_Table[11])) ADCKeyboard_DATA.Buttons = Button_7;
	else if((ADC_Table[12] > ADC_value) && (ADC_value > ADC_Table[13])) ADCKeyboard_DATA.Buttons = Button_6;
	else if((ADC_Table[14] > ADC_value) && (ADC_value > ADC_Table[15])) ADCKeyboard_DATA.Buttons = Button_5;
	else if((ADC_Table[16] > ADC_value) && (ADC_value > ADC_Table[17])) ADCKeyboard_DATA.Buttons = Button_4;
	else if((ADC_Table[18] > ADC_value) && (ADC_value > ADC_Table[19])) ADCKeyboard_DATA.Buttons = Button_3;
	else if((ADC_Table[20] > ADC_value) && (ADC_value > ADC_Table[21])) ADCKeyboard_DATA.Buttons = Button_2;
	else if((ADC_Table[22] > ADC_value) && (ADC_value > ADC_Table[23])) ADCKeyboard_DATA.Buttons = Button_1;
	else ADCKeyboard_DATA.Buttons = Button_NONE;
}

