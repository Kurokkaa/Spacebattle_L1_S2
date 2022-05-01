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
#include "..\sdl2\sdl2-light.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "..\sdl2\sdl2-ttf-light.h"
#include "..\sdl2\sdl2-audio.h"

/**
 * @brief representations des entités du jeu
 * @param x position de x par rapport au centre
 * @param y position de y par rapport au centre du sprite
 * @param h la  hauteur du sprite
 * @param w la largeur du sprite 
 * @param v la vitesse vertical du sprite 
 * @param is_visible le sprite doit-il être affiché ou non  
 * @param is_apply le sprite doit-il être appliqué
 */

struct sprite_s
{
    /* data */
    int x; /*!< abscysses du sprite*/
    int y; /*!< ordonnée du sprite*/
    int h; /*!< hauteur du sprite*/
    int w; /*!< largeur du sprite*/
    int v; /*!< vitesse du sprite*/
    int is_visible; /*!< */
    int is_apply;  
};

typedef struct sprite_s sprite_t;






/**
 * \brief Représentation du monde du jeu
 * \param ship le vaisseau du joueur 
 * \param enemies le tableau de tous les ennemies
 * \param missile le sprite du missile
 * \param gameover le programme est-il terminer
 * \param nb_enemies_survived nombre d'ennemi ayant survécu
 * \param state l'etat du programme
 * \param nb_enemies_left nombre d'ennemi restant en jeu
 * \param score score du joueur
 * \param timer_end timer de fermeture de la fenêtre
 * \param life nombre de vie du vaisseau
*/

struct world_s
{
    sprite_t ship; /*!<sprite du vaisseau du joueur*/
    sprite_t* enemies; /*!<tableau de sprite_t représentant les ennemies*/
    sprite_t missile; /*<sprite du missile*.*/
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int nb_enemies_survived; /*!< nombre d'ennemis survécu*/
    enum etat state; /*!< etat du programme*/
    int nb_enemies_left; /*!< nombre d'ennemis restant*/
    int score; /*!< score actuel du joueur*/
    int timer_end; /*!< compte à rebours de la fermeture du programme*/
    int life;   /*!< nombre de vie restant du joueur*/
    int menu_courant; /*!< position dans le menu*/
    int x_logo; /*!< abscysse du logo dans le menu*/
    int playable;
};

typedef struct world_s world_t;

void init_data(world_t * world);
void print_sprite(sprite_t* sprite);
void clean_data(world_t *world);
int is_game_over(world_t *world);
void update_data(world_t *world);
void handle_events(SDL_Event *event,world_t *world);
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v);
void right_limit(sprite_t* sprite);
void left_limit(sprite_t* sprite);
void bottom_limit(sprite_t* sprite);
int sprites_collide(sprite_t *sp2, sprite_t *sp1);
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2,world_t* world);
void init_ennemies(world_t* world);
void update_ennemies(world_t* world);
void replace_missile(world_t* world);
void handle_ennemies(world_t* world);
void compute_game(world_t* world);
void move_missile(world_t* world);
int generate_number(int a, int b);
void lose_life(world_t* world);
int CheckState(world_t* world);
int CheckLife(world_t* world);
int get_is_apply(sprite_t* sprite);
int get_is_visible(sprite_t* sprite);
int get_x(sprite_t* sprite);
int get_y(sprite_t* sprite);
int get_h(sprite_t* sprite);
int get_w(sprite_t* sprite);
int get_v(sprite_t* sprite);
void set_visible(sprite_t* sprite);
void set_invisible(sprite_t* sprite);
void set_x(sprite_t* sprite,int x);
void set_y(sprite_t* sprite,int y);
void set_h(sprite_t* sprite,int h);
void set_w(sprite_t* sprite,int w);
void set_v(sprite_t* sprite,int v );
void set_apply(sprite_t* sprite);
void set_not_apply(sprite_t* sprite);
#endif