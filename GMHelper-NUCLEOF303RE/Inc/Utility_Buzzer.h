/*
 * Utility_Buzzer.h
 *
 *  Created on: May 17, 2020
 *      Author: h4XX0rZ
 */

#ifndef INC_UTILITY_BUZZER_H_
#define INC_UTILITY_BUZZER_H_

#include "Utility_PitchNotes.h"
#include "MX_Initialize.h"

//-----IT and services------
void Buzzer_notes_it();
void Buzzer_note_duration_it();
void Buzzer_note_duration_service();
//-----Sound effects------
void Buzzer_SetNote(uint16_t note);
void Buzzer_PlayTone(uint16_t note, uint8_t duration);
//-----Tracks------
void Buzzer_PlayTrack1();
void Buzzer_PlayTrack2();
//-----For specific usage------
void Buzzer_Bomb();
void Buzzer_h4XX1nG();
//-----Other------
void Buzzer_Start();
void Buzzer_Stop();

#endif /* INC_UTILITY_BUZZER_H_ */
