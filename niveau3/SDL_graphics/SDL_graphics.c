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
 * 
 * @param renderer le renderer 
 * @param texture la texture de l'entité
 * @param sprite l'entité
 */
void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite){
    if(sprite->is_visible==1){ //si le sprite est visible on l'applique sinon 
        SDL_Rect dst = {0, 0, 0, 0};
    
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
        dst.x = sprite->x; dst.y=sprite->y;
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
    //si le vaisseau n'est ni affiché ni appliqué la texture est nettoyé
    else if(!(sprite->is_apply)){ //s'il ne doit pas être appliqué on nettoie
        clean_texture(texture);
    }
}

/**
 * @brief met à jour le renderer
 * 
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
        apply_sprite(renderer,ressources->skin_ship,&(world->ship));
        apply_enemies(renderer,ressources->skin_ennemy,world->enemies);
        if(world->missile.is_apply){
            apply_sprite(renderer,ressources->missile,&world->missile);
         }
        apply_text(renderer,0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/6,40, "score;",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,ressources->font);
        display_life(renderer,ressources,world);
        
        if(world->playable){
        stop_music(0);
        play_music(0,ressources->sound.game_theme,0);
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
        apply_text(renderer,SCREEN_WIDTH/3,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,60,"Jouer",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/3,SCREEN_HEIGHT/2+50,SCREEN_WIDTH/3,60,"Highscore",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/3,SCREEN_HEIGHT/2+100,SCREEN_WIDTH/3,60,"Quitter",ressources->font);
        display_selection_zone(SCREEN_WIDTH/3-10,SCREEN_HEIGHT/2+world->menu_courant*50,SCREEN_WIDTH/3+20,50,renderer);
        apply_texture(ressources->menu_sprite,renderer,world->x_logo-SCREEN_WIDTH/4,SCREEN_HEIGHT/5);
        if(world->playable && !Mix_Playing(0)){
        play_music(0,ressources->sound.menu_theme,0);
        
        }
        break;
    }    
    // on met à jour l'écran
    update_screen(renderer);
}
void display_selection_zone(int x, int y, int w, int h,SDL_Renderer *renderer){
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;
    r1.x = x;   r1.y = y;   r1.w = w;   r1.h = 5;
    r2.x = x;   r2.y = y+5; r2.h = h;   r2.w = 5;   
    r3.x = x+w; r3.y = y;   r3.w = 5;   r3.h = h+5;
    r4.x = x;   r4.y = y+h; r4.w = w;   r4.h = 5;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 228, 226,226 ,255);

    // Render rect
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
 * 
 * @param renderer le renderer 
 * @param texture la texture de l'entité
 * @param sprite l'entité 
 */
void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]){
    for(int i = 0; i<NB_ENEMIES;i++){
        apply_sprite(renderer,texture[i],&(sprite[i]));
    }
}



void display_life(SDL_Renderer *renderer,ressources_t* ressources,world_t* world){
    int i;
    for(i=0;i<world->life;i++){
        apply_texture(ressources->coeur_plein,renderer,0,SCREEN_HEIGHT/4+i*20);
    }
    for(i=world->life;i<LIFE_NUMBER;i++){
        apply_texture(ressources->coeur_vide,renderer,0,SCREEN_HEIGHT/4+i*20);
    }
}