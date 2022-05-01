
#include "sdl2-audio.h"


void init_audio(){
    
   Mix_OpenAudio(20000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 5096);
    
     channel_allocation(3);
    Mix_Volume(0,100);
    Mix_Volume(1,100);
    Mix_Volume(2,100);
   
    
}
void clean_audio(audio_t* sound){
    Mix_FreeChunk(sound->missile_shot); 
    Mix_FreeChunk(sound->menu_theme);
    Mix_FreeChunk(sound->death);
    Mix_FreeChunk(sound->enemy_destruction);
    Mix_FreeChunk(sound->Game_over);
    Mix_FreeChunk(sound->game_theme);
}

Mix_Chunk* load_music(char* path){
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if(sound==NULL){
        printf("Erreur de chargement %s \n",Mix_GetError());
    }
    return sound;
}
void init_music(audio_t* sound){
    sound->missile_shot = load_music("ressources/audio/missile_shot.wav");
    sound->menu_theme = load_music("ressources/audio/menu_theme.wav");
    sound->death = load_music("ressources/audio/death.wav");
    sound->enemy_destruction = load_music("ressources/audio/enemy_destruction.wav");
    sound->Game_over = load_music("ressources/audio/Game_over.wav");
    sound->game_theme = load_music("ressources/audio/game_theme.wav");
}

void play_music(int channel,Mix_Chunk* music,int times){

    Mix_PlayChannel(channel,music,times);
}
void channel_allocation(int nb_channels){
    Mix_AllocateChannels(nb_channels);
}
int change_volume(int channel, int volume){
    return Mix_Volume(channel,volume);
}
void stop_music(int channel){
    Mix_HaltChannel(channel);
}