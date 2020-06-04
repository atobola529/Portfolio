/*
 * h4XX1nG.h
 *
 *  Created on: May 4, 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_GAME_H4XX1NG_H_
#define INC_GAME_H4XX1NG_H_

#include <LCD_ST7735.h>
#include <Utility_Xtoa.h>
#include <Utility_RNG.h>

volatile uint32_t h4XX1nG_tick;
volatile uint32_t h4XX1nG_inprogress_flag;
volatile uint32_t h4XX1nG_flag;

void h4XX1nG_reboot();
void h4XX1nG_intro();
void h4XX1nG_menu();
void h4XX1nG_border();
void h4XX1nG_progress_bar(float bar_status);

void h4XX1nG_tick_service();
void h4XX1nG_tick_it();

void h4XX1nG_GetETA(uint8_t *HH, uint8_t *MM, uint8_t *SS);
void h4XX1nG_done();
uint8_t h4XX1nG_GetStatus();





#endif /* INC_GAME_H4XX1NG_H_ */
