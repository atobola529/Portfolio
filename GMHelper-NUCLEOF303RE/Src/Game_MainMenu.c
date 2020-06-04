/*
 * MainMenu.c
 *
 *  Created on: 4 maj 2020
 *      Author: h4XX0rZ
 */

#include <Game_MainMenu.h>

uint8_t Game = 0;
uint8_t settings_block = 0;

void MainMenu_service()
{
	uint8_t buttons;
	uint8_t *pbuttons = &buttons;
	ADCKeyboard_GetButtonsState(pbuttons);

	if(settings_block == 1)
	{
			if(buttons == Button_NONE) settings_block = 0;
	}

	switch(Game)
	{
		case 0:
		{
			switch(buttons)
				{
					case Button_1:
					{
						PointCapture_ModeSelect(1);
						Game = 1;
						PointCapture_Settings();
						break;
					}
					case Button_2:
					{
						PointCapture_ModeSelect(2);
						Game = 2;
						PointCapture_Settings();
						break;
					}
					case Button_3:
					{
						Bomb_Settings(STANDARD);
						Game = 3;
						break;
					}
					case Button_4:
					{
						Bomb_Settings(WITH_KEYS);
						Game = 4;
						break;
					}
					default: Game = 0; break;
				}
		}
		case 1:
		{
			PointCapture_tick_service();
			PointCapture_Mode1_service();
			break;
		}
		case 2:
		{
			PointCapture_tick_service();
			PointCapture_Mode2_service();
			break;
		}
		case 3:
		{
			Bomb_tick_service();
			break;
		}
		case 4:
		{
			Bomb_tick_service();
			h4XX1nG_tick_service();
			break;
		}
	}
}

void MainMenu_Display()
{
	ST7735_Clear(COLOR565_BLACK);
	ST7735_PutStr5x7(10, 10, "Wybierz tryb:", COLOR565_KHAKI, COLOR565_BLACK);
	ST7735_PutStr5x7(10, 20, "1.PointCtrl v1", COLOR565_KHAKI, COLOR565_BLACK);
	ST7735_PutStr5x7(10, 30, "2.PointCtrl v2", COLOR565_KHAKI, COLOR565_BLACK);
	ST7735_PutStr5x7(10, 40, "3.Bomba", COLOR565_KHAKI, COLOR565_BLACK);
	ST7735_PutStr5x7(10, 50, "4.Bomba z kluczami", COLOR565_KHAKI, COLOR565_BLACK);
	ST7735_PutStr5x7(10, 60, "X.TagCollector", COLOR565_KHAKI, COLOR565_BLACK);
	ST7735_PutStr5x7(10, 70, "X.???????", COLOR565_KHAKI, COLOR565_BLACK);
	ST7735_PutStr5x7(60, 100, "by Kebab :)", COLOR565_KHAKI, COLOR565_BLACK);
}

