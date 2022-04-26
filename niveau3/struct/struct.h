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
};

typedef struct world_s world_t;
/**
 * @brief retourne la valeur de is_apply
 * 
 * @param sprite 
 * @return int la valeur d'is_apply
 */
int get_is_apply(sprite_t* sprite);
/**
 * @brief retourne la valeur de is_invisible
 * 
 * @param sprite 
 * @return int 
 */
int get_is_visible(sprite_t* sprite);

/**
 * @brief retourne la valeur de x 
 * 
 * @param sprite 
 * @return int 
 */
int get_x(sprite_t* sprite);
/**
 * @brief retourne la valeur de y
 * 
 * @param sprite 
 * @return int 
 */
int get_y(sprite_t* sprite);
/**
 * @brief retourne la valeur de h
 * 
 * @param sprite 
 * @return int 
 */
int get_h(sprite_t* sprite);
/**
 * @brief retourne la valeur de w
 * 
 * @param sprite 
 * @return int 
 */
int get_w(sprite_t* sprite);
/**
 * @brief retourne la valeur de v
 * 
 * @param sprite 
 * @return int 
 */
int get_v(sprite_t* sprite);
/**
 * @brief met is_visible à 1
 * @param sprite 
 */
void set_visible(sprite_t* sprite);
/**
 * @brief met is_visible à 0
 * 
 */
void set_invisible(sprite_t* sprite);
/**
 * @brief change la valeur de x
 * 
 * @param sprite 
 * @param x 
 */
void set_x(sprite_t* sprite,int x);
/**
 * @brief change la valeur de y
 * 
 * @param sprite 
 * @param y
 */
void set_y(sprite_t* sprite,int y);
/**
 * @brief change la valeur de h
 * 
 * @param sprite 
 * @param h
 */
void set_h(sprite_t* sprite,int h);
/**
 * @brief change la valeur de w
 * 
 * @param sprite 
 * @param w 
 */
void set_w(sprite_t* sprite,int w);
/**
 * @brief change la valeur de v
 * 
 * @param sprite 
 * @param v 
 */
void set_v(sprite_t* sprite,int v );
#endif



