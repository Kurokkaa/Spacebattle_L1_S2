/**
 * \file constante.h
 * \brief Constantes du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H
/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 30

/**
 * @brief Taille du Mini boss
 * 
 */
#define MBOSS_SIZE 135

/**
 * \brief Taille du missile
*/

#define MISSILE_SIZE 8
/**
 * @brief vitesse verticale de l'ennemi
 */
#define ENEMY_SPEED 1
/**
 * @brief vitesse verticale du missile
 */
#define MISSILE_SPEED 5
/**
 * @brief nombres d'ennemies
 */
#define NB_ENEMIES 10
/**
 * @brief distance vertical entre deux ennemies
 * 
 */
#define VERTICAL_DIST (4*SHIP_SIZE)
/**
 * @brief nombre d'itération à attendre avant de fermer le jeu
 * 
 */
#define TIME_ENDING 270

/**
 * @brief nombre de vies du vaisseau
 */
#define LIFE_NUMBER 3
/**
 * @brief nombre de vagues d'ennemies
 * 
 */
#define NB_WAVE 10
/**
 * @brief énumeration afin de gérer les différents états du jeu
 * 
 */
enum etat {gagnant,perdu,fin,jeu,menu};
#define TIMER_BETWEEN_2_FRAMES 6
#endif