
/**
 * \file struct.c
 * \brief Module graphique du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */

#include "struct.h"


int get_is_apply(sprite_t* sprite){
    return sprite->is_apply;
}

int get_is_visible(sprite_t* sprite){
    return sprite->is_visible;
    }

int get_x(sprite_t* sprite){
    return sprite->x;
}

int get_y(sprite_t* sprite){
    return sprite->y;
}
int get_h(sprite_t* sprite){
    return sprite->h;
}

int get_v(sprite_t* sprite){
    return sprite->v;
}

int get_w(sprite_t* sprite){
    return sprite->w;
}

void set_visible(sprite_t* sprite){
    sprite->is_visible=1;
}

void set_invisible(sprite_t* sprite){
    sprite->is_visible=0;
}

void set_apply(sprite_t* sprite){
    sprite->is_apply = 1;
}
void set_not_apply(sprite_t* sprite){
    sprite->is_apply = 0;
}
void set_x(sprite_t* sprite,int x){
    sprite->x=x;
}
void set_y(sprite_t* sprite,int y){
    sprite->y=y;
}
void set_h(sprite_t* sprite,int h){
    sprite->h=h;
}
void set_w(sprite_t* sprite,int w){
    sprite->w=w;
}
void set_v(sprite_t* sprite,int v ){
    sprite->v=v;
    }