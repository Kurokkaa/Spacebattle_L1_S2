/**
 * \file SDL_data.c
 * \brief Module graphique du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */
#include "SDL_graphics.h"



/**
 * @brief affiche l'entité à la position enregistré dans les données du jeu
 * @param renderer le renderer 
 * @param texture la texture de l'entité à afficher
 * @param sprite les données de l'entité à afficher
 */
void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite){
    if(sprite->is_visible==1){ //si le sprite est visible on l'applique sinon 
        SDL_Rect dst = {0, 0, 0, 0};
    
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
        dst.x = sprite->x; dst.y=sprite->y;
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
    //si le vaisseau n'est ni affiché ni appliqué la texture est nettoyé
    else if(!(sprite->is_apply)){ //s'il ne doit pas être appliqué on nettoie la texture
        clean_texture(texture);
    }
}

/**
 * @brief met à jour le renderer
 * @param renderer le renderer
 * @param world le monde du jeu
 * @param ressources les ressources
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources){
    //tableau qui accueillera le score
    char number[15]; 
    
    //on vide le renderer
    clear_renderer(renderer);
    apply_background(renderer,ressources);
    //le score est transformé en chaine de caractéres
    sprintf(number,"%d",world->score);
    
    //on change l'affichage selon l'etat du jeu
    switch (world->state)  
    {
        case jeu: 
                                    //---affichage des entités---//
            apply_sprite(renderer,ressources->skin_ship,&(world->ship));
            apply_enemies(renderer,ressources->skin_ennemy,world->enemies);
            if(world->mboss.is_apply&&world->mboss.is_visible){
                 SDL_SetRenderDrawColor(renderer, 255, 0,0 ,255);
                 SDL_Rect life_gauge;
                 life_gauge.x=SCREEN_WIDTH-50;
                 life_gauge.y=SCREEN_HEIGHT/2;
                 life_gauge.w=20;
                 life_gauge.h=-SCREEN_HEIGHT/3+(10-world->mboss.life_points)*SCREEN_HEIGHT/30; 
                 SDL_RenderFillRect(renderer,&life_gauge);
                if(world->mboss.direction==1){
                    apply_sprite(renderer,ressources->mini_boss_D,&(world->mboss));
                }
                if(world->mboss.direction==-1){
                    apply_sprite(renderer,ressources->mini_boss_G,&(world->mboss));
                }
            }
            //Si le missile est appliqué dans le jeu on doit l'afficher
            if(world->missile.is_apply){ 

                apply_sprite(renderer,ressources->missile,&world->missile);

            }
            apply_sprite(renderer,ressources->missile_boss,&world->missile_mboss);
                                    //---affichge des textes---//
            apply_text(renderer,0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/6,40, "score;",ressources->font);
            apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,ressources->font);
                                    //---affichage des animations---//
            display_life(renderer,ressources,world); //on affiche les vies
            draw_animation(world,ressources,renderer); //on affiche la liste des explosions
                                    //---gestion du son---//
            if(world->playable||!Mix_Playing(0)){   //lorsque qu'on passe sur le jeu la musique doit être changé 
                play_music(0,ressources->sound.game_theme,0); //et on lance la musique du jeu
                world->playable=0;

            }
            break;
    case gagnant:
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"congratulation ! ",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/3,SCREEN_HEIGHT/2-SCREEN_HEIGHT/8,SCREEN_WIDTH/6,40, "score;",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/3 + SCREEN_WIDTH/6 ,SCREEN_HEIGHT/2-SCREEN_HEIGHT/8,SCREEN_WIDTH/15,40,number,ressources->font);
        break;
    case perdu:
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"You Lose ! ",ressources->font);
        apply_text(renderer,0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/6,40, "score;",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,ressources->font);
        break;
    case fin:
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"Game Over ! ",ressources->font);
        apply_text(renderer,0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/6,40, "score;",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,ressources->font);
        break;
    case menu: 
        apply_texture(ressources->solo_menu,renderer,SCREEN_WIDTH/3,SCREEN_HEIGHT/2+15);
        apply_texture(ressources->highscore_menu,renderer,SCREEN_WIDTH/6,SCREEN_HEIGHT/2+60);
        apply_texture(ressources->quitter_menu,renderer,SCREEN_WIDTH/4,SCREEN_HEIGHT/2+110);
        display_selection_zone(SCREEN_WIDTH/6-10,SCREEN_HEIGHT/2+world->menu_courant*45,SCREEN_WIDTH/2+65,50,renderer);
        apply_texture(ressources->menu_sprite,renderer,world->x_logo-SCREEN_WIDTH/4,SCREEN_HEIGHT/5);
        if(world->playable && !Mix_Playing(0)){ //on ne joue que la première fois qu'on arrive dans le jeu
        play_music(0,ressources->sound.menu_theme,0); //on lance la musique du menu
        }
        break;
    }    
    // on met à jour l'écran
    update_screen(renderer);
}
/**
 * @brief crée un rectangle non rempli au coordonnées souhaité
 * 
 * @param x le x du point en haut à gauche du rectangle
 * @param y le y du point en haut à gauche du rectangle
 * @param w la largeur du rectangle
 * @param h la hauteur du rectangle
 * @param renderer 
 */
void display_selection_zone(int x, int y, int w, int h,SDL_Renderer *renderer){
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;
    r1.x = x;   r1.y = y;   r1.w = w;   r1.h = 5; //les coordonées du 1er rectangle 
    r2.x = x;   r2.y = y+5; r2.h = h;   r2.w = 5; //les coordonées du 2ème rectangle
    r3.x = x+w; r3.y = y;   r3.w = 5;   r3.h = h+5; //les coordonées du 3ème rectangle
    r4.x = x;   r4.y = y+h; r4.w = w;   r4.h = 5; //les coordonées du 4ème rectangle

    // choix de la couleur
    SDL_SetRenderDrawColor(renderer, 228, 226,226 ,255);

    // Rendu de chaque rectangle 
    SDL_RenderFillRect(renderer, &r1 ); 
    SDL_RenderFillRect(renderer, &r2 );
    SDL_RenderFillRect(renderer, &r3 );
    SDL_RenderFillRect(renderer, &r4 );
}

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param ressources les ressources
*/
void apply_background(SDL_Renderer *renderer, ressources_t *ressources){
    if(ressources->background != NULL){
      apply_texture(ressources->background, renderer, 0, 0);
    }
}
/**
 * @brief affiche les texture des ennemies selon leur position
 * @param renderer le renderer 
 * @param texture la texture de l'entité
 * @param sprite l'entité 
 */
void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]){
    for(int i = 0; i<NB_ENEMIES;i++){
        apply_sprite(renderer,texture[i],&(sprite[i]));
    }
}


/**
 * @brief on affiche les vie selon le nombre de vies restantes
 * 
 * @param renderer 
 * @param ressources 
 * @param world 
 */
void display_life(SDL_Renderer *renderer,ressources_t* ressources,world_t* world){
    int i;
    //on affiche d'abord les coeurs pleins
    for(i=0;i<world->life;i++){
        apply_texture(ressources->coeur_plein,renderer,0,SCREEN_HEIGHT/4+i*20);
    }
    //puis les coeurs vides
    for(i=world->life;i<LIFE_NUMBER;i++){
        apply_texture(ressources->coeur_vide,renderer,0,SCREEN_HEIGHT/4+i*20);
    }
}
/**
 * @brief affiche les animations des explosion sur les ennemis morts
 * 
 * @param world le monde 
 * @param ressources la texture de l'explosion
 * @param renderer le moteur de rendu
 */
void draw_animation(world_t* world,ressources_t* ressources,SDL_Renderer* renderer){
    int i;
    //pour chaque explosion
    for (i=0; i<world->explosion_counter;i++){
        if(world->explosion[i].frame_timer<=0){ //si le temps d'attente est atteint
            world->explosion[i].frame_timer=TIMER_BETWEEN_2_FRAMES; //on le réinitialise
            world->explosion[i].frame_number++; //et on passe à la frame suivante
        
        int w;
        SDL_QueryTexture(ressources->explosion,NULL,NULL,&w,NULL);
            if(world->explosion[i].frame_number>=w/world->explosion[i].w){ //si on atteint la dernière frame ou qu'on la dépassé 
                world->explosion[i]=world->explosion[world->explosion_counter-1]; //on remplace par une explosion non modifié
                world->explosion_counter--; //on réduit le nombre d'explosion
                return;
            }
        }
        else{
            world->explosion[i].frame_timer--; //sinon on décremente le compte à rebours;
        }
    SDL_Rect SRC; //zone de capture dans la texture
    SDL_Rect DEST; //zone de rendu 
    DEST.x=world->explosion[i].x;
    DEST.y=world->explosion[i].y;
    DEST.h=world->explosion[i].h;
    DEST.w=world->explosion[i].w;
    /*chaque zone de la texture fais la même largeur donc,
     afin de trouver le x de la zone à capturer, 
     on multiplie la largeur d'une zone par le numéro de la frame
    */
    SRC.x=world->explosion[i].frame_number * world->explosion[i].w; 
    SRC.y=0;
    SRC.h=world->explosion[i].h;
    SRC.w=world->explosion[i].w;
    //on affiche la sélection dans la zone de l'ennemi
    SDL_RenderCopy(renderer,ressources->explosion,&SRC,&DEST);
}
}
