/**
 * @file sdl2-audio.c
 * @author CHAPUSOT ALEXIS et ANDRE JEFFREY
 * @brief fichier de la gestion sonore de spacebattle
 */
#include "sdl2-audio.h"

/**
 * @brief initialise le module audio et alloue 3 canaux
 */
void init_audio(){
    
    Mix_OpenAudio(41000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 10192);
    
    channel_allocation(3);
    Mix_Volume(0,100);
    Mix_Volume(1,100);
    Mix_Volume(2,100);
}
/**
 * @brief décharge les sons
 * @param sound la liste des sons
 */
void clean_audio(audio_t* sound){
    Mix_FreeChunk(sound->missile_shot); 
    Mix_FreeChunk(sound->menu_theme);
    Mix_FreeChunk(sound->death);
    Mix_FreeChunk(sound->enemy_destruction);
    Mix_FreeChunk(sound->Game_over);
    Mix_FreeChunk(sound->game_theme);
}
/**
 * @brief renvoie un pointeur vers le son souhaité 
 * 
 * @param path le chemin vers le son
 * @return Mix_Chunk* 
 */
Mix_Chunk* load_music(char* path){
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if(sound==NULL){
        printf("Erreur de chargement %s \n",Mix_GetError());
    }
    return sound;
}
/**
 * @brief charge les sons 
 * @param sound 
 */
void init_music(audio_t* sound){
    sound->missile_shot = load_music("ressources/audio/missile_shot.wav");
    sound->menu_theme = load_music("ressources/audio/menu_theme.wav");
    sound->death = load_music("ressources/audio/death.wav");
    sound->enemy_destruction = load_music("ressources/audio/enemy_destruction.wav");
    sound->Game_over = load_music("ressources/audio/Game_over.wav");
    sound->game_theme = load_music("ressources/audio/game_theme.wav");
}
/**
 * @brief joue le son
 * 
 * @param channel le canal sur lequelle le son doit être joué
 * @param music un pointeur vers le son
 * @param times le nombre de fois qu'il doit être rejouer, -1 s'il doit être jouer en boucle 
 */
void play_music(int channel,Mix_Chunk* music,int times){

    Mix_PlayChannel(channel,music,times);
}
/**
 * @brief alloue le nombre de canaux souhaité
 * 
 * @param nb_channels le nombre de canaux
 */
void channel_allocation(int nb_channels){
    Mix_AllocateChannels(nb_channels);
}
/**
 * @brief change le volume sur le canal
 * 
 * @param channel le canal à changé
 * @param volume le volume en pourcentage
 * @return int le succès de l'opération
 */
int change_volume(int channel, int volume){
    return Mix_Volume(channel,volume);
}
/**
 * @brief arrête le son sur le canal
 * @param channel le canal qui doit être arrêté
 */
void stop_music(int channel){
    Mix_HaltChannel(channel);
}