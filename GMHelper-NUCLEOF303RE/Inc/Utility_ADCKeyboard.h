/*
 * ADCKeyboard.h
 *
 *  Created on: 5 maj 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_UTILITY_ADCKEYBOARD_H_
#define INC_UTILITY_ADCKEYBOARD_H_

#include "MX_Initialize.h"

//-------READ ADC-------
#define GetADC_value() HAL_ADC_GetValue(&hadc3)

enum
{
	Button_0 = 0,
	Button_1 = 1,
	Button_2 = 2,
	Button_3 = 3,
	Button_4 = 4,
	Button_5 = 5,
	Button_6 = 6,
	Button_7 = 7,
	Button_8 = 8,
	Button_9 = 9,
	Button_OK = 10,
	Button_CANCEL = 11,
	Button_TEAM_1 = 12,
	Button_TEAM_2 = 13,
	Button_ANY = 14,
	Button_NONE = 20

}Buttons_TypeDef;

void ADCKeyboard_Start();
void ADCKeyboard_Stop();
void ADCKeyboard_tick_it();
void ADCKeyboard_GetButtonsState(uint8_t *ButtonState);
void ADCKeyboard_SetButton(uint16_t ADC_value);


#endif /* INC_UTILITY_ADCKEYBOARD_H_ */
