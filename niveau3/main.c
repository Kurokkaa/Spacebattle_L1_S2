/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "SDL2/sdl2-light.h"
#include "SDL_data/SDL_data.h"
#include "SDL_graphics/SDL_graphics.h"
#include "sdl2/sdl2-ttf-light.h"
#include "sdl2/sdl2-audio.h"
void clean_texture_enemies(SDL_Texture** texture,SDL_Texture** texture_boss){
    int i;
    for(i=0;i<NB_ENEMIES;i++){
        if(NULL != texture[i]){
        SDL_DestroyTexture(texture[i]);
    }
    }
}
/**
 * \brief La fonction nettoie les textures
 * \param ressources les ressources
*/
void clean_ressources(ressources_t *ressources,audio_t* sound){
    clean_texture(ressources->background);
    clean_texture(ressources->skin_ship);
    clean_texture(ressources->missile);
    clean_texture(ressources->coeur_plein);
    clean_texture(ressources->coeur_vide);
    clean_texture(ressources->menu_sprite);
    clean_texture(ressources->explosion);
    clean_texture(ressources->solo_menu);
    clean_texture(ressources->mini_boss_D);
    clean_texture(ressources->mini_boss_G);
    clean_texture(ressources->quitter_menu);
    clean_texture(ressources->highscore_menu);
    clean_texture(ressources->missile_mboss);
    clean_texture(ressources->bossp1);
    clean_texture(ressources->bossp2);
    clean_texture(ressources->missile_boss);
    clean_texture_enemies(ressources->skin_ennemy,ressources->skin_boss_enemy);
    
    
    clean_audio(sound);
    clean_font(ressources->font);

    
}
/**
 * @brief 
 * 
 * @param renderer le renderer
 * @param ressources les ressources
 */
void init_textures_enemies(SDL_Renderer *renderer, ressources_t *ressources){
    for(int i = 0;i<NB_ENEMIES;i++){
        ressources->skin_ennemy[i]=load_image("ressources/enemy.bmp",renderer);
        ressources->life_texture[i]=load_image("ressources/coeur_plein.bmp",renderer);
    }
    for(int i = 0;i<NB_SBIRES;i++){
        ressources->skin_boss_enemy[i]=load_image("ressources/enemy.bmp",renderer);
    }
}


/**
 * @brief charge les images liées au textures 
 * 
 * @param renderer le renderer
 * @param ressources les ressources
 */
void init_ressources(SDL_Renderer *renderer, ressources_t *ressources,audio_t* audio){
    ressources->background = load_image( "ressources/space-background.bmp",renderer);
    
    ressources->skin_ship = load_image("ressources/spaceship.bmp",renderer);

    init_textures_enemies(renderer,ressources);

    ressources->missile = load_image("ressources/missile.bmp", renderer);
    
    ressources->font  = load_font("ressources/arial.ttf",14);

    ressources->menu_sprite = load_image("ressources/spacebattle.bmp",renderer);

    ressources->coeur_plein = load_image("ressources/coeur_plein.bmp",renderer);
    
    ressources->coeur_vide = load_image("ressources/coeur_vide.bmp",renderer);

    ressources->solo_menu = load_image("ressources/Solo.bmp",renderer);

    ressources->explosion = load_image("ressources/explosion.bmp",renderer);

    ressources->quitter_menu = load_image("ressources/quitter.bmp",renderer);

    ressources->highscore_menu = load_image("ressources/highscore.bmp",renderer);

    ressources->mini_boss_D = load_image("ressources/boss1d.bmp",renderer);

    ressources->mini_boss_G = load_image("ressources/boss1g.bmp",renderer);

    ressources->missile_mboss = load_image("ressources/missilemb.bmp",renderer);
    
    ressources->bossp1 = load_image("ressources/bossp1.bmp",renderer);

    ressources->bossp2 = load_image("ressources/bossp2.bmp",renderer);

    ressources->missile_boss = load_image("ressources/missile_boss.bmp",renderer);

    init_music(audio);
}

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *ressources, world_t * world,audio_t* audio){
    clean_ressources(ressources,audio);
    clean_sdl(renderer,window);
}

/**
 * @brief initialise les différents module
 * 
 * @param window 
 * @param renderer 
 * @param ressources 
 * @param world 
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world,audio_t* audio){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_ttf();
    init_audio();
    init_ressources(*renderer,ressources,audio);
    
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int WinMain( int argc, char* args[] )
{
    srand(time(NULL));
    SDL_Event event;
    world_t world;
    ressources_t ressources;
    SDL_Renderer *renderer;
    SDL_Window *window;
    audio_t audio;

    
    //initialisation du jeu
    init(&window,&renderer,&ressources,&world,&audio);
    
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
       //mise à jour des données liée à la physique du monde
        update_data(&world,&audio);
        
        //gestion des évènements
        handle_events(&event,&world,&audio);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&ressources,&audio);
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
        
    }
    
    //nettoyage final
    clean(window,renderer,&ressources,&world,&audio);
    
    
    return 0;
}
