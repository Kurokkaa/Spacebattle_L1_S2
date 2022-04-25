#ifndef STRUCT_F
#define STRUCT_F

#include "../SDL2/sdl2-light.h"

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s
{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* skin_ship; /*! apparence du vaisseau*/
    SDL_Texture* skin_ennemy; /*! apparende de l'ennemi*/
    SDL_Texture* missile; /*apparence du missile*/
};

typedef struct textures_s textures_t;




/**
 * @brief representations des entités du jeu
 * @param x position de x par rapport au centre
 * @param y position de y par rapport au centre du sprite
 * @param h la  hauteur du sprite
 * @param w la largeur du sprite 
 * @param v la vitesse vertical du sprite 
 * @param is_visible le sprite doit-il être affiché ou non  
 */

struct sprite_s
{
    /* data */
    int x;
    int y;
    int h;
    int w;
    int v;
    int is_visible; 
    int is_apply;  
};

typedef struct sprite_s sprite_t;

/**
 * \brief Représentation du monde du jeu
*/

struct world_s
{
    sprite_t ship;
    sprite_t ennemi;
    sprite_t missile;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
};

typedef struct world_s world_t;



#endif



