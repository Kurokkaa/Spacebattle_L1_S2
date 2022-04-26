/**
 * \file SDL_graphics.h
 * \brief Constantes du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */


#ifndef SDL_graphics
#define SDL_graphics

#include "../struct/struct.h"
#include "../constantes/constantes.h"
#include "..\sdl2\sdl2-light.h"
#include "..\sdl2\sdl2-ttf-light.h"
#include <math.h>

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(textures_t *textures);
/**
 * @brief charge les images liées au textures 
 * 
 * @param renderer le renderer
 * @param textures les textures
 */
void  init_textures(SDL_Renderer *renderer, textures_t *textures);
/**
 * @brief 
 * 
 * @param renderer le renderer
 * @param textures les textures
 */
void init_textures_enemies(SDL_Renderer *renderer, textures_t *textures);

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);



void apply_background(SDL_Renderer *renderer, textures_t *textures);

void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite);

void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]);

char* display_score(world_t* world);

#endif