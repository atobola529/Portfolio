/*
 * Janitor.c
 *
 *  Created on: May 6, 2020
 *      Author: h4XX0rZ
 */

#include <Game_Janitor.h>

uint8_t Janitor_KeyPlugged = 0;
uint8_t Janitor_KeyID = 21;
uint8_t Janitor_KeyChecked = 0;
uint8_t Janitor_Buttons;

uint16_t KeyADC_Table[] = {
		373, 173, 		// KEY 18  || MAX, MIN
		573, 374, 		// KEY 17  || MAX, MIN
		757, 557, 		// KEY 16  || MAX, MIN
		957, 757, 		// KEY 15  || MAX, MIN
		1130, 958,		// KEY 14  || MAX,MIN
		1336, 1136, 	// KEY 13  || MAX, MIN
		1536, 1337, 	// KEY 12  || MAX, MIN
		1745, 1545, 	// KEY 11  || MAX, MIN
		1891, 1750, 	// KEY 10  || MAX, MIN
		2155, 1955, 	// KEY 9  || MAX, MIN
		2395, 2195, 	// KEY 8 || MAX, MIN
		2605, 2405, 	// KEY 7 || MAX, MIN
		2814, 2614, 	// KEY 6 || MAX, MIN
		3009, 2810, 	// KEY 5 || MAX, MIN
		3210, 3010, 	// KEY 4 || MAX, MIN
		3415, 3215, 	// KEY 3 || MAX, MIN
		3614, 3414, 	// KEY 2 || MAX, MIN
		3828, 3628 	// KEY 1 || MAX, MIN
};

uint8_t Janitor_CheckIfKeyPlugged()
{
	return CheckKeySlot();
}

uint8_t Janitor_GetKeyID()
{
	return Janitor_KeyID;
}

void Janitor_CheckKey()
{
	uint16_t ADC_value;
	ADC_value = GetKeyADCValue();
	if((KeyADC_Table[0] > ADC_value) && (ADC_value > KeyADC_Table[1])) Janitor_KeyID = KEY_18;
	else if((KeyADC_Table[2] > ADC_value) && (ADC_value > KeyADC_Table[3])) Janitor_KeyID = KEY_17;
	else if((KeyADC_Table[4] > ADC_value) && (ADC_value > KeyADC_Table[5])) Janitor_KeyID = KEY_16;
	else if((KeyADC_Table[6] > ADC_value) && (ADC_value > KeyADC_Table[7])) Janitor_KeyID = KEY_15;
	else if((KeyADC_Table[8] > ADC_value) && (ADC_value > KeyADC_Table[9])) Janitor_KeyID = KEY_14;
	else if((KeyADC_Table[10] > ADC_value) && (ADC_value > KeyADC_Table[11])) Janitor_KeyID = KEY_13;
	else if((KeyADC_Table[12] > ADC_value) && (ADC_value > KeyADC_Table[13])) Janitor_KeyID = KEY_12;
	else if((KeyADC_Table[14] > ADC_value) && (ADC_value > KeyADC_Table[15])) Janitor_KeyID = KEY_11;
	else if((KeyADC_Table[16] > ADC_value) && (ADC_value > KeyADC_Table[17])) Janitor_KeyID = KEY_10;
	else if((KeyADC_Table[18] > ADC_value) && (ADC_value > KeyADC_Table[19])) Janitor_KeyID = KEY_9;
	else if((KeyADC_Table[20] > ADC_value) && (ADC_value > KeyADC_Table[21])) Janitor_KeyID = KEY_8;
	else if((KeyADC_Table[22] > ADC_value) && (ADC_value > KeyADC_Table[23])) Janitor_KeyID = KEY_7;
	else if((KeyADC_Table[24] > ADC_value) && (ADC_value > KeyADC_Table[25])) Janitor_KeyID = KEY_6;
	else if((KeyADC_Table[26] > ADC_value) && (ADC_value > KeyADC_Table[27])) Janitor_KeyID = KEY_5;
	else if((KeyADC_Table[28] > ADC_value) && (ADC_value > KeyADC_Table[29])) Janitor_KeyID = KEY_4;
	else if((KeyADC_Table[30] > ADC_value) && (ADC_value > KeyADC_Table[31])) Janitor_KeyID = KEY_3;
	else if((KeyADC_Table[32] > ADC_value) && (ADC_value > KeyADC_Table[33])) Janitor_KeyID = KEY_2;
	else if((KeyADC_Table[34] > ADC_value) && (ADC_value > KeyADC_Table[35])) Janitor_KeyID = KEY_1;
	else Janitor_KeyID = 21;
}
void Janitor_tick_it()
{
	if(CheckKeySlot() == 1)
		{
			//ADCKeyboard_GetButtonsState(&Janitor_Buttons);
			//if(Janitor_Buttons < Button_ANY)
			//{
				Janitor_CheckKey();
			//}
		}
	else Janitor_KeyID = 21;
}
