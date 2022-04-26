/**
 * \file SDL_data.c
 * \brief Module graphique du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */
#include "SDL_graphics.h"



void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->skin_ship);
    clean_texture(textures->skin_ennemy);
    clean_texture(textures->missile);
}

void init_textures_enemies(SDL_Renderer *renderer, textures_t *textures){
    for(int i = 0;i<NB_ENEMIES;i++){
        textures->skin_ennemy[i]=load_image("ressources/enemy.bmp",renderer);
    }
}



void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    
    textures->skin_ship = load_image("ressources/spaceship.bmp",renderer);

    init_textures_enemies(renderer,textures);

    textures->missile = load_image("ressources/missile.bmp", renderer);
    
    textures->font  = load_font("ressources/arial.ttf",14);

    textures->menu_sprite = load_image("ressources/spacebattle.bmp",renderer);
}
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
    clean_font(textures->font);
}
void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite){
    if(sprite->is_visible==1){ //si le sprite est visible on l'applique sinon 
        SDL_Rect dst = {0, 0, 0, 0};
    
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
        dst.x = sprite->x; dst.y=sprite->y;
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
    else{
        if(!(sprite->is_apply)){ //s'il ne doit pas être appliqué on nettoie
        clean_texture(texture);
    }
}
}
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    char number[15];
    //on vide le renderer
    clear_renderer(renderer);
    apply_background(renderer,textures);
    sprintf(number,"%d",world->score);
    switch (world->state)
     
    {
    case jeu:
        
       
        apply_sprite(renderer,textures->skin_ship,&(world->ship));
        apply_enemies(renderer,textures->skin_ennemy,world->enemies);
        if(world->missile.is_apply){
            apply_sprite(renderer,textures->missile,&world->missile);
         }
        apply_text(renderer,0,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/6,40, "score;",textures->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,textures->font);
        break;
    case gagnant:
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"congratulation ! ",textures->font);
        apply_text(renderer,SCREEN_WIDTH/3,SCREEN_HEIGHT/2-SCREEN_HEIGHT/8,SCREEN_WIDTH/6,40, "score;",textures->font);
        apply_text(renderer,SCREEN_WIDTH/3 + SCREEN_WIDTH/6 ,SCREEN_HEIGHT/2-SCREEN_HEIGHT/8,SCREEN_WIDTH/15,40,number,textures->font);
        break;
    case perdu:
        printf("%s",number);
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"You Lose ! ",textures->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,textures->font);
        break;
    case fin:
        
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"Game Over ! ",textures->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,textures->font);
    case menu:
        apply_texture(textures->menu_sprite,renderer,SCREEN_WIDTH/8,SCREEN_HEIGHT/5);
        apply_text(renderer,SCREEN_WIDTH/4,SCREEN_HEIGHT/5+100,SCREEN_WIDTH/3,50,"PRESS SPACE TO START ",textures->font);
        
        break;
    default:
        break;
    }
    
    //application des textures dans le renderer
   
    
   
    
    
    
    
    
    // on met à jour l'écran
    update_screen(renderer);
}


void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}

void apply_enemies(SDL_Renderer* renderer, SDL_Texture* texture[], sprite_t sprite[]){
    for(int i = 0; i<NB_ENEMIES;i++){
        apply_sprite(renderer,texture[i],&(sprite[i]));
    }
}

