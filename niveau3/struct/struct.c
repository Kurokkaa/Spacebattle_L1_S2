
/**
 * \file struct.c
 * \brief Module graphique du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */

#include "struct.h"

/**
 * @brief retourne la valeur de is_apply
 * 
 * @param sprite 
 * @return int la valeur d'is_apply
 */
int get_is_apply(sprite_t* sprite){
    return sprite->is_apply;
}
/**
 * @brief retourne la valeur de is_invisible
 * 
 * @param sprite 
 * @return int 
 */
int get_is_visible(sprite_t* sprite){
    return sprite->is_visible;
    }
/**
 * @brief retourne la valeur de x 
 * 
 * @param sprite 
 * @return int 
 */
int get_x(sprite_t* sprite){
    return sprite->x;
}
/**
 * @brief retourne la valeur de y
 * 
 * @param sprite 
 * @return int 
 */
int get_y(sprite_t* sprite){
    return sprite->y;
}
/**
 * @brief retourne la valeur de h
 * 
 * @param sprite 
 * @return int 
 */
int get_h(sprite_t* sprite){
    return sprite->h;
}
/**
 * @brief retourne la valeur de v
 * 
 * @param sprite 
 * @return int 
 */
int get_v(sprite_t* sprite){
    return sprite->v;
}
/**
 * @brief retourne la valeur de w
 * 
 * @param sprite 
 * @return int 
 */
int get_w(sprite_t* sprite){
    return sprite->w;
}
/**
 * @brief met is_visible à 1
 * @param sprite 
 */
void set_visible(sprite_t* sprite){
    sprite->is_visible=1;
}
/**
 * @brief met is_visible à 0
 * 
 */
void set_invisible(sprite_t* sprite){
    sprite->is_visible=0;
}
/**
 * @brief rend le sprite applicable
 * 
 * @param sprite 
 */
void set_apply(sprite_t* sprite){
    sprite->is_apply = 1;
}
/**
 * @brief rend le sprite inapplicable
 * 
 * @param sprite 
 */
void set_not_apply(sprite_t* sprite){
    sprite->is_apply = 0;
}
/**
 * @brief change la valeur de x
 * 
 * @param sprite 
 * @param x 
 */
void set_x(sprite_t* sprite,int x){
    sprite->x=x;
}
/**
 * @brief change la valeur de y
 * 
 * @param sprite 
 * @param y
 */
void set_y(sprite_t* sprite,int y){
    sprite->y=y;
}
/**
 * @brief change la valeur de h
 * 
 * @param sprite 
 * @param h
 */
void set_h(sprite_t* sprite,int h){
    sprite->h=h;
}
/**
 * @brief change la valeur de w
 * 
 * @param sprite 
 * @param w 
 */
void set_w(sprite_t* sprite,int w){
    sprite->w=w;
}
/**
 * @brief change la valeur de v
 * 
 * @param sprite 
 * @param v
 */
void set_v(sprite_t* sprite,int v ){
    sprite->v=v;
    }

