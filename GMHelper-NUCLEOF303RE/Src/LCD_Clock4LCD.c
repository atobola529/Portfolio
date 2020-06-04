/*
 * Clock4LCD.c
 *
 *  Created on: 4 maj 2020
 *      Author: h4XX0rZ
 */

#include <LCD_Clock4LCD.h>

void Clock4LCD_tick_increment(uint8_t *pHour, uint8_t *pMinute, uint8_t *pSecond)
{
	*pSecond+= 1;
	if(*pSecond == 60)
	{
		*pSecond = 0;
		*pMinute+= 1;
		if(*pMinute == 60)
		{
			*pMinute = 0;
			if(*pHour <99) pHour+= 1;
		}
	}
}

void Clock4LCD_tick_decrement(uint8_t *pHour, uint8_t *pMinute, uint8_t *pSecond)
{
	if(*pSecond > 0) *pSecond -= 1;
	else if(*pMinute > 0)
	{
		*pMinute -= 1;
		*pSecond = 59;
	}
	else if(*pHour > 0)
	{
		*pHour -= 1;
		*pMinute = 59;
		*pSecond = 59;
	}
}

char Clock4LCD_FormatCheck(uint8_t *pHour, uint8_t *pMinute, uint8_t  *pSecond)
{
	if((60 > *pSecond) && (*pSecond <=0))
	{
		if((60 > *pMinute) && (*pMinute <=0))
		{
			if((99 > *pHour) && (*pHour <=0))
			{
				return 1;
			}
		}
	}
	return 0;
}

