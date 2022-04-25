/**
 * \file SDL_graphics.h
 * \brief Constantes du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */


#ifndef SDL_graphics
#define SDL_graphics
#include "../SDL2/sdl2-light.h"
#include "../struct/struct.h"
#include "../constantes/constantes.h"

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(textures_t *textures);
/**
 * @brief charge les images liées au textures 
 * 
 * @param renderer le moteur de rendu
 * @param textures la liste des textures
 */
void  init_textures(SDL_Renderer *renderer, textures_t *textures);

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world);

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world);

void apply_background(SDL_Renderer *renderer, textures_t *textures);



#endif