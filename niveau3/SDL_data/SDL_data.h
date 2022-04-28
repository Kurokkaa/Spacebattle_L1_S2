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
#include "../struct/struct.h"
#include <math.h>
#include <time.h>
#include "..\sdl2\sdl2-ttf-light.h"



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
#endif