/*
 * LEDRGB.c
 *
 *  Created on: May 10, 2020
 *      Author: h4XX0rZ
 */

#include <Utility_LEDRGB.h>
#include "MX_Initialize.h"



uint8_t LEDRGB_pwm_tick_flag = 0;
uint8_t LEDRGB_tick_flag = 0;
uint16_t LEDRGB_pwm_tick_counter = 0;

struct
{
	uint8_t Color_RED;
	uint8_t Color_BLUE;
	uint8_t Color_GREEN;
	uint8_t ONoff;
}LED1, LED2;


void LEDRGB_pwm_tick_it()
{
	if(LED1.ONoff == 1 || LED2.ONoff == 1)
	{
		if(LEDRGB_pwm_tick_counter++ >= RGB_VALUE_MAX)
					{
						if(LED1.ONoff == 1)
						{
							LED1_RED_H();
							LED1_GREEN_H();
							LED1_BLUE_H();
						}
						if(LED2.ONoff == 1)
						{
							LED2_RED_H();
							LED2_GREEN_H();
							LED2_BLUE_H();
						}
						LEDRGB_pwm_tick_counter = 0;
					}
					if(LED1.ONoff == 1)
					{
						if(LEDRGB_pwm_tick_counter >= LED1.Color_RED) LED1_RED_L();
						if(LEDRGB_pwm_tick_counter >= LED1.Color_GREEN) LED1_GREEN_L();
						if(LEDRGB_pwm_tick_counter >= LED1.Color_BLUE) LED1_BLUE_L();
					}
					else
					{
						LED1_RED_L();
						LED1_GREEN_L();
						LED1_BLUE_L();
					}
					if(LED2.ONoff == 1)
					{
						if(LEDRGB_pwm_tick_counter >= LED2.Color_RED) LED2_RED_L();
						if(LEDRGB_pwm_tick_counter >= LED2.Color_GREEN) LED2_GREEN_L();
						if(LEDRGB_pwm_tick_counter >= LED2.Color_BLUE) LED2_BLUE_L();
					}
					else
					{
						LED2_RED_L();
						LED2_GREEN_L();
						LED2_BLUE_L();
					}

	}

}

void LEDRGB_SetColor(uint8_t RED, uint8_t GREEN, uint8_t BLUE, uint8_t which)
{
	switch(which)
	{
		case 1:
			{
				LED1.Color_RED = RED;
				LED1.Color_GREEN = GREEN;
				LED1.Color_BLUE = BLUE;
				break;
			}
		case 2:
			{
				LED2.Color_RED = RED;
				LED2.Color_GREEN = GREEN;
				LED2.Color_BLUE = BLUE;
				break;
			}
		default: break;
	}
}

void LEDRGB_SetPredefinedColor(uint8_t color, uint8_t which)
{
	switch(color)
	{
		case LED_RED: 		LEDRGB_SetColor(255, 0, 0, which); break;
		case LED_BLUE: 		LEDRGB_SetColor(0, 0, 255, which); break;
		case LED_GREEN:		LEDRGB_SetColor(0, 255, 0, which); break;
		case LED_ORANGE:	LEDRGB_SetColor(255, 128, 0, which); break;
		case LED_PURPLE:	LEDRGB_SetColor(128, 0, 255, which); break;
		case LED_CYAN:		LEDRGB_SetColor(0, 255, 255, which); break;
		case LED_YELLOW:	LEDRGB_SetColor(255, 255, 0, which); break;
		case LED_PINK:		LEDRGB_SetColor(255, 0, 255, which); break;
		case LED_DARK_RED:	LEDRGB_SetColor(204, 0, 0, which); break;
		case LED_DARK_BLUE:	LEDRGB_SetColor(0, 0, 204, which); break;
		case LED_DARK_ORANGE:LEDRGB_SetColor(153, 76, 0, which); break;
		case LED_DARK_PURPLE:LEDRGB_SetColor(76, 0, 153, which); break;
		case LED_WHITE:		LEDRGB_SetColor(128, 128, 128, which); break;
		default: break;
	}
}

void LEDRGB_GetPredefinedColor(uint8_t color, uint8_t *RED, uint8_t *GREEN, uint8_t *BLUE)
{
	switch(color)
		{
			case LED_RED:
				{
					*RED = 255;
					*GREEN = 0;
					*BLUE = 0;
					break;
				}
			case LED_BLUE:
				{
					*RED = 0;
					*GREEN = 0;
					*BLUE = 255;
					break;
				}
			case LED_GREEN:
				{
					*RED = 0;
					*GREEN = 255;
					*BLUE = 0;
					break;
				}
			case LED_ORANGE:
				{
					*RED = 255;
					*GREEN = 128;
					*BLUE = 0;
					break;
				}
			case LED_PURPLE:
				{
					*RED = 128;
					*GREEN = 0;
					*BLUE = 255;
					break;
				}
			case LED_CYAN:
				{
					*RED = 0;
					*GREEN = 255;
					*BLUE = 255;
					break;
				}
			case LED_YELLOW:
				{
					*RED = 255;
					*GREEN = 255;
					*BLUE = 0;
					break;
				}
			case LED_PINK:
				{
					*RED = 255;
					*GREEN = 0;
					*BLUE = 255;
					break;
				}
			case LED_DARK_RED:
				{
					*RED = 204;
					*GREEN = 0;
					*BLUE = 0;
					break;
				}
			case LED_DARK_BLUE:
				{
					*RED = 204;
					*GREEN = 0;
					*BLUE = 0;
					break;
				}
			case LED_DARK_ORANGE:
				{
					*RED = 153;
					*GREEN = 76;
					*BLUE = 0;
					break;
				}
			case LED_DARK_PURPLE:
				{
					*RED = 76;
					*GREEN = 0;
					*BLUE = 153;
					break;
				}
			case LED_WHITE:
				{
					*RED = 128;
					*GREEN = 128;
					*BLUE = 128;
					break;
				}
			default: break;
		}
}

void LEDRGBon(uint8_t which)
{
	switch(which)
	{
		case 1: LED1.ONoff = 1; break;
		case 2: LED2.ONoff = 1; break;
		default: break;
	}
}

void LEDRGBoff(uint8_t which)
{
	switch(which)
	{
		case 1: LED1.ONoff = 0; break;
		case 2: LED2.ONoff = 0; break;
		default: break;
	}
}
