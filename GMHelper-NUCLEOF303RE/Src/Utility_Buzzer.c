/*
 * Utility_Buzzer.c
 *
 *  Created on: May 17, 2020
 *      Author: h4XX0rZ
 *
 *      Notes for Pirates of the Carribean -  https://github.com/xitangg/-Pirates-of-the-Caribbean-Theme-Song
 */

#include "Utility_Buzzer.h"

#define TRACK1_DURATION	203
#define TRACK2_DURATION 26

//-------ENUMS-------
enum
{
	Track_NONE,
	Track_1,
	Track_2
};

enum
{
	FULLNOTE = 40,				//value * 4,5ms || 40 * 4,5ms = 180ms
	HALFNOTE = FULLNOTE/2,
	QUATERNOTE = HALFNOTE/2,
	EIGHTNOTE = QUATERNOTE/2,
	PAUSE = 30
};

//-------global-------
struct
{
	uint8_t ONoff;
	uint8_t Silence;
	uint8_t track;
	uint8_t note_pause;
}Buzzer_flags;


struct
{
	uint16_t note_duration;
	uint16_t note_duration_cnt;
	uint16_t pause_duration_cnt;
	uint8_t  track_duration;
	uint16_t track_which_tone;
}Buzzer_DATA;

//-------Track1-------
//Pirates of the Carribean
uint16_t Track1_notes[] =
		{
			NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
			NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
		    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
		    NOTE_A4, NOTE_G4, NOTE_A4, 0,

	  	    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
		    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
			NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
			NOTE_A4, NOTE_G4, NOTE_A4, 0,

			NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
			NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
			NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
			NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

			NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
			NOTE_D5, NOTE_E5, NOTE_A4, 0,
			NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
			NOTE_C5, NOTE_A4, NOTE_B4, 0,

			NOTE_A4, NOTE_A4,
			//Repeat of first part
			NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
			NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
			NOTE_A4, NOTE_G4, NOTE_A4, 0,

			NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
			NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
			NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
			NOTE_A4, NOTE_G4, NOTE_A4, 0,

			NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
			NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
			NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
			NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

			NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
			NOTE_D5, NOTE_E5, NOTE_A4, 0,
			NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
			NOTE_C5, NOTE_A4, NOTE_B4, 0,
			//End of Repeat

			NOTE_E5, 0, 0, NOTE_F5, 0, 0,
			NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
			NOTE_D5, 0, 0, NOTE_C5, 0, 0,
			NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

			NOTE_E5, 0, 0, NOTE_F5, 0, 0,
			NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
			NOTE_D5, 0, 0, NOTE_C5, 0, 0,
			NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
		};
uint16_t Track1_notes_duration[] =
		{
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, EIGHTNOTE,

			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, EIGHTNOTE,

			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE,

			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			QUATERNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, EIGHTNOTE+QUATERNOTE,

			QUATERNOTE, EIGHTNOTE,
			//Rpeat of First Part
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, EIGHTNOTE,

			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, EIGHTNOTE,

			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE,

			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			QUATERNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, EIGHTNOTE+QUATERNOTE,
			//End of Repeat

			QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE,
			QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, HALFNOTE,

			QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE,
			QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE, QUATERNOTE, EIGHTNOTE, EIGHTNOTE+QUATERNOTE,
			EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, HALFNOTE
		};


//-------Track2-------
//Win sound
uint16_t Track2_notes[] =
{
	NOTE_A3, NOTE_A5, NOTE_A6, NOTE_A3, NOTE_A5,
	NOTE_A6, NOTE_A6, NOTE_E3, NOTE_E5, NOTE_A6,
	NOTE_E3, NOTE_E5, NOTE_E3, NOTE_E5, NOTE_E7,
	NOTE_E6, NOTE_C8, NOTE_E6, NOTE_CS8, NOTE_D8,
	NOTE_D4, 0, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4
};
uint16_t Track2_notes_duration[] =
{
	EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE,
	EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE,
	EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE,
	EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE,
	EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE, EIGHTNOTE
};


//-------- CODE STARTS HERE --------


void Buzzer_notes_it()
{
	if(Buzzer_flags.Silence == 0) HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
}

void Buzzer_note_duration_it()
{
	if(Buzzer_flags.note_pause == 0) Buzzer_DATA.note_duration_cnt++;
	else if(Buzzer_flags.note_pause == 1) Buzzer_DATA.pause_duration_cnt++;
}

void Buzzer_note_duration_service()
{
	switch(Buzzer_flags.note_pause)
	{
		case 0:
			{
				if(Buzzer_DATA.note_duration_cnt >= Buzzer_DATA.note_duration)
					{
						Buzzer_flags.note_pause = 1;
						Buzzer_flags.Silence = 1;
					}
				break;
			}
		case 1:
			{
				if(Buzzer_DATA.pause_duration_cnt >= PAUSE)
						{
							Buzzer_flags.note_pause = 2;
							Buzzer_flags.Silence = 0;
						}
				break;
			}
		case 2:
			{
				if(++Buzzer_DATA.track_which_tone <= Buzzer_DATA.track_duration)
					{
						switch(Buzzer_flags.track)
							{
								case Track_1: Buzzer_PlayTone(Track1_notes[Buzzer_DATA.track_which_tone], Track1_notes_duration[Buzzer_DATA.track_which_tone]); break;
								case Track_2: Buzzer_PlayTone(Track2_notes[Buzzer_DATA.track_which_tone], Track2_notes_duration[Buzzer_DATA.track_which_tone]); break;
								default: break;
							}
						Buzzer_flags.note_pause = 0;
						Buzzer_DATA.note_duration_cnt = 0;
						Buzzer_DATA.pause_duration_cnt = 0;

					}
					else
					{
						Buzzer_flags.track = Track_NONE;
						Buzzer_Stop();
						Buzzer_flags.note_pause = 3;
					}
					break;
				}
			default: break;
	}

}

void Buzzer_SetNote(uint16_t note)
{
	htim15.Instance->ARR = note;
	htim15.Instance->CNT = 0;
	Buzzer_flags.Silence = 0; //Timer prescaler setted to 143 so interrupts freq 500kHz, Set ARR to predefined value (Utility_PitchNotes) to get required freq for note
}

void Buzzer_PlayTone(uint16_t note, uint8_t duration)
{
	Buzzer_SetNote(note);
	Buzzer_DATA.note_duration = duration;
	Buzzer_flags.note_pause = 0;
}

void Buzzer_PlayTrack1()
{
	Buzzer_DATA.track_which_tone = 0;
	Buzzer_PlayTone(Track1_notes[0],Track1_notes_duration[0]);
	Buzzer_DATA.track_duration = TRACK1_DURATION;
	Buzzer_flags.track = Track_1;
	Buzzer_Start();
}

void Buzzer_PlayTrack2()
{
	Buzzer_DATA.track_which_tone = 0;
	Buzzer_PlayTone(Track2_notes[0],Track2_notes_duration[0]);
	Buzzer_DATA.track_duration = TRACK2_DURATION;
	Buzzer_flags.track = Track_2;
	Buzzer_Start();
}

void Buzzer_Bomb()
{
	Buzzer_SetNote(NOTE_C7);
	Buzzer_Start();
}
void Buzzer_h4XX1nG()
{
	if(Buzzer_flags.track == Track_NONE) Buzzer_PlayTrack1();
}

void Buzzer_Start()
{
	HAL_TIM_Base_Start_IT(&htim15);
	Buzzer_flags.ONoff = 1;
}

void Buzzer_Stop()
{
	HAL_TIM_Base_Stop_IT(&htim15);
	Buzzer_flags.ONoff = 0;
	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, 0);
}
