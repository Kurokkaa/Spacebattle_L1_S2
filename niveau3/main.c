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
void clean_texture_textures_enemies(SDL_Texture** texture){
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
void clean_ressources(ressources_t *ressources){
    clean_texture(ressources->background);
    clean_texture(ressources->skin_ship);
    clean_texture(ressources->missile);
    clean_texture_textures_enemies(ressources->skin_ennemy);
    clean_audio(&(ressources->sound));
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
    }
}


/**
 * @brief charge les images liées au textures 
 * 
 * @param renderer le renderer
 * @param ressources les ressources
 */
void init_ressources(SDL_Renderer *renderer, ressources_t *ressources){
    ressources->background = load_image( "ressources/space-background.bmp",renderer);
    
    ressources->skin_ship = load_image("ressources/spaceship.bmp",renderer);

    init_textures_enemies(renderer,ressources);

    ressources->missile = load_image("ressources/missile.bmp", renderer);
    
    ressources->font  = load_font("ressources/arial.ttf",14);

    ressources->menu_sprite = load_image("ressources/spacebattle.bmp",renderer);

    ressources->coeur_plein = load_image("ressources/coeur_plein.bmp",renderer);
    
    ressources->coeur_vide = load_image("ressources/coeur_vide.bmp",renderer);

    ressources->solo_menu = load_image("ressources/Solo.bmp",renderer);

    init_music(&(ressources->sound));
}
/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *ressources, world_t * world){
    clean_ressources(ressources);
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
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world){
    init_data(world);
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_audio();
    init_ressources(*renderer,ressources);
    
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

    
    //initialisation du jeu
    init(&window,&renderer,&ressources,&world);
   
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
       //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&ressources);
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
        
    }
    
    //nettoyage final
    clean(window,renderer,&ressources,&world);
    
    
    return 0;
}
