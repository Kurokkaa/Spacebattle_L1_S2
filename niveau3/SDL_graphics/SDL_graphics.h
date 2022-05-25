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
 * @param skin_boss_enemy textures des ennemies qui accompagnent le boss
 * @param missile apparence du missile
 * @param font police utilisé pour afficher du texte
 * @param menu_sprite logo du menu
 * @param coeur_plein texture des coeurs plein
 * @param coeur_vide  texture des coeurs vides
 * @param quitter_menu Logo quitter dans le menu
 * @param highscore_menu Logo highscore dans le menu
 * @param explosion Texture de l'explosion
 * @param mini_boss_G Texture du boss qui va à gauche
 * @param mini_boss_D Texture du boss qui va à droite
 * @param missile_mboss Texture du missile du mid boss
 * @param bossp1 Texture du boss phase 1
 * @param bossp2 Texture du boss phase 2
 * @param missile_boss Texture du missile du boss
*/

struct ressources_s
{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* skin_ship; /*!< Texture du vaisseau*/
    SDL_Texture* skin_ennemy[NB_ENEMIES]; /*!< Texture de l'ennemi*/
    SDL_Texture* skin_boss_enemy[NB_SBIRES];
    SDL_Texture* missile; /*!<Apparence du missile*/
    TTF_Font* font;  /*!< Police d'ecriture */
    SDL_Texture* menu_sprite; /*!<Texture du logo dans le menu*/
    SDL_Texture* coeur_plein; /*!< Texture des coeurs pleins */
    SDL_Texture* coeur_vide; /*!< Texture des coeurs vide */
    SDL_Texture* solo_menu; /*!< Texture du bouton solo dans le menu*/
    SDL_Texture* quitter_menu; /*!< Texture du bouton quitter*/
    SDL_Texture* highscore_menu; /*:<Texture du bouton highscore dans le menu*/
    SDL_Texture* explosion; /*!< Texture de l'animation des explosions*/
    SDL_Texture* mini_boss_G;/*!< Texture du boss qui va à gauche*/
    SDL_Texture* mini_boss_D;/*!< Texture du boss qui va à droite*/
    SDL_Texture* missile_mboss; /*<Texture du missile que le boss tire*/
    SDL_Texture* bossp1; /*<Texture de la phase 1 du boss*/
    SDL_Texture* bossp2; /*<Texture de la phase 2 du boss*/
    SDL_Texture* missile_boss;/*<Texture du missile du boss*/
    SDL_Texture* life_texture[NB_ENEMIES]
};

typedef struct ressources_s ressources_t;



void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources,audio_t* audio);
void apply_background(SDL_Renderer *renderer, ressources_t *ressources);
void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite);
void apply_sbires(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]);
void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]);
void display_life(SDL_Renderer *renderer,ressources_t* ressources,world_t* world);
void display_selection_zone(int x, int y, int w, int h,SDL_Renderer *renderer);
void draw_animation(world_t* world,ressources_t* ressources,SDL_Renderer* renderer);
void display_rank(SDL_Renderer* renderer, world_t* world,ressources_t* ressources);
#endif