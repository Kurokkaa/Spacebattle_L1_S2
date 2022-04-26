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
#include "struct/struct.h"
#include "sdl2/sdl2-ttf-light.h"

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int WinMain( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    
    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    

    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
       //mise à jour des données liée à la physique du monde
        update_data(&world);
 
        //gestion des évènements
        handle_events(&event,&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
        
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
