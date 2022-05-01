/**
 * \file SDL_graphics.h
 * \brief Constantes du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */


#ifndef SDL_graphics_H
#define SDL_graphics


#include "../constantes/constantes.h"
#include "..\sdl2\sdl2-light.h"
#include "..\sdl2\sdl2-ttf-light.h"
#include <math.h>
#include "../SDL_data/SDL_data.h"
#include "../SDL2/sdl2-audio.h"

/**
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage graphique
 * @param background la texture de fond du jeu
 * @param skin_ship apparence du vaisseau
 * @param skin_ennemy tableau de textures des ennemis
 * @param missile apparence du missile
 * @param font police utilisé pour afficher du texte
 * @param menu_sprite logo du menu
 * @param coeur_plein texture des coeurs plein
 * @param coeur_vide  texture des coeurs vides
*/

struct ressources_s
{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* skin_ship; /*!< apparence du vaisseau*/
    SDL_Texture* skin_ennemy[NB_ENEMIES]; /*!< apparence de l'ennemi*/
    SDL_Texture* missile; /*!<apparence du missile*/
    TTF_Font* font;  /*!< Police d'ecriture */
    SDL_Texture* menu_sprite;
    SDL_Texture* coeur_plein;
    SDL_Texture* coeur_vide;
    audio_t sound;
};

typedef struct ressources_s ressources_t;

void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources);
void apply_background(SDL_Renderer *renderer, ressources_t *ressources);
void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite);
void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]);
void display_life(SDL_Renderer *renderer,ressources_t* ressources,world_t* world);
void display_selection_zone(int x, int y, int w, int h,SDL_Renderer *renderer);
#endif