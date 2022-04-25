/**
 * \file SDL_data.h
 * \brief Constantes du jeu
 * \author CHAPUSOT Alexis
 * \version 1.0
 * \date 7 AVRIL 2022
 */
#ifndef SDL_DATA_H
#define SDL_DATA_H
#include "../constantes/constantes.h"
#include "../SDL2/sdl2-light.h"
#include <stdio.h>
#include <stdlib.h>
#include "../struct/struct.h"


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world);

/**
 * @brief afficher les données d'un sprite
 * 
 * @param sprite le sprite examiné
 */
void print_sprite(sprite_t* sprite);


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */

void update_data(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world);

/**
 * @brief rend visible l'objet
 * 
 * @param sprite 
 */

void set_visible(sprite_t* sprite);

/**
 * @brief rend invisible le sprite
 * 
 * @param sprite 
 */

void set_invisible(sprite_t* sprite);

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world);


/**
 * @brief Fonction pour initialiser les valeurs des coordonnées d'un vaisseau
 * 
 * @param sprite la structure de type struct_t
 * @param x abscisse
 * @param y ordonnée
 * @param w largeur
 * @param h hauteur
 * @param v vitesse verticale
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, textures_t *textures);

/**
 * @brief la fonction bloque le vaisseau sur la droite pour qu'il ne sorte pas de l'écran
 * 
 * @param sprite le vaisseau
 */
void right_limit(sprite_t* sprite);

/**
 * @brief la fonction bloque le vaisseau sur la gauche pour qu'il ne sorte pas de l'écran
 * 
 * @param sprite le vaisseau
 */
void left_limit(sprite_t* sprite);

/**
 * @brief fonction qui va repositionner l'ennemi en haut de l'ecran s'il dépasse le bas de l'écran
 * 
 * @param sprite l'ennemi
 */
void bottom_limit(sprite_t* sprite);
/**
 * @brief retourne 1 si une collision entre les deux sprites à lieu sinon 0
 * @param *spa pointeur vers le 1eme sprite
 * @param *sp2 pointeur vers le 2eme sprite
 */
int sprites_collide(sprite_t *sp2, sprite_t *sp1);

void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1);

void init_ennemies(world_t* world);

#endif