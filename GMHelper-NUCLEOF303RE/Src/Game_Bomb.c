/*
 * Bomb.c
 *
 *  Created on: May 8, 2020
 *      Author: h4XX0rZ
 */

#include <Game_Bomb.h>

#define KEYIDS_LENGTH 13

//---------ENUM---------
enum
{
	step1 = 1,
	step2 = 2,
	step3 = 3,
	step4 = 4,
	step5 = 5,
	step6 = 6
}Setting_steps;
//---------FLAGS---------
struct
{
	uint8_t tick;
	uint8_t clock_tick;
	uint8_t blink_tick;
	uint8_t settings;
	uint8_t WrongPIN;
	uint8_t PINisOK;
	uint8_t settings_block;
	uint8_t GameIsON;
	uint8_t h4XX1nG;
	uint8_t mode;
	uint8_t KeyOK;
	uint8_t blink_swapper;
}Bomb_flags;
//---------GLOBAL---------
struct
{
	uint8_t Defusing_Key_ID;
	uint8_t h4XX1nG_Key_ID;
	uint8_t pin_length;
	uint8_t buttons;
	uint8_t time_HH;
	uint8_t time_MM;
	uint8_t time_SS;
	char PIN[8];
}Bomb_DATA;

uint8_t KeyIDs[KEYIDS_LENGTH] = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 13, 16, 17}; //5, 12, 14, 15, 18 excluded due to lack of those

void Bomb_tick_it()
{
	Bomb_flags.tick = 1;
}

void Bomb_blink_tick_it()
{
	Bomb_flags.blink_tick = 1;
}

void Bomb_clock_tick_it()
{
	Bomb_flags.clock_tick = 1;
}

void Bomb_tick_service()
{
	char buff[10];
	char *pbuff = buff;

	ADCKeyboard_GetButtonsState(&Bomb_DATA.buttons);
	if(Bomb_flags.settings_block == 1)
	{
		if(Bomb_DATA.buttons == Button_NONE) Bomb_flags.settings_block = 0;
	}

	if(Bomb_flags.GameIsON == 1)
	{
		if(Bomb_flags.tick == 1)
		{
			KeyToLCD_doit(45,70,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
			if(Bomb_DATA.buttons == Button_OK && Bomb_flags.settings_block == 0)
			{
				if(Bomb_flags.KeyOK == 1) //Check PIN if defusing key plugged
				{
					Bomb_CheckPIN();
					if(Bomb_flags.PINisOK == 1)
					{
						Bomb_Disarmed();
					}
					else
					{
						ST7735_PutStr5x7(10, 95, "NIEPOPRAWNY PIN",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
						KeyToLCD_buffor_clear();
						Bomb_flags.WrongPIN = 1;
					}

				}
				else if(Bomb_flags.KeyOK == 2) // Start hacking if h4XX1nG key plugged
				{
					Bomb_flags.h4XX1nG = 1;
					Bomb_flags.GameIsON = 0;
				}
				Bomb_flags.settings_block = 1;
			}
			Bomb_flags.tick = 0;
		}
		if(Bomb_flags.blink_tick == 1)
		{
			KeyToLCD_blink(45,70,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
			Bomb_flags.blink_tick = 0;
		}
		if(Bomb_flags.clock_tick == 1)
		{
			Clock4LCD_tick_decrement(&Bomb_DATA.time_HH, &Bomb_DATA.time_MM, &Bomb_DATA.time_SS);

			if(Bomb_flags.mode == STANDARD) Bomb_Display_Info();
			else Bomb_Display_Info_2();

			if(Bomb_flags.mode == WITH_KEYS)
				{
					uint8_t keyid;
					keyid = Janitor_GetKeyID();
					if(keyid == Bomb_DATA.Defusing_Key_ID) Bomb_flags.KeyOK = 1;
					else if(keyid == Bomb_DATA.h4XX1nG_Key_ID) Bomb_flags.KeyOK = 2;
					else if(keyid < 19) Bomb_flags.KeyOK = 0;
					else Bomb_flags.KeyOK = 3;
				}

			if(Bomb_flags.WrongPIN == 2)
			{
				ST7735_PutStr5x7(10, 95, "               ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
				Bomb_flags.WrongPIN = 0;
			}
			if(Bomb_flags.WrongPIN == 1) Bomb_flags.WrongPIN++;
			if(Bomb_TimeCheck())
			{
				Bomb_flags.GameIsON = 0;
				ST7735_PutStr5x7(10, 40, "Bomba wybuchla      ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
				ST7735_PutStr5x7(10, 50, "                    ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
				ST7735_PutStr5x7(10, 60, "Koniec rozgrywki!" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
				Buzzer_Bomb();
			}
			Bomb_flags.clock_tick = 0;
		}
	}

	if(Bomb_flags.settings!= 0 && Bomb_flags.GameIsON == 0)
	{
		if(Bomb_flags.tick == 1 && Bomb_flags.settings_block == 0)
		{
			switch(Bomb_flags.settings)
			{
				case step1:
					{
						if(Bomb_flags.mode == STANDARD) Bomb_Settings_Menu();
						else Bomb_Settings_Menu_2();
						Bomb_flags.settings++;
						break;
					}
				case step2: //Set Time
					{
						KeyToLCD_DATA.word_length = 5;
						KeyToLCD_doit(46,20,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
						if(Bomb_DATA.buttons == Button_OK)
						{
							Bomb_SetTime(10 * KeyToLCD_DATA.intbuff[0] + KeyToLCD_DATA.intbuff[1], 10 * KeyToLCD_DATA.intbuff[2] + KeyToLCD_DATA.intbuff[3], 10 * KeyToLCD_DATA.intbuff[4] + KeyToLCD_DATA.intbuff[5]);
							ST7735_PutStr5x7(46, 20, "        ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
							Bomb_DisplayTime(46, 20);
							ST7735_PutStr5x7(110, 20, "OK",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
							Bomb_flags.settings++;
							Bomb_flags.settings_block = 1;
							KeyToLCD_buffor_clear();
						}
						break;
					}
				case step3: //Set pin length
					{
						KeyToLCD_DATA.word_length = 0;
						KeyToLCD_doit(10,50,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
						if(Bomb_DATA.buttons == Button_OK)
						{
							Bomb_ResetPIN();
							Bomb_DATA.pin_length = KeyToLCD_DATA.intbuff[0] - 1;
							KeyToLCD_DATA.word_length = Bomb_DATA.pin_length;
							ST7735_PutStr5x7(10, 50, itoa(Bomb_DATA.pin_length + 1, &KeyToLCD_DATA.buff, 10),COLOR565_WHITE ,COLOR565_DARK_KHAKI);
							ST7735_PutStr5x7(110, 50, "OK",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
							Bomb_flags.settings++;
							Bomb_flags.settings_block = 1;
						}
						break;
					}
				case step4: //Set pin
					{
						uint8_t i;
						KeyToLCD_doit(40,60,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
						if(Bomb_DATA.buttons == Button_OK)
						{
							for(i=0; i < KeyToLCD_DATA.word_length + 1 ; i++) Bomb_DATA.PIN[i] = KeyToLCD_DATA.buff[i];
							ST7735_PutStr5x7(40, 60, &Bomb_DATA.PIN ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
							ST7735_PutStr5x7(110, 60, "OK",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
							if(Bomb_flags.mode == STANDARD) Bomb_flags.settings++;
							else
								{
									Bomb_flags.settings = step6;
									Bomb_KeyID_shuffle();
								}
							Bomb_flags.settings_block = 1;
							KeyToLCD_buffor_clear();
						}
						break;
					}
				case step5: //OK to start
					{
						ST7735_PutStr5x7(10, 90, "OK aby rozpoczac",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
						ST7735_PutStr5x7(10, 100, "CANCEL zmien ustaw.",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
						if(Bomb_DATA.buttons == Button_OK)
						{
							Bomb_flags.settings = 0;
							if(Bomb_flags.mode == STANDARD) Bomb_Display_Menu();
							else Bomb_Display_Menu_2();
							Bomb_Start();
						}
						else if(Bomb_DATA.buttons == Button_CANCEL)
						{
							Bomb_flags.settings = 1;
							KeyToLCD_buffor_clear();

						}
						break;
					}
				case step6: //Set defusing KEY
					{
						if(Janitor_GetKeyID() < 21) ST7735_PutStr5x7(90, 80, itoa(Janitor_GetKeyID(), pbuff, 10), COLOR565_WHITE ,COLOR565_DARK_KHAKI);
						else ST7735_PutStr5x7(90, 80, "? ", COLOR565_WHITE ,COLOR565_DARK_KHAKI);

						if(Bomb_DATA.buttons == Button_OK)
						{
							if(Janitor_GetKeyID() < 21) Bomb_DATA.Defusing_Key_ID = Janitor_GetKeyID();
							else Bomb_DATA.Defusing_Key_ID = KeyIDs[0];

							ST7735_PutStr5x7(90, 80, itoa(Bomb_DATA.Defusing_Key_ID, pbuff, 10), COLOR565_WHITE ,COLOR565_DARK_KHAKI);
							ST7735_PutStr5x7(110, 80, "OK", COLOR565_WHITE ,COLOR565_DARK_KHAKI);

							Bomb_DATA.h4XX1nG_Key_ID = KeyIDs[1];
							Bomb_flags.settings = step5;
							Bomb_flags.settings_block = 1;
						}
						break;
					}
				default: break;
			}
			Bomb_flags.tick = 0;
		}
		if(Bomb_flags.blink_tick == 1)
		{
			switch(Bomb_flags.settings)
			{
				case step2:KeyToLCD_blink(46,20,COLOR565_WHITE ,COLOR565_DARK_KHAKI); break;
				case step3:KeyToLCD_blink(10,50,COLOR565_WHITE ,COLOR565_DARK_KHAKI); break;
				case step4:KeyToLCD_blink(40,60,COLOR565_WHITE ,COLOR565_DARK_KHAKI); break;
				default: break;
			}
			Bomb_flags.blink_tick = 0;
		}
	}
	else if(Bomb_flags.h4XX1nG != 0)
	{
		if(Janitor_CheckIfKeyPlugged() == 1)
		{

			if(Bomb_flags.clock_tick == 1)
				{
					Clock4LCD_tick_decrement(&Bomb_DATA.time_HH, &Bomb_DATA.time_MM, &Bomb_DATA.time_SS);
					if(Bomb_flags.h4XX1nG == step2)
						{
							Buzzer_h4XX1nG();
							h4XX1nG_tick_it();
						}
					Bomb_flags.clock_tick = 0;
				}

			switch(Bomb_flags.h4XX1nG)
			{
				case step1: //hacking intro
				{
					h4XX1nG_reboot();
					h4XX1nG_menu();
					h4XX1nG_GetETA(&Bomb_DATA.time_HH, &Bomb_DATA.time_MM, &Bomb_DATA.time_SS);
					Bomb_flags.h4XX1nG++;
					break;
				}
				case step2: //hacking in progress
				{
					if(h4XX1nG_GetStatus() == 0) Bomb_flags.h4XX1nG++;
					break;
				}
				case step3: //hacking done
				{
					if(Bomb_DATA.buttons == Button_OK)
					{
						Bomb_Display_Menu_2();
						Bomb_flags.h4XX1nG = 0;
						Bomb_flags.GameIsON = 0;
						Bomb_Disarmed();

					}
					break;
				}
			}
		}
		else
		{
			Bomb_flags.h4XX1nG = 0;
			Bomb_flags.GameIsON = 1;
			Bomb_Display_Menu_2();
		}

	}
}



void Bomb_Display_Menu()
{
	ST7735_Clear(COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 40, "Podaj pin i wcisnij",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 50, "OK aby rozbroic" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 70, "PIN: ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 110, "Tryb: ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 120, "Rozborjenie bomby",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
}

void Bomb_Display_Menu_2()
{
	ST7735_Clear(COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 40, "Podaj pin i wcisnij",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 50, "OK aby rozbroic" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 70, "PIN: ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 85, "Klucz: ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 110, "Tryb: ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 120, "Rozbr. bomby klucze",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
}

void Bomb_Display_Info()
{
	Bomb_DisplayTime(30, 15);
}

void Bomb_Display_Info_2()
{
	Bomb_DisplayTime(30, 15);
	switch(Bomb_flags.KeyOK)
	{
		case 0: ST7735_PutStr5x7(52, 85, "NIEPOPRAWNY ",COLOR565_WHITE ,COLOR565_DARK_KHAKI); break;
		case 1: ST7735_PutStr5x7(52, 85, "OK          ",COLOR565_WHITE ,COLOR565_DARK_KHAKI); break;
		case 2: ST7735_PutStr5x7(52, 85, "G3t h4Xx3D  ",COLOR565_WHITE ,COLOR565_DARK_KHAKI); break;
		case 3: ST7735_PutStr5x7(52, 85, "NIE WYKRYTO ",COLOR565_WHITE ,COLOR565_DARK_KHAKI); break;
		default: break;
	}

}

void Bomb_CheckPIN()
{
	uint8_t i;
	uint8_t correct = 0;
	for(i = 0; i < KeyToLCD_DATA.word_length; i++)
	{
		if(Bomb_DATA.PIN[i] != KeyToLCD_DATA.buff[i]) correct++;
	}
	if(correct == 0) Bomb_flags.PINisOK = 1;
}

void Bomb_SetPIN(char pin[])
{
	uint8_t i;
	for(i = 0; i == Bomb_DATA.pin_length - 1; i++)
	{
		Bomb_DATA.PIN[i] = pin[i];
	}
}

void Bomb_ResetPIN()
{
	uint8_t  i;
	for(i=0;i < 8; i++) Bomb_DATA.PIN[i] = 0x20;
}

void Bomb_Settings(uint8_t mode)
{
	Bomb_SetMode(mode);
	Bomb_flags.settings= 1;
}

void Bomb_Settings_Menu()
{
	ST7735_Clear(COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 5, "USTAWIENIA",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 20, "Czas: HHMMSS ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 40, "Dlugosc PINu (1-9): ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 60, "PIN: XXXXXXXXX" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);

	ST7735_PutStr5x7(10, 110, "Tryb: ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 120, "Rozborjenie bomby",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
}

void Bomb_Settings_Menu_2()
{
	ST7735_Clear(COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 5, "USTAWIENIA",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 20, "Czas: HHMMSS ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 40, "Dlugosc PINu (1-9): ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 60, "PIN: XXXXXXXXX" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 80, "Numer klucza: " ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);

	ST7735_PutStr5x7(10, 110, "Tryb: ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 120, "Rozbr. bomby klucze",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
}

uint8_t Bomb_TimeCheck()
{
	if(Bomb_DATA.time_HH == 0 && Bomb_DATA.time_MM == 0 && Bomb_DATA.time_SS == 0) return 1;
	else return 0;
}

void Bomb_SetTime(uint32_t HH, uint32_t MM, uint32_t SS)
{
	if(SS < 60) Bomb_DATA.time_SS = SS;
	else
	{
		SS = SS-60;
		MM++;
		Bomb_DATA.time_SS = SS;
	}
	if(MM < 60) Bomb_DATA.time_MM = MM;
	else
	{
		MM = MM-60;
		HH++;
		Bomb_DATA.time_MM = MM;
	}
	if(HH < 100) Bomb_DATA.time_HH = HH;
	else Bomb_DATA.time_HH = 99;
}

void Bomb_DisplayTime(uint16_t X, uint16_t Y)
{
		char buff[10];	//PROOFCHECK THIS SHIT M8
		char *pbuff = buff;
		uint32_t HH,MM,SS;

		HH = Bomb_DATA.time_HH;
		MM = Bomb_DATA.time_MM;
		SS = Bomb_DATA.time_SS;

		if(HH > 9) ST7735_PutStr5x7(X, Y, itoa(HH, pbuff, 10),COLOR565_WHITE ,COLOR565_DARK_KHAKI);
		else
		{
			ST7735_PutStr5x7(X, Y, "0",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
			ST7735_PutStr5x7(X+7, Y, itoa(HH, pbuff, 10),COLOR565_WHITE ,COLOR565_DARK_KHAKI);
		}

		ST7735_PutStr5x7(X+14, Y, ":" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);

		if(MM > 9) ST7735_PutStr5x7(X+21, Y, itoa(MM, pbuff, 10),COLOR565_WHITE ,COLOR565_DARK_KHAKI);

		else
		{
			ST7735_PutStr5x7(X+21, Y, "0",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
			ST7735_PutStr5x7(X+28, Y, itoa(MM, pbuff, 10),COLOR565_WHITE ,COLOR565_DARK_KHAKI);
		}

		ST7735_PutStr5x7(X+35, Y, ":" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);

		if(SS > 9)ST7735_PutStr5x7(X+42, Y, itoa(SS, pbuff, 10),COLOR565_WHITE ,COLOR565_DARK_KHAKI);
		else
		{
			ST7735_PutStr5x7(X+42, Y, "0",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
			ST7735_PutStr5x7(X+48, Y, itoa(SS, pbuff, 10),COLOR565_WHITE ,COLOR565_DARK_KHAKI);
		}
}

void Bomb_KeyID_shuffle()
{
	uint32_t randbuff;
	uint8_t swapbuff;
	uint8_t i;

	for(i=KEYIDS_LENGTH-1; i>0 ;i--)
	{
		randbuff = RNG_Random()%i;
		swapbuff = KeyIDs[i];
		KeyIDs[i] = KeyIDs[randbuff];
		KeyIDs[randbuff] = swapbuff;
	}
}

void Bomb_Disarmed()
{
	ST7735_PutStr5x7(10, 40, "Bomba zostala       ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 50, "rozbrojona        ",COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	ST7735_PutStr5x7(10, 60, "Koniec rozgrywki!" ,COLOR565_WHITE ,COLOR565_DARK_KHAKI);
	Bomb_flags.GameIsON = 0;
	Buzzer_PlayTrack2();
}

void Bomb_SetMode(uint8_t mode)
{
	if(mode == STANDARD)
	{
		Bomb_flags.mode = STANDARD;
		Bomb_flags.KeyOK = 1;
	}
	else Bomb_flags.mode = WITH_KEYS;
}

void Bomb_Start()
{
	Bomb_flags.GameIsON = 1;
	Bomb_flags.h4XX1nG = 0;
	KeyToLCD_buffor_clear();
	KeyToLCD_DATA.word_length = 8;
}

void Bomb_Stop()
{
	Bomb_flags.GameIsON = 0;
}
