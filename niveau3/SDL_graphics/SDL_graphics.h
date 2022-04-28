/**
 * \file SDL_graphics.h
 * \brief Constantes du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */


#ifndef SDL_graphics_H
#define SDL_graphics

#include "../struct/struct.h"
#include "../constantes/constantes.h"
#include "..\sdl2\sdl2-light.h"
#include "..\sdl2\sdl2-ttf-light.h"
#include <math.h>


void clean_textures(ressources_t *ressources);
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t* ressources, world_t * world);
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources);
void apply_background(SDL_Renderer *renderer, ressources_t *ressources);
void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite);
void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]);
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world);
void init_textures(SDL_Renderer *renderer, ressources_t *ressources);
void init_textures_enemies(SDL_Renderer *renderer, ressources_t *ressources);
void display_life(SDL_Renderer *renderer,ressources_t* ressources,world_t* world);
#endif