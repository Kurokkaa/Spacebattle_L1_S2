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

#define SHIP_SIZE 32


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
 * @brief nombres d'ennemie
 */
#define NB_ENEMIES 20
/**
 * @brief distance vertical entre deux ennemies
 * 
 */
#define VERTICAL_DIST (2*SHIP_SIZE)
/**
 * @brief nombre d'itération à attendre avant de fermer le jeu
 * 
 */
#define TIME_ENDING 270
/**
 * @brief énumeration afin de gérer les différents états du jeu
 * 
 */
enum etat {gagnant,perdu,fin,jeu,menu};

#endif