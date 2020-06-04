/*
 * Janitor.h
 *
 *  Created on: May 4, 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_GAME_JANITOR_H_
#define INC_GAME_JANITOR_H_

#include "MX_Initialize.h"
#include <Utility_ADCKeyboard.h>
#include <Utility_Xtoa.h>
#include "stm32f3xx_hal.h"

#define CheckKeySlot() HAL_GPIO_ReadPin(DigitalKey_GPIO_Port, DigitalKey_Pin)

#define StartADC() HAL_ADC_Start(&hadc4)
#define StopADC() HAL_ADC_Stop(&hadc4)
#define GetKeyADCValue() HAL_ADC_GetValue(&hadc4);

enum
{
	KEY_1 = 1,
	KEY_2 = 2,
	KEY_3 = 3,
	KEY_4 = 4,
	KEY_5 = 5,
	KEY_6 = 6,
	KEY_7 = 7,
	KEY_8 = 8,
	KEY_9 = 9,
	KEY_10 = 10,
	KEY_11 = 11,
	KEY_12 = 12,
	KEY_13 = 13,
	KEY_14 = 14,
	KEY_15 = 15,
	KEY_16 = 16,
	KEY_17 = 17,
	KEY_18 = 18
}KeysID_TypeDef;

uint8_t Janitor_CheckIfKeyPlugged();
uint8_t Janitor_GetKeyID();
void Janitor_CheckKey();
void Janitor_tick_it();

#endif /* INC_GAME_JANITOR_H_ */
