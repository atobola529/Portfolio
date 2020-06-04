/*
 * LEDRGB.h
 *
 *  Created on: May 10, 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_UTILITY_LEDRGB_H_
#define INC_UTILITY_LEDRGB_H_

#include "stm32f3xx_hal.h"

#define RGB_VALUE_MAX 255
#define HIGH 1
#define LOW 0
//-----------MACROS-----------
//---RGB FOR LED 1 ---
#define LED1_RED_H() 	HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, HIGH)
#define LED1_RED_L() 	HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, LOW)
#define LED1_GREEN_H() 	HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, HIGH)
#define LED1_GREEN_L() 	HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, LOW)
#define LED1_BLUE_H() 	HAL_GPIO_WritePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin, HIGH)
#define LED1_BLUE_L() 	HAL_GPIO_WritePin(RGB_BLUE_GPIO_Port, RGB_BLUE_Pin, LOW)
//---RGB FOR LED 2 ---
#define LED2_RED_H() 	HAL_GPIO_WritePin(RGB1_RED_GPIO_Port, RGB1_RED_Pin, HIGH)
#define LED2_RED_L() 	HAL_GPIO_WritePin(RGB1_RED_GPIO_Port, RGB1_RED_Pin, LOW)
#define LED2_GREEN_H() 	HAL_GPIO_WritePin(RGB1_GREEN_GPIO_Port, RGB1_GREEN_Pin, HIGH)
#define LED2_GREEN_L()	HAL_GPIO_WritePin(RGB1_GREEN_GPIO_Port, RGB1_GREEN_Pin, LOW)
#define LED2_BLUE_H()	HAL_GPIO_WritePin(RGB1_BLUE_GPIO_Port, RGB1_BLUE_Pin, HIGH)
#define LED2_BLUE_L() 	HAL_GPIO_WritePin(RGB1_BLUE_GPIO_Port, RGB1_BLUE_Pin, LOW)
//-----------ENUMS-----------
enum
{
	LED_TEAM1 = 1,
	LED_TEAM2 = 2
}LEDteam_TypeDef;

enum
{
	LED_RED,
	LED_BLUE,
	LED_GREEN,
	LED_ORANGE,
	LED_PURPLE,
	LED_CYAN,
	LED_YELLOW,
	LED_PINK,
	LED_DARK_RED,
	LED_DARK_BLUE,
	LED_DARK_ORANGE,
	LED_DARK_PURPLE,
	LED_WHITE
} LEDcolor_TypeDef;

//-----------FUNCTIONS-----------
void LEDRGB_pwm_tick_it();

void LEDRGB_SetColor(uint8_t RED, uint8_t GREEN, uint8_t BLUE, uint8_t which);
void LEDRGB_SetPredefinedColor(uint8_t color, uint8_t which);
void LEDRGB_GetPredefinedColor(uint8_t color, uint8_t *RED, uint8_t *GREEN, uint8_t *BLUE);

void LEDRGBon(uint8_t which);
void LEDRGBoff(uint8_t which);

#endif /* INC_UTILITY_LEDRGB_H_ */
