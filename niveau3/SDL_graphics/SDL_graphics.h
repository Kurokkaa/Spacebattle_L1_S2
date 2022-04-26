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
 * \param ressources les ressources
*/
void clean_textures(ressources_t *ressources);
/**
 * @brief charge les images liées au textures 
 * 
 * @param renderer le renderer
 * @param ressources les ressources
 */
void  init_textures(SDL_Renderer *renderer, ressources_t *ressources);
/**
 * @brief 
 * 
 * @param renderer le renderer
 * @param ressources les ressources
 */
void init_textures_enemies(SDL_Renderer *renderer, ressources_t *ressources);

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t* ressources, world_t * world);
/**
 * @brief met à jour le renderer
 * 
 * @param renderer le renderer
 * @param world le monde du jeu
 * @param ressources les ressources
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources);



/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param ressources les ressources
*/

void apply_background(SDL_Renderer *renderer, ressources_t *ressources);
/**
 * @brief affiche l'entité à la position enregistré dans les données du jeu
 * 
 * @param renderer le renderer 
 * @param texture la texture de l'entité
 * @param sprite l'entité
 */
void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite);
/**
 * @brief affiche les texture des ennemies selon leur position
 * 
 * @param renderer le renderer 
 * @param texture la texture de l'entité
 * @param sprite l'entité 
 */
void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]);


#endif