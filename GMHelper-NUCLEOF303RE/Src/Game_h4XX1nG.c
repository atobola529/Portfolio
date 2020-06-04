/*
 * h4XX1nG.c
 *
 *  Created on: 2 maj 2020
 *      Author: h4XX0rZ
 */

#include <Game_h4XX1nG.h>


uint32_t ETA_MAX;
uint32_t ETA;

uint8_t h4XX1nG_status;

void h4XX1nG_reboot()
{
	uint32_t i;

	h4XX1nG_status = 1;

	ST7735_Clear(COLOR565_WHITE);
	for(i=0;i<8;i++)
	{
		ST7735_PutStr5x7(5, 5, ">REBOOTING SYSTEM ", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
		ST7735_PutStr5x7(5, 5, ">REBOOTING SYSTEM_", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
	}
	for(i=0;i<8;i++)
	{
		ST7735_PutStr5x7(5, 15, ">INITIALIZING DRIVERS ", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
		ST7735_PutStr5x7(5, 15, ">INITIALIZING DRIVERS_", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
	}
	ST7735_PutStr5x7(5, 25, ">TRYING TO RECOVER", COLOR565_BLACK, COLOR565_WHITE);
	for(i=0;i<15;i++)
	{
		ST7735_PutStr5x7(5, 35, "CORRUPTED FILES.  ", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(200);
		ST7735_PutStr5x7(5, 35, "CORRUPTED FILES.. ", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(200);
		ST7735_PutStr5x7(5, 35, "CORRUPTED FILES...", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(200);
	}

	ST7735_PutStr5x7(5, 45, ">RECOVER FAILED", COLOR565_BLACK, COLOR565_WHITE);
	HAL_Delay(200);
	ST7735_PutStr5x7(5, 55, ">PROCEED WITH K1LL3M", COLOR565_BLACK, COLOR565_WHITE);
	for(i=0;i<12;i++)
	{
		ST7735_PutStr5x7(5, 65, "PROCEDURE.  ", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
		ST7735_PutStr5x7(5, 65, "PROCEDURE.. ", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
		ST7735_PutStr5x7(5, 65, "PROCEDURE...", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
	}

	ST7735_PutStr5x7(5, 75, ">FALIURE DUE TO", COLOR565_BLACK, COLOR565_WHITE);
	for(i=0;i<15;i++)
	{
		ST7735_PutStr5x7(5, 85, "UNKNOWN REASON ", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
		ST7735_PutStr5x7(5, 85, "UNKNOWN REASON_", COLOR565_BLACK, COLOR565_WHITE);
		HAL_Delay(300);
	}

	ST7735_PutStr5x7(5, 95, ">PROCESSOR HIJACKED", COLOR565_BLACK, COLOR565_WHITE);
	HAL_Delay(1000);
	ST7735_PutStr5x7(5, 105, ">RUN h4XX1nG.exe", COLOR565_BLACK, COLOR565_WHITE);
	HAL_Delay(2000);
	h4XX1nG_intro();
}
void h4XX1nG_intro()
{
	uint32_t i;

	ST7735_Clear(COLOR565_BLACK);
	ST7735_PutStr5x7(17, 70, "  U     H       :  ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 70, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(17, 55, "      T   X       )", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 55, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(17, 20, "Y    O      3      ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 20, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(17, 40, " O         X   >   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 40, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(17, 89, "    G    4   D     ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 89, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(17, 45, "Y U  T  H X     :  ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 45, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(17, 65, "YO   O     X3  >   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 65, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(17, 100, " OU G T H4 X D   :)", COLOR565_DARK_GREEN, COLOR565_BLACK);
	HAL_Delay(200);
	ST7735_PutStr5x7(17, 100, "                   ", COLOR565_DARK_GREEN, COLOR565_BLACK);
	for(i=0;i<10;i++)
	{
		ST7735_PutStr5x7(17, 64, "YOU GOT H4XX3D  >;)", COLOR565_DARK_GREEN, COLOR565_BLACK);
		HAL_Delay(200);
		ST7735_PutStr5x7(17, 64, "YOU GOT H4XX3D  >:)", COLOR565_DARK_GREEN, COLOR565_BLACK);
		HAL_Delay(200);
	}

}
void h4XX1nG_menu()
{
	ST7735_Clear(COLOR565_BLACK);
	h4XX1nG_border();
	ST7735_PutStr5x7(20, 20, "h4XX1n' 1n",COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(20, 30, "pr0gr355...",COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(20, 40, "g3t s0m3",COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(20, 50, "ch1ptun3 :3",COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(20, 70, "ETA:    s",COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(20, 90, "[          ]   %",COLOR565_DARK_GREEN, COLOR565_BLACK);
}

void h4XX1nG_border()
{
	uint32_t i;
	ST7735_Clear(COLOR565_BLACK);
	ST7735_PutStr5x7(10, 10, "*-*-*-*-*-*-*-*-*-*", COLOR565_DARK_GREEN, COLOR565_BLACK); //19 symbols
	for(i=17;i<119;i+=7)
	{
		ST7735_PutStr5x7(10, i, "|", COLOR565_DARK_GREEN, COLOR565_BLACK);
		ST7735_PutStr5x7(118, i, "|", COLOR565_DARK_GREEN, COLOR565_BLACK);
	}
	ST7735_PutStr5x7(10, 119, "*-*-*-*-*-*-*-*-*-*", COLOR565_DARK_GREEN, COLOR565_BLACK);
}


void h4XX1nG_progress_bar(float bar_status)
{

	if(bar_status == 100)ST7735_PutStr5x7(76, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
	else if(bar_status > 87)ST7735_PutStr5x7(69, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
	else if(bar_status > 75)ST7735_PutStr5x7(62, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
	else if(bar_status > 62)ST7735_PutStr5x7(55, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
	else if(bar_status > 50)ST7735_PutStr5x7(48, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
	else if(bar_status > 37)ST7735_PutStr5x7(41, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
	else if(bar_status > 25)ST7735_PutStr5x7(34, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
	else if(bar_status > 12) ST7735_PutStr5x7(27, 90, "#",COLOR565_DARK_GREEN, COLOR565_BLACK);
}


void h4XX1nG_tick_service()
{
	char buff[10];
	char *pbuff = &buff;
	float bar = 0;
	if(h4XX1nG_tick == 1)
	{
		ETA--;
		bar = 100 - (1.0*ETA/ETA_MAX)*100;
		if(ETA > 99) ST7735_PutStr5x7(48, 70, itoa(ETA, pbuff, 10) ,COLOR565_DARK_GREEN, COLOR565_BLACK);
		else if(ETA > 9)
		{
			ST7735_PutStr5x7(20, 70, "ETA:    s",COLOR565_DARK_GREEN, COLOR565_BLACK);
			ST7735_PutStr5x7(54, 70, itoa(ETA, pbuff, 10) ,COLOR565_DARK_GREEN, COLOR565_BLACK);

		}
		else
		{
			ST7735_PutStr5x7(20, 70, "ETA:    s",COLOR565_DARK_GREEN, COLOR565_BLACK);
			ST7735_PutStr5x7(62, 70, itoa(ETA, pbuff, 10) ,COLOR565_DARK_GREEN, COLOR565_BLACK);
		}

		h4XX1nG_progress_bar(bar);

		ST7735_PutStr5x7(90, 90, itoa(bar, pbuff, 10) ,COLOR565_DARK_GREEN, COLOR565_BLACK);
		h4XX1nG_tick = 0;
		if(bar == 100)
			{
				h4XX1nG_done();
			}
	}



}

void h4XX1nG_tick_it()
{
	if(ETA > 0)h4XX1nG_tick = 1;
}

void h4XX1nG_GetETA(uint8_t *HH, uint8_t *MM, uint8_t *SS)
{
	uint8_t Hour = *HH;
	uint8_t Minute = *MM;
	uint8_t Second = *SS;

	ETA = (Hour * 3600) + (Minute * 60) + Second;
	ETA = ETA/(1 + RNG_Random()%5);
	ETA_MAX = ETA;
}

void h4XX1nG_done()
{
	h4XX1nG_status = 0;
	ST7735_Clear(COLOR565_BLACK);
	h4XX1nG_border();
	ST7735_PutStr5x7(20, 20, "h4XX1n' 15",COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(20, 30, "d0n3 >:)",COLOR565_DARK_GREEN, COLOR565_BLACK);
	ST7735_PutStr5x7(20, 40, "Pr355 OK",COLOR565_DARK_GREEN, COLOR565_BLACK);
}

uint8_t h4XX1nG_GetStatus()
{
	return h4XX1nG_status;
}
