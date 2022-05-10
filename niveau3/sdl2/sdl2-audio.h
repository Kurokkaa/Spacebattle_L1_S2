/**
 * @file sdl2-audio.h
 * @author CHAPUSOT Alexis et ANDRE Jeffrey
 * @brief module de gestion audio pour space_b 
 * @date 2022-04-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __SDL2_MIXER__LIGHT__H__
#define __SDL2_MIXER__LIGHT__H__

#include "..\..\SDL2-2.0.20\x86_64-w64-mingw32\include\SDL2\SDL_mixer.h"
#include <stdio.h>


struct audio_s
{
    Mix_Chunk* missile_shot;
    Mix_Chunk* menu_theme;
    Mix_Chunk* death;
    Mix_Chunk* enemy_destruction;
    Mix_Chunk* Game_over;
    Mix_Chunk* game_theme;
    
};

typedef struct audio_s audio_t;


void init_audio();
void init_music(audio_t* sound);
void clean_audio(audio_t* sound);
Mix_Chunk* load_music(char* path);
void channel_allocation(int nb_channels);
int change_volume(int channel, int volume);
void play_music(int channel,Mix_Chunk* music,int times);
void stop_music(int channel);






#endif