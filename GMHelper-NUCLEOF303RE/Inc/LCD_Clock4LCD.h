/*
 * Clock4LCD.h
 *
 *  Created on: 4 maj 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_LCD_CLOCK4LCD_H_
#define INC_LCD_CLOCK4LCD_H_

#include "stm32f3xx_hal.h"

void Clock4LCD_tick_increment(uint8_t *pHour, uint8_t *pMinute, uint8_t *pSecond);
void Clock4LCD_tick_decrement(uint8_t *pHour, uint8_t *pMinute, uint8_t *pSecond);
char Clock4LCD_FormatCheck(uint8_t *pHour, uint8_t *pMinute, uint8_t *pSecond);

#endif /* INC_LCD_CLOCK4LCD_H_ */
