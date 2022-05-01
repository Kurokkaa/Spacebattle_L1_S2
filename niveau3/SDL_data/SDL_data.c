/**
 * \file SDL_data.c
 * \brief Module de gestion des données du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */


#include "SDL_data.h"



/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_data(world_t * world){
                /*----------------------------------initialisation des sprites--------------------------------*/
    init_ennemies(world);
    
   
    init_sprite(&(world->missile),SCREEN_WIDTH/2-MISSILE_SIZE/2, SCREEN_HEIGHT-3*SHIP_SIZE/2+MISSILE_SIZE-SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile));
             /*---------------------------------------------------------------------------------------------*/
    //on n'est pas à la fin du jeu
    world->gameover = 0;   
    world->nb_enemies_left=NB_ENEMIES; //il reste tous les ennemies au début
    world->nb_enemies_survived=0;      
    world->score=0;
    world->state=menu;                 //on ne lance pas le jeu au démarrage de l'application mais le menu
    world->timer_end=0;                //compte à rebours de la fermeture de la fenêtre
    world->life=LIFE_NUMBER;
    world->menu_courant=0;
    world->playable = 1;
    init_sprite(&(world->ship), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-3*SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, 0);
    printf("%d",world->ship.is_apply);
    printf("%d",world->ship.is_visible);
    printf("%d",world->score);
}



/**
 * @brief afficher les données d'un sprite
 * 
 * @param sprite le sprite examiné
 */
void print_sprite(sprite_t* sprite){
    printf("X: %d\ny: %d\nh: %d\nw: %d\nv: %d\n",sprite->x,sprite->y,sprite->h,sprite->w,sprite->v);
}


/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world){
    return world->gameover;
}

/**
 * @brief replace le missile en cas de destruction
 * @param world le monde du jeu
 * 
 */
void replace_missile(world_t* world){
    //si le missile dépasse la zone haute de l'écran ou a eu une collision
    if(get_y(&(world->missile))<=0 || !get_is_apply(&(world->missile)) ){ 
        //on le cache afin de la replacer
        set_apply(&(world->missile));
        set_invisible(&(world->missile));  
    }
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world){
    switch (world->state)
    {
    case menu:
        if(world->x_logo>=SCREEN_HEIGHT/5){
            world->x_logo=SCREEN_HEIGHT/5;
        }
        else world->x_logo+=3;
        break;
    case jeu:
        replace_missile(world);
        move_missile(world);
        left_limit(&(world->ship));
        right_limit(&(world->ship));
        update_ennemies(world);
        handle_ennemies(world);  
        compute_game(world);
        break;
    case perdu:
        compute_game(world);
        break;
    case gagnant:
        compute_game(world);
        break;
    case fin:
        compute_game(world);
        break;
    default:
        break;
    }
    if(world->state==menu){
        
    }
    else{
    
    }

    

}

/**
 * @brief gère la position des ennemies
 * @param world le monde du jeu
 */
void handle_ennemies(world_t* world){
    //si le vaisseau n'a pas été détruit
    if(get_is_apply(&(world->ship))){
        //on vérifie les collision avec les 
        for(int i = 0; i<NB_ENEMIES;i++){
            //si l'ennemi n'a pas été détruit
            if(get_is_apply(&(world->enemies[i]))){
                handle_sprites_collision(&(world->ship),&(world->enemies[i]),world);
                //si le missile n'est pas visible il doit être ignoré
                if(get_is_visible(&(world->missile))){
                    handle_sprites_collision(&(world->missile),&(world->enemies[i]),world);
                }
            }
    //si le vaisseau enemi est en dehors de l'ecran
    //il a survécu
    //et on le retire du jeu et on enleve une vie au joueur
    if(get_y(&(world->enemies[i]))>=SCREEN_HEIGHT && world->enemies[i].is_apply){
        set_not_apply(&(world->enemies[i]));
        set_invisible(&(world->enemies[i]));
        world->nb_enemies_survived++;
        world->nb_enemies_left--;
        lose_life(world);

    }
        }
    }
}

/**
 * @brief déplace le missile
 * @param world le monde
 */

void move_missile(world_t* world){
    //s'il est visible il est donc lancé il doit monter en fonction de MISSILE_SPEED
    if(get_is_visible(&(world->missile))){
    set_y(&(world->missile),get_y(&(world->missile))-MISSILE_SPEED); /*!< Si le missile est visible, c'est qu'il doit se déplacer */
    }
    //sinon il est positionné au dessus du vaisseau 
    else{
        set_x(&(world->missile),get_x(&(world->ship))+SHIP_SIZE/2-MISSILE_SIZE/2); /*!< sinon il doit être placer au dessus du vaisseau*/
        set_y(&(world->missile),get_y(&(world->ship))); /*!< sinon il doit être placer au dessus du vaisseau*/
    }
}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
         //Si l'utilisateur a cliqué sur le X de la fenêtre
        switch(event->type){
            case SDL_QUIT:
                //On indique la fin du jeu
                world->gameover=1;
                break;
            case SDL_KEYDOWN:
                switch (world->state) //selon l'état du jeu les touches ne font pas la même action
                {
                case menu:
                    switch (event->key.keysym.sym){
                        case SDLK_RETURN:
                            switch (world->menu_courant)
                            {
                            case 0:
                                world->state=jeu;
                                break;
                            
                            case 2:
                                world->gameover=1;
                            }
                            break;
                        case SDLK_DOWN:
                            world->menu_courant++;
                            if(world->menu_courant>2){
                                world->menu_courant=0;
                            }
                            break;
                        case SDLK_UP:
                            if(world->menu_courant==0){
                                world->menu_courant=2;
                            }
                            else{
                                world->menu_courant--;
                            }
                            break;
                        case SDLK_ESCAPE:
                            world->gameover=1;
                            break;
                    }
                    break; 
                case jeu:
                    switch (event->key.keysym.sym)
                    {
                    case SDLK_d:
                        printf("La touche D est appuyée\n");
                        break;
                    case SDLK_RIGHT:
                        set_x(&(world->ship),get_x(&world->ship)+10);
                        break;
                    case SDLK_LEFT:
                        set_x(&(world->ship),get_x(&world->ship)-10);
                        break;
                    case SDLK_SPACE:
                        if(get_is_visible(&(world->ship))){ // on peut tirer seulement si le vaisseau est visible
                            set_visible(&(world->missile));
                        }
                        break;
                    case SDLK_ESCAPE:
                        world->gameover=1;
                        break;
                    }
                }
        }
    }
}
/**
 * @brief Fonction pour initialiser les valeurs des coordonnées d'un vaisseau
 * 
 * @param sprite la structure de type struct_t
 * @param x abscisse
 * @param y ordonnée
 * @param w largeur
 * @param h hauteur
 * @param v vitesse verticale
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v){
    sprite->is_apply=1;
    sprite->is_visible=1;
    set_x(sprite,x);
    set_y(sprite,y);
    set_w(sprite,w);
    set_h(sprite,h);
    set_v(sprite,v);
     
}
/**
 * @brief la fonction bloque le vaisseau sur la gauche pour qu'il ne sorte pas de l'écran
 * 
 * @param sprite le vaisseau
 */
void left_limit(sprite_t* sprite){
    if(sprite->x<=0){
        sprite->x=0;
    }
}
/**
 * @brief la fonction bloque le vaisseau sur la droite pour qu'il ne sorte pas de l'écran
 * 
 * @param sprite le vaisseau
 */
void right_limit(sprite_t* sprite){
    //si la droite du sprite arrive au bord il est bloqué
    if(sprite->x>=SCREEN_WIDTH-SHIP_SIZE){
        sprite->x=SCREEN_WIDTH-SHIP_SIZE;
    }
}
/**
 * @brief fonction qui va repositionner l'ennemi en haut de l'ecran s'il dépasse le bas de l'écran
 * 
 * @param sprite l'ennemi
 */
void bottom_limit(sprite_t* sprite){
    if(sprite->y>=SCREEN_HEIGHT){
        sprite->y=0;
    }
}
/**
 * @brief retourne 1 si une collision entre les deux sprites à lieu sinon 0
 * @param *spa pointeur vers le 1eme sprite
 * @param *sp2 pointeur vers le 2eme sprite
 */
int sprites_collide(sprite_t *sp2, sprite_t *sp1){
    int distanceX = sp1->x - sp2->x;
    int distanceY = sp1->y - sp2->y;
    int distance  = sqrt(distanceX*distanceX + distanceY*distanceY);
    return (distance <= sp1->w/2 + sp2->w/2); 
}
/**
 * @brief efface les sprites en cas de collision
 * 
 * @param sp2 
 * @param sp1 
 */

void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t* world){
    if (sprites_collide(sp2,sp1)){
        sp1->is_visible=0; 
        sp2->is_visible=0;
        sp1->is_apply=0;
        sp2->is_apply=0;
        world->nb_enemies_left--;
        world->score++;
        
    }
}
/**
 * @brief génère un nombre entre a et b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int generate_number(int a, int b){
    return rand()%(b-a)+a;
    }
/**
 * @brief initialise les ennemies 
 * 
 * @param world 
 */   
void init_ennemies(world_t* world){
    int i;
    int x;
    int y;
    world->enemies=(sprite_t*)malloc(sizeof(sprite_t)*NB_ENEMIES); 
    for(i=0;i<NB_ENEMIES;i++){
        x = generate_number(0,SCREEN_WIDTH-SHIP_SIZE);
        y = -(SHIP_SIZE + i* VERTICAL_DIST);
        init_sprite(&(world->enemies[i]),x,y,SHIP_SIZE,SHIP_SIZE,ENEMY_SPEED);
    }
}
/**
 * @brief mise à jour de la position des ennnemies
 * 
 * @param world 
 */
void update_ennemies(world_t* world){
    int i;
    for(i=0;i<NB_ENEMIES;i++){
        world->enemies[i].y+=world->enemies[i].v;
    }
}
/**
 * @brief compteur du nombre de vies
 *
 * @param world
 */
void lose_life(world_t* world){
    world->life-=1;
}
/**
 * @brief retourne 1 si l'etat = perdu,gagnant ou fin
 * 
 * @param world 
 */
int CheckState(world_t* world){
    return world->state==perdu || world->state==gagnant || world->state==fin;
}
/**
 * @brief returne 1 si le nombre de vie égal à 0 sinon 0
 * 
 * @param world 
 * @return int 
 */
int CheckLife(world_t* world){
    return world->life==0;
}
/**
 * @brief retourne si le nombre d'ennemi restant = 0
 * 
 * @param world 
 * @return int 
 */
int CheckEnemiesLeft(world_t* world){
    return world->nb_enemies_left==0;
}

/**
 * @brief retourne si le nombre d'ennemi qui à survie = 0
 * 
 * @param world 
 * @return int 
 */
int CheckEnemiesSurvived(world_t* world){
    return world->nb_enemies_survived==0;
}
/**
 * @brief change l'état de la partie en fonction de la situation
 * 
 * @param world 
 */
void compute_game(world_t* world){
  
    if(world->timer_end==TIME_ENDING){
            world->gameover=1;    
        }
    else if(CheckState(world)){   
            //si on est en fin de partie le compte à rebours progresse
            world->timer_end++;
    }
    else{
        if(CheckLife(world)||!get_is_visible(&(world->ship))){
            //la partie est perdu
                world->score=0;
                world->state=perdu;
        }
        //sinon si tous les ennemis sont mort ou a survécu
         if(CheckEnemiesLeft(world)){
            //on regarde combien d'ennemi ont survécu
            //s'ils ont eté tous détruit
            if(CheckEnemiesSurvived(world)){
                //le joueur a gagné
                world->state=gagnant;
                world->score*=2;
                }
            //sinon la partie est juste terminé
            else{
                world->state=fin;   
                }
        }
    }
}

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
