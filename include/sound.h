#ifndef __SOUND_H__
#define __SOUND_H__

#include "types.h"

extern volatile uint8_t music_on;

void play_sound(uint32_t frequence, uint32_t time);

void no_sound();

void beep(void);

void play_music(void);

void tetris_theme(void);
  
void mario_theme(void);
  
void impossible_mission_theme(void);

#endif
