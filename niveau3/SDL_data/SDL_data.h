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
#include <string.h>
#include "sys/stat.h"

/**
 * @brief representations des entités du jeu
 * @param x position de x par rapport au centre
 * @param y position de y par rapport au centre du sprite
 * @param h la  hauteur du sprite
 * @param w la largeur du sprite 
 * @param v la vitesse vertical du sprite 
 * @param is_visible le sprite doit-il être affiché ou non  
 * @param is_apply le sprite doit-il être appliqué
 * @param life_points les points de vies du boss
 */

struct sprite_s
{ 
    int x; /*!< abscysses du sprite*/
    int y; /*!< ordonnée du sprite*/
    int h; /*!< hauteur du sprite*/
    int w; /*!< largeur du sprite*/
    int v; /*!< vitesse du sprite*/
    int is_visible; /*!<le sprite est-il visible */
    int is_apply;  /*!<le sprite est-il appliqué */
    int life_points; /*!<point de vie*/
    int direction; /*!<sens du boss*/
};

typedef struct sprite_s sprite_t;



/**
 * @brief struct qui gere les animation
 * @param frame_number numéro de l'étape de l'animation
 * @param frame_timer variable qui gère le frame rate de l'animation
 * @param x coordonées en x de l'animation
 * @param y coordonées en y de l'animtion
 * @param w largeur du sprite de l'animation
 * @param h hauteur du sprite de l'animation
 */

struct animation_s
{
    int frame_number; /*!<numéro de l'étape de l'animation*/
    int frame_timer; /*!<frame rate de l'animation*/
    int x;  /*!<coordonées en x de l'animation*/
    int y; /*!<coordonées en y de l'animtion*/
    int w; /*!largeur du sprite de l'animation*/
    int h; /*!hauteur du sprite de l'animation*/
};

typedef struct animation_s animation_t;

struct highscore_s
{
    char pseudo[11];
    char score[11]; 
};

typedef struct highscore_s highscore_t;
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
    sprite_t missile; /*<sprite du missile*/
    sprite_t mboss; /*<sprite du mini boss*/
    sprite_t missile_mboss;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int nb_enemies_survived; /*!< nombre d'ennemis survécu*/
    enum etat state; /*!< état du programme*/
    int nb_enemies_left; /*!< nombres d'ennemis restants*/
    int score; /*!< score actuel du joueur*/
    int timer_end; /*!< compte à rebours de la fermeture du programme*/
    int life;   /*!< nombre de vie restant du joueur*/
    int menu_courant; /*!< position dans le menu*/
    int x_logo; /*!< abscysse du logo dans le menu*/
    int playable; /*!<la musique doit-elle être joué*/
    animation_t explosion[10]; /*!<tableau qui stocke les animation de l'explosion*/
    int explosion_counter; /*!<nombres d'explosions*/
    int wave;/*!<numéro de la vague actuelle*/
    int mboss_shoot_cooldown;/*!<nombre d'itération avant la prochaine de tir du boss*/
    int pause; /*!<variable qui gère la pause*/
    char pseudo[SIZE_PSEUDO_MAX]; /*!chaine de caractères qui contiendra le pseudo du joueur*/
    highscore_t* rank;
    int nb_player;
};

typedef struct world_s world_t;

void init_data(world_t * world);
void print_sprite(sprite_t* sprite);
void clean_data(world_t *world);
int is_game_over(world_t *world);
void update_data(world_t *world,audio_t* audio);
void handle_events(SDL_Event* event,world_t *world,audio_t* audio);
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v);
void right_limit(sprite_t* sprite);
void left_limit(sprite_t* sprite);
int sprites_collide(sprite_t *sp2, sprite_t *sp1);
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2,world_t* world,audio_t* audio);
void init_ennemies(world_t* world);
void update_ennemies(world_t* world);
void replace_missile(world_t* world);
void handle_ennemies(world_t* world,audio_t* audio);
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
void add_animation(int x, int y,world_t* world);
void set_wave(world_t* world);
int check_wave(world_t* world);
void init_boss(sprite_t* boss,int x,int y,int w, int h,int v);
void move_missile_mboss(world_t* world);
void replace_missile_mboss(world_t* world);
void handle_mboss_collision(world_t* world);
void handle_mboss(world_t* world);
void move_mboss(world_t* world);
void assign_new_highscore(world_t* world,highscore_t* highscore_array,int size);
void read_highscore(world_t* world);
#endif