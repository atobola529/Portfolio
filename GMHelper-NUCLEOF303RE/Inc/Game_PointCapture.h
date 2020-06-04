/*
 * PointCapture.h
 *
 *  Created on: 4 maj 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_GAME_POINTCAPTURE_H_
#define INC_GAME_POINTCAPTURE_H_

#include <LCD_Clock4LCD.h>
#include <LCD_KeyToLCD.h>
#include <LCD_ST7735.h>
#include <Utility_LEDRGB.h>
#include <Utility_Xtoa.h>
#include <Utility_ADCKeyboard.h>

#define HIGH 1
#define LOW 0

typedef enum
{
	TIME_GLOBAL = 0,
	TIME_TEAM1 = 1,
	TIME_TEAM2 = 2

}TimeID_TypeDef;

typedef enum
{
	TEAM1 = 1,
	TEAM2 = 2
}TeamID_Typedef;

void PointCapture_tick_it();
void PointCapture_clock_it();
void PointCapture_tick_blink_it();
void PointCapture_tick_service();

void PointCapture_Mode1_Menu();
void PointCapture_Mode1_service();
void PointCapture_Mode1_DisplayInfo();
void PointCapture_Mode1_EndOfGame();
void PointCapture_Mode2_Menu();
void PointCapture_Mode2_service();
void PointCapture_Mode2_DisplayInfo();
void PointCapture_Mode2_EndOfGame();

void PointCapture_Settings();
void PointCapture_Settings_Menu_1();
void PointCapture_Settings_Menu_2();
void PointCapture_Settings_Menu_3();
void PointCapture_Settings_Menu_4();

void PointCapture_TeamInControl_LED();
void PointCapture_DominatingTeam_Choose();
void PointCapture_DisplayTime(uint16_t X, uint16_t Y, TimeID_TypeDef which_time);
void PointCapture_SetTime(uint8_t HH, uint8_t MM, uint8_t SS);
void PointCapture_ModeSelect(uint8_t MODE);
void PointCapture_StartGame();

#endif /* INC_GAME_POINTCAPTURE_H_ */
