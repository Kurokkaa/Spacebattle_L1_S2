#ifndef STRUCT_F
#define STRUCT_F


#include "../SDL2/sdl2-light.h"
#include "../constantes/constantes.h"
#include "..\sdl2\sdl2-ttf-light.h"


/**
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage graphique
*/

struct ressources_s
{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* skin_ship; /*!< apparence du vaisseau*/
    SDL_Texture* skin_ennemy[NB_ENEMIES]; /*!< apparende de l'ennemi*/
    SDL_Texture* missile; /*!<apparence du missile*/
    TTF_Font* font;  /*!< Police d'ecriture */
    SDL_Texture* menu_sprite;
};

typedef struct ressources_s ressources_t;




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
 * \param ship le vaisseau du joueur 
 * \param enemies le tableau de tous les ennemies
 * \param missile le sprite du missile
*/

struct world_s
{
    sprite_t ship;
    sprite_t enemies[NB_ENEMIES];
    sprite_t missile;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int nb_enemies_survived;
    enum etat state;
    int nb_enemies_left;
    int score;
    int timer_end;
    int life;
};

typedef struct world_s world_t;

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
void life_counter(world_t* world);
#endif



