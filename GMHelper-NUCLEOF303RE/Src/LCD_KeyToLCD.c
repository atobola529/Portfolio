/*
 * KeyToLCD_DATA.c
 *
 *  Created on: 12 maj 2020
 *      Author: h4XX0rZ
 */

#include <LCD_KeyToLCD.h>

uint8_t blink_swapper = 0;


void KeyToLCD_doit(uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor)
{
	uint8_t button;
	uint8_t *pbutton = &button;
	ADCKeyboard_GetButtonsState(pbutton);

		if(button != KeyToLCD_DATA.button_mem)
		{
			switch(button)
			{
				case Button_0: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x30; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 0; break;
				case Button_1: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x31; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 1; break;
				case Button_2: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x32; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 2; break;
				case Button_3: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x33; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 3; break;
				case Button_4: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x34; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 4; break;
				case Button_5: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x35; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 5; break;
				case Button_6: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x36; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 6; break;
				case Button_7: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x37; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 7; break;
				case Button_8: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x38; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 8; break;
				case Button_9: KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x39; KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length++] = 9; break;
				case Button_CANCEL:
					{
						if(KeyToLCD_DATA.buff_length == 0)
						{
							KeyToLCD_DATA.buff_length = KeyToLCD_DATA.word_length;
							KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length] = 0x20;
							KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length] = NULL;
						}
						else
						{
							KeyToLCD_DATA.buff[--KeyToLCD_DATA.buff_length] = 0x20;
							KeyToLCD_DATA.intbuff[KeyToLCD_DATA.buff_length] = NULL;
						}
						break;
					}
				default: break;
			}
		ST7735_PutStr5x7(X, Y, KeyToLCD_DATA.buff, color, bgcolor);
		KeyToLCD_DATA.button_mem = button;
		if(KeyToLCD_DATA.buff_length > KeyToLCD_DATA.word_length) KeyToLCD_DATA.buff_length = 0;
		}
}


void KeyToLCD_blink(uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor)
{
	uint16_t a;

	a = 6 * KeyToLCD_DATA.buff_length;
	if(blink_swapper == 1) ST7735_PutChar5x7(X+a, Y, 0x20,COLOR565_WHITE, COLOR565_BLACK);
	else ST7735_PutChar5x7(X+a, Y, KeyToLCD_DATA.buff[KeyToLCD_DATA.buff_length], color, bgcolor);
	blink_swapper ^= 1;
}

void KeyToLCD_buffor_clear()
{
	uint8_t i;
	for(i=0;i<9;i++) KeyToLCD_DATA.buff[i] = 0x20;
	KeyToLCD_DATA.buff_length = 0;
}
