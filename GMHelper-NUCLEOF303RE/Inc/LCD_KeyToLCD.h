/*
 * KeyboardToLCD.h
 *
 *  Created on: 12 maj 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_LCD_KEYTOLCD_H_
#define INC_LCD_KEYTOLCD_H_

#include <LCD_ST7735.h>
#include <Utility_ADCKeyboard.h>

struct
{
	uint8_t button_mem;
	char buff[10];
	int intbuff[10];
	uint8_t buff_length;
	uint8_t word_length;
}KeyToLCD_DATA;


void KeyToLCD_doit(uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);
void KeyToLCD_blink(uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor);
void KeyToLCD_buffor_clear();

#endif /* INC_LCD_KEYTOLCD_H_ */
