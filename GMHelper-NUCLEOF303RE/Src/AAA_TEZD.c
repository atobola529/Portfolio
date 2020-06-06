/*
 * AAA_TEZD.c
 *
 *  Created on: May 14, 2020
 *      Author: h4XX0rZ
 */

#include "AAA_TEZD.h"

uint8_t tone;

void DisplayPluggedKey()
{
	uint8_t key_id;
	key_id = Janitor_GetKeyID();
		switch(key_id)
		{
			case KEY_1: ST7735_PutStr5x7(55, 80, "Klucz 1 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_2: ST7735_PutStr5x7(55, 80, "Klucz 2 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_3: ST7735_PutStr5x7(55, 80, "Klucz 3 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_4: ST7735_PutStr5x7(55, 80, "Klucz 4 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_5: ST7735_PutStr5x7(55, 80, "Klucz 5 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_6: ST7735_PutStr5x7(55, 80, "Klucz 6 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_7: ST7735_PutStr5x7(55, 80, "Klucz 7 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_8: ST7735_PutStr5x7(55, 80, "Klucz 8 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_9: ST7735_PutStr5x7(55, 80, "Klucz 9 ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_10: ST7735_PutStr5x7(55, 80, "Klucz 10", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_11: ST7735_PutStr5x7(55, 80, "Klucz 11", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_12: ST7735_PutStr5x7(55, 80, "Klucz 12", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_13: ST7735_PutStr5x7(55, 80, "Klucz 13", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_14: ST7735_PutStr5x7(55, 80, "Klucz 14", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_15: ST7735_PutStr5x7(55, 80, "Klucz 15", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_16: ST7735_PutStr5x7(55, 80, "Klucz 16", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_17: ST7735_PutStr5x7(55, 80, "Klucz 17", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			case KEY_18: ST7735_PutStr5x7(55, 80, "Klucz 18", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
			default:  ST7735_PutStr5x7(55, 80, "Klucz ? ", COLOR565_ALICE_BLUE, COLOR565_BLACK); break;
		}
}

void BuzzerTonesTest()
{

}
