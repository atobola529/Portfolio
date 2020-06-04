/*
 * Bomb.h
 *
 *  Created on: May 8, 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_GAME_BOMB_H_
#define INC_GAME_BOMB_H_

#include "Game_Janitor.h"
#include "Game_h4XX1nG.h"
#include <LCD_Clock4LCD.h>
#include <LCD_KeyToLCD.h>
#include <LCD_ST7735.h>
#include <Utility_ADCKeyboard.h>
#include "Utility_Buzzer.h"
#include "Utility_RNG.h"


enum
{
	STANDARD,
	WITH_KEYS
}BombMode_TypeDef;

//---interrupt ticks---
void Bomb_tick_it();
void Bomb_blink_tick_it();
void Bomb_clock_tick_it();
void Bomb_tick_service();
//-------MENUS-------
void Bomb_Display_Menu();
void Bomb_Display_Menu_2();
void Bomb_Display_Info();
void Bomb_Display_Info_2();
//-------PIN-------
void Bomb_CheckPIN();
void Bomb_SetPIN();
void Bomb_ResetPIN();
//-------SETTINGS-------
void Bomb_Settings(uint8_t mode);
void Bomb_Settings_Menu();
void Bomb_Settings_Menu_2();
//-------TIME-------
uint8_t Bomb_TimeCheck();
void Bomb_SetTime(uint32_t HH, uint32_t MM, uint32_t SS);
void Bomb_DisplayTime(uint16_t X, uint16_t Y);
//-------OTHER-------
void Bomb_KeyID_shuffle();
void Bomb_Disarmed();
void Bomb_SetMode(uint8_t mode);
void Bomb_Start();
void Bomb_Stop();

#endif /* INC_GAME_BOMB_H_ */
