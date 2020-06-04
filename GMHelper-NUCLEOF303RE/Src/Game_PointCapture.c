/*
 * PointCapture.c
 *
 *  Created on: 4 maj 2020
 *      Author: h4XX0rZ
 */

#include <Game_PointCapture.h>

//---------ENUMS---------
enum
{
	step1 = 1,
	step2 = 2,
	step3 = 3,
	step4 = 4,
	step5 = 5,
	step6 = 6,
	step7 = 7,
	step8 = 8
}Setting_steps;
//---------FLAGS---------
struct
{
	uint8_t tick;
	uint8_t blink_tick;
	uint8_t clock_tick;
	uint8_t settings;
	uint8_t GameIsON;
}PC_flags;

//---------GLOBAL---------
struct
{
	uint8_t time_HH;
	uint8_t time_MM;
	uint8_t time_SS;
	uint8_t DominatingTeam;
	uint8_t TeamInControlOfPoint;
	uint8_t mode;
	uint8_t buttons;
} PC_DATA;

//---------TEAMS---------
struct
{
	uint8_t time_HH;
	uint8_t time_MM;
	uint8_t time_SS;
	//uint8_t color_R; //for user defined color with RGB (255,255,255) input || might be implemented with BT and android app feature
	//uint8_t color_G;
	//uint8_t color_B;
	uint8_t predef_color;
	char *Name;

}PC_DATA_team1, PC_DATA_team2;


void PointCapture_tick_it()
{
	PC_flags.tick = 1;
}

void PointCapture_clock_it()
{
	PC_flags.clock_tick = 1;
}

void PointCapture_tick_blink_it()
{
	PC_flags.blink_tick = 1;
}

void PointCapture_tick_service()
{
	if(PC_flags.clock_tick == 1)
	{
		if(PC_flags.GameIsON == 1)
		{
			if(PC_DATA.mode == 1)
			{
				switch(PC_DATA.TeamInControlOfPoint)
					{
						case 0:
						{
							break;
						}
						case 1:
						{
							Clock4LCD_tick_decrement(&PC_DATA.time_HH, &PC_DATA.time_MM, &PC_DATA.time_SS);
							Clock4LCD_tick_increment(&PC_DATA_team1.time_HH, &PC_DATA_team1.time_MM, &PC_DATA_team1.time_SS);
							break;
						}
						case 2:
						{
							Clock4LCD_tick_decrement(&PC_DATA.time_HH, &PC_DATA.time_MM, &PC_DATA.time_SS);
							Clock4LCD_tick_increment(&PC_DATA_team2.time_HH, &PC_DATA_team2.time_MM, &PC_DATA_team2.time_SS);
							break;
						}
						default:
						{
							ST7735_PutStr5x7(5, 5, "ERROR: PointCapture_Mode1 WRONG DOMINATING TEAM",COLOR565_WHITE ,COLOR565_INDIAN_RED); break;
						}
					}
				PointCapture_DisplayTime(49,15,TIME_GLOBAL);
			}
			else if(PC_DATA.mode == 2)
			{
				switch(PC_DATA.TeamInControlOfPoint)
					{
						case 0:
						{
							break;
						}
						case 1:
						{
							Clock4LCD_tick_increment(&PC_DATA_team1.time_HH, &PC_DATA_team1.time_MM, &PC_DATA_team1.time_SS);
							PointCapture_DisplayTime(70,55,TIME_TEAM1);
							break;
						}
						case 2:
						{
							Clock4LCD_tick_increment(&PC_DATA_team2.time_HH, &PC_DATA_team2.time_MM, &PC_DATA_team2.time_SS);
							PointCapture_DisplayTime(70,80,TIME_TEAM2);
							break;
						}
						default:
						{
							ST7735_PutStr5x7(5, 5, "ERROR: PointCapture_Mode2 WRONG DOMINATING TEAM",COLOR565_WHITE ,COLOR565_INDIAN_RED); break;
						}
					}
			}
		}
			PC_flags.clock_tick = 0;
	}
	if(PC_flags.tick == 1)
	{
		if(PC_flags.settings != 0)
		{
			ADCKeyboard_GetButtonsState(&PC_DATA.buttons);
			switch(PC_flags.settings)
			{
				case step1:
				{
					PointCapture_Settings_Menu_1();
					PC_flags.settings++;
					KeyToLCD_DATA.word_length = 5;
					break;
				}
				case step2:
				{
					KeyToLCD_doit(46, 20, COLOR565_WHITE ,COLOR565_INDIAN_RED);
					if(PC_DATA.buttons == Button_OK)
					{
						PointCapture_SetTime(10 * KeyToLCD_DATA.intbuff[0] + KeyToLCD_DATA.intbuff[1], 10 * KeyToLCD_DATA.intbuff[2] + KeyToLCD_DATA.intbuff[3], 10 * KeyToLCD_DATA.intbuff[4] + KeyToLCD_DATA.intbuff[5]);
						PC_flags.settings++;
					}
					break;
				}
				case step3:
				{
					PointCapture_Settings_Menu_2();
					PC_flags.settings++;
					break;
				}
				case step4:
				{
					switch(PC_DATA.buttons)
					{
						case Button_1: PC_DATA_team1.Name = "Czerwoni "; LEDRGB_SetPredefinedColor(LED_RED, TEAM1); PC_DATA_team1.predef_color = LED_RED; PC_flags.settings++; break;
						case Button_2: PC_DATA_team1.Name = "Niebiescy"; LEDRGB_SetPredefinedColor(LED_BLUE, TEAM1); PC_DATA_team1.predef_color = LED_BLUE; PC_flags.settings++; break;
						case Button_3: PC_DATA_team1.Name = "Zieloni  "; LEDRGB_SetPredefinedColor(LED_GREEN, TEAM1); PC_DATA_team1.predef_color = LED_GREEN; PC_flags.settings++; break;
						case Button_4: PC_DATA_team1.Name = "Pomarancz"; LEDRGB_SetPredefinedColor(LED_DARK_ORANGE, TEAM1); PC_DATA_team1.predef_color = LED_DARK_ORANGE; PC_flags.settings++; break;
						case Button_5: PC_DATA_team1.Name = "Zolci    "; LEDRGB_SetPredefinedColor(LED_YELLOW, TEAM1); PC_DATA_team1.predef_color = LED_YELLOW; PC_flags.settings++; break;
						case Button_6: PC_DATA_team1.Name = "Rozowi   "; LEDRGB_SetPredefinedColor(LED_PINK, TEAM1); PC_DATA_team1.predef_color = LED_PINK; PC_flags.settings++; break;
						case Button_7: PC_DATA_team1.Name = "Bez tasm "; LEDRGB_SetPredefinedColor(LED_WHITE, TEAM1); PC_DATA_team1.predef_color = LED_WHITE; PC_flags.settings++; break;
						case Button_CANCEL: PC_flags.settings = step1; break;
						default: break;
					}
					break;
				}
				case step5:
				{
					PointCapture_Settings_Menu_3();
					LEDRGBon(TEAM1);
					PC_DATA_team2.predef_color = 100;
					PC_flags.settings++;
					break;
				}
				case step6:
				{
					switch(PC_DATA.buttons)
					{
						case Button_1: PC_DATA_team2.Name = "Czerwoni "; LEDRGB_SetPredefinedColor(LED_RED, TEAM2); PC_DATA_team2.predef_color = LED_RED; break;
						case Button_2: PC_DATA_team2.Name = "Niebiescy"; LEDRGB_SetPredefinedColor(LED_BLUE, TEAM2); PC_DATA_team2.predef_color = LED_BLUE; break;
						case Button_3: PC_DATA_team2.Name = "Zieloni  "; LEDRGB_SetPredefinedColor(LED_GREEN, TEAM2); PC_DATA_team2.predef_color = LED_GREEN; break;
						case Button_4: PC_DATA_team2.Name = "Pomarancz"; LEDRGB_SetPredefinedColor(LED_DARK_ORANGE, TEAM2); PC_DATA_team2.predef_color = LED_DARK_ORANGE;  break;
						case Button_5: PC_DATA_team2.Name = "Zolci    "; LEDRGB_SetPredefinedColor(LED_YELLOW, TEAM2); PC_DATA_team2.predef_color = LED_YELLOW; break;
						case Button_6: PC_DATA_team2.Name = "Rozowi   "; LEDRGB_SetPredefinedColor(LED_PINK, TEAM2); PC_DATA_team2.predef_color = LED_PINK; break;
						case Button_7: PC_DATA_team2.Name = "Bez tasm "; LEDRGB_SetPredefinedColor(LED_WHITE, TEAM2); PC_DATA_team2.predef_color = LED_WHITE; break;
						case Button_CANCEL: PC_flags.settings = step3; break;
						default: PC_DATA_team2.predef_color = 100; break;
					}
					if(PC_DATA_team2.predef_color != 100)
					{
						if(PC_DATA_team1.predef_color != PC_DATA_team2.predef_color) PC_flags.settings++;
						else ST7735_PutStr5x7(10, 100, "Ten sam kolor!",COLOR565_WHITE ,COLOR565_INDIAN_RED);
					}

					break;
				}
				case step7:
				{
					PointCapture_Settings_Menu_4();
					LEDRGBon(TEAM2);
					PC_flags.settings++;
				}
				case step8:
				{
					if(PC_DATA.buttons == Button_OK)
					{
						PC_flags.settings = 0;
						PointCapture_StartGame();
					}
					else if(PC_DATA.buttons == Button_CANCEL)
					{
						PC_flags.settings = step5;
					}
					break;
				}
			}
		}
		if(PC_flags.blink_tick == 1)
		{
			switch(PC_flags.settings)
			{
				case step2:KeyToLCD_blink(46, 20,COLOR565_WHITE ,COLOR565_INDIAN_RED); break;
				default: break;
			}
			PC_flags.blink_tick = 0;
		}
		PC_flags.tick = 0;
	}
}

void PointCapture_Mode1_Menu()
{
	ST7735_Clear(COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 15, "Czas: ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 40, "Przejete przez:  ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 70, "Prowadzi druzyna: ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 100, "Tryb: ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 110, "Dominacja Punktu v1",COLOR565_WHITE ,COLOR565_INDIAN_RED);
}

void PointCapture_Mode1_service()
{
	if(PC_flags.GameIsON == 1)
	{
		ADCKeyboard_GetButtonsState(&PC_DATA.buttons);
		if(PC_DATA.buttons == 1) PC_DATA.TeamInControlOfPoint = 1;
		else if(PC_DATA.buttons == 2) PC_DATA.TeamInControlOfPoint = 2;

		PointCapture_TeamInControl_LED();
		PointCapture_DominatingTeam_Choose();
		PointCapture_Mode1_DisplayInfo();
		PointCapture_Mode1_EndOfGame();
	}
}

void PointCapture_Mode1_DisplayInfo()
{
	if(PC_DATA.TeamInControlOfPoint == 1) ST7735_PutStr5x7(10, 50, PC_DATA_team1.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else if(PC_DATA.TeamInControlOfPoint == 2 ) ST7735_PutStr5x7(10, 50, PC_DATA_team2.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);


	if(PC_DATA.DominatingTeam == 1) ST7735_PutStr5x7(10, 80, PC_DATA_team1.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else if(PC_DATA.DominatingTeam == 2) ST7735_PutStr5x7(10, 80, PC_DATA_team2.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
}

void PointCapture_Mode1_EndOfGame()
{
	if((PC_DATA.time_HH == 0)  && (PC_DATA.time_MM == 0) && (PC_DATA.time_SS == 0))
	{
		PC_flags.GameIsON = 0;
		LEDRGBon(TEAM1);
		LEDRGBon(TEAM2);
		PointCapture_DominatingTeam_Choose();
		ST7735_Clear(COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(10, 10, "Punkt przejety!", COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(10, 30, "Dominujaca druzyna:", COLOR565_WHITE ,COLOR565_INDIAN_RED);
		switch(PC_DATA.DominatingTeam)
		{
			case 1: ST7735_PutStr5x7(10, 40, PC_DATA_team1.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED); break;
			case 2: ST7735_PutStr5x7(10, 40, PC_DATA_team2.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED); break;
			default: ST7735_PutStr5x7(10, 40, "REMIS! :O", COLOR565_WHITE ,COLOR565_INDIAN_RED); break;
		}
		ST7735_PutStr5x7(10, 60, "Czas dominacji: ", COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(10, 70, PC_DATA_team1.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(70, 70, PC_DATA_team2.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
		PointCapture_DisplayTime(10, 80, TIME_TEAM1);
		PointCapture_DisplayTime(70, 80, TIME_TEAM2);
	}
}

void PointCapture_Mode2_Menu()
{
	ST7735_Clear(COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 10, "Czas: ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 30, "Przejete przez: ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 55, PC_DATA_team1.Name,COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 80, PC_DATA_team2.Name,COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 100, "Tryb: ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 110, "Dominacja Punktu v2",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	PointCapture_DisplayTime(49,10,TIME_GLOBAL);

}

void PointCapture_Mode2_service()
{
	if(PC_flags.GameIsON == 1)
		{
			ADCKeyboard_GetButtonsState(&PC_DATA.buttons);
			if(PC_DATA.buttons == 1) PC_DATA.TeamInControlOfPoint = 1;
			else if(PC_DATA.buttons == 2) PC_DATA.TeamInControlOfPoint = 2;

			PointCapture_DominatingTeam_Choose();
			PointCapture_TeamInControl_LED();
			PointCapture_Mode2_DisplayInfo();
			PointCapture_Mode2_EndOfGame();
		}

}

void PointCapture_Mode2_DisplayInfo()
{
	if(PC_DATA.TeamInControlOfPoint == 1) ST7735_PutStr5x7(30, 40, PC_DATA_team1.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else if(PC_DATA.TeamInControlOfPoint == 2) ST7735_PutStr5x7(30, 40, PC_DATA_team2.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
}

void PointCapture_Mode2_EndOfGame()
{
	if((PC_DATA.time_HH == PC_DATA_team1.time_HH)  && (PC_DATA.time_MM == PC_DATA_team1.time_MM) && (PC_DATA.time_SS == PC_DATA_team1.time_SS))
	{
		PC_flags.GameIsON = 0;
		LEDRGBon(TEAM1);
		LEDRGBon(TEAM2);
		ST7735_PutStr5x7(10, 30, "Punkt zostal zdoboty",COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(30, 40, "Wygrywa ", COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(76, 40, PC_DATA_team1.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);

	}
	else if((PC_DATA.time_HH == PC_DATA_team2.time_HH)  && (PC_DATA.time_MM == PC_DATA_team2.time_MM) && (PC_DATA.time_SS == PC_DATA_team2.time_SS))
	{
		PC_flags.GameIsON = 0;
		LEDRGBon(TEAM1);
		LEDRGBon(TEAM2);
		ST7735_PutStr5x7(30, 40, "Wygrywa ", COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(76, 40, PC_DATA_team2.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
	}
}

void PointCapture_Settings()
{
	PC_flags.settings = 1;
}

void PointCapture_Settings_Menu_1()
{
	ST7735_Clear(COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 5, "USTAWIENIA",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 20, "Czas: HHMMSS ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 100, "Tryb: ",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	if(PC_DATA.mode == 1 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v1",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else if(PC_DATA.mode == 2 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v2",COLOR565_WHITE ,COLOR565_INDIAN_RED);
}

void PointCapture_Settings_Menu_2()
{
	ST7735_Clear(COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 5, "USTAWIENIA",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 20, "Wybierz kolor TEAM1",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 30, "1. Czerwony",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 40, "2. Niebieski",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 50, "3. Zielony",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 60, "4. Pomaranczowy",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 70, "5. Zolty",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 80, "6. Rozowy",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 90, "7. Bez tasm",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	if(PC_DATA.mode == 1 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v1",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else if(PC_DATA.mode == 2 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v2",COLOR565_WHITE ,COLOR565_INDIAN_RED);
}

void PointCapture_Settings_Menu_3()
{
	ST7735_Clear(COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 5, "USTAWIENIA",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 20, "Wybierz kolor TEAM2",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 30, "1. Czerwony",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 40, "2. Niebieski",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 50, "3. Zielony",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 60, "4. Pomaranczowy",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 70, "5. Zolty",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 80, "6. Rozowy",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 90, "7. Bez tasm",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	if(PC_DATA.mode == 1 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v1",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else if(PC_DATA.mode == 2 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v2",COLOR565_WHITE ,COLOR565_INDIAN_RED);
}

void PointCapture_Settings_Menu_4()
{
	ST7735_Clear(COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 5, "USTAWIENIA",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 20, "Czas:",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	PointCapture_DisplayTime(58, 20, TIME_GLOBAL);
	ST7735_PutStr5x7(10, 40, "TEAM1", COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(50, 40, PC_DATA_team1.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 50, "TEAM2", COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(50, 50, PC_DATA_team2.Name, COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 70, "OK aby rozpoczac", COLOR565_WHITE ,COLOR565_INDIAN_RED);
	ST7735_PutStr5x7(10, 90, "CANCEL - cofnij", COLOR565_WHITE ,COLOR565_INDIAN_RED);
	if(PC_DATA.mode == 1 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v1",COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else if(PC_DATA.mode == 2 )ST7735_PutStr5x7(10, 110, "Przejecie punktu v2",COLOR565_WHITE ,COLOR565_INDIAN_RED);
}

void PointCapture_TeamInControl_LED()
{
	switch(PC_DATA.TeamInControlOfPoint)
	{
		case 1:
			{
				LEDRGBon(TEAM1);
				LEDRGBoff(TEAM2);
				break;
			}
		case 2:
			{
				LEDRGBon(TEAM2);
				LEDRGBoff(TEAM1);
				break;
			}
		default:
			{
				LEDRGBoff(TEAM1);
				LEDRGBoff(TEAM2);
				break;
			}
	}

}

void PointCapture_DominatingTeam_Choose()
{
	if(PC_DATA_team1.time_HH > PC_DATA_team2.time_HH) PC_DATA.DominatingTeam= 1;
	else if(PC_DATA_team1.time_HH == PC_DATA_team2.time_HH)
	{
		if(PC_DATA_team1.time_MM > PC_DATA_team2.time_MM) PC_DATA.DominatingTeam= 1;
		else if(PC_DATA_team1.time_MM == PC_DATA_team2.time_MM)
		{
			if(PC_DATA_team1.time_SS > PC_DATA_team2.time_SS) PC_DATA.DominatingTeam = 1;
			else if(PC_DATA_team1.time_SS == PC_DATA_team2.time_SS)
			{
				PC_DATA.DominatingTeam = 0;
			}
			else PC_DATA.DominatingTeam = 2;
		}
		else PC_DATA.DominatingTeam = 2;
	}
	else PC_DATA.DominatingTeam = 2;
}

void PointCapture_DisplayTime(uint16_t X, uint16_t Y, TimeID_TypeDef which_time) //X,Y - begining of string
{
	char buff[10];
	char *pbuff = &buff;
	uint8_t HH,MM,SS;

	switch(which_time)
	{
		case TIME_GLOBAL:
		{
			HH = PC_DATA.time_HH;
			MM = PC_DATA.time_MM;
			SS = PC_DATA.time_SS;
			break;
		}
		case TIME_TEAM1:
		{
			HH = PC_DATA_team1.time_HH;
			MM = PC_DATA_team1.time_MM;
			SS = PC_DATA_team1.time_SS;
			break;
		}
		case TIME_TEAM2:
		{
			HH = PC_DATA_team2.time_HH;
			MM = PC_DATA_team2.time_MM;
			SS = PC_DATA_team2.time_SS;
			break;
		}
		default:
		{
			ST7735_PutStr5x7(10, 10, "ERROR PointCapture_DisplayTime which_team default!",COLOR565_WHITE ,COLOR565_INDIAN_RED);
			break;
		}
	}

	if(HH > 9) ST7735_PutStr5x7(X, Y, itoa(HH, pbuff, 10),COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else
	{
		ST7735_PutStr5x7(X, Y, "0",COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(X+6, Y, itoa(HH, pbuff, 10),COLOR565_WHITE ,COLOR565_INDIAN_RED);
	}

	ST7735_PutStr5x7(X+14, Y, ":" ,COLOR565_WHITE ,COLOR565_INDIAN_RED);

	if(MM > 9) ST7735_PutStr5x7(X+21, Y, itoa(MM, pbuff, 10),COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else
	{
		ST7735_PutStr5x7(X+21, Y, "0",COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(X+27, Y, itoa(MM, pbuff, 10),COLOR565_WHITE ,COLOR565_INDIAN_RED);
	}

	ST7735_PutStr5x7(X+35, Y, ":" ,COLOR565_WHITE ,COLOR565_INDIAN_RED);

	if(SS > 9)ST7735_PutStr5x7(X+42, Y, itoa(SS, pbuff, 10),COLOR565_WHITE ,COLOR565_INDIAN_RED);
	else
	{
		ST7735_PutStr5x7(X+42, Y, "0",COLOR565_WHITE ,COLOR565_INDIAN_RED);
		ST7735_PutStr5x7(X+47, Y, itoa(SS, pbuff, 10),COLOR565_WHITE ,COLOR565_INDIAN_RED);
	}
}

void PointCapture_SetTime(uint8_t HH, uint8_t MM, uint8_t SS)
{
	PC_DATA.time_HH = HH;
	PC_DATA.time_MM = MM;
	PC_DATA.time_SS = SS;
}

void PointCapture_ModeSelect(uint8_t MODE)
{
	switch(MODE)
	{
		case 1: PC_DATA.mode = 1; break;
		case 2: PC_DATA.mode = 2; break;
		default: PC_DATA.mode = 1; break;
	}
}

void PointCapture_StartGame()
{
	if(PC_DATA.mode == 1) PointCapture_Mode1_Menu();
	else if(PC_DATA.mode == 2) PointCapture_Mode2_Menu();
	PC_DATA_team1.time_HH = 0;
	PC_DATA_team1.time_MM = 0;
	PC_DATA_team1.time_SS = 0;
	PC_DATA_team2.time_HH = 0;
	PC_DATA_team2.time_MM = 0;
	PC_DATA_team2.time_SS = 0;
	PC_flags.GameIsON = 1;
	PC_DATA.DominatingTeam = 0;
	PC_DATA.TeamInControlOfPoint = 0;
}
