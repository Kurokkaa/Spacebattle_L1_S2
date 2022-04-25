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


void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    
    textures->skin_ship = load_image("ressources/spaceship.bmp",renderer);

    textures->skin_ennemy = load_image("ressources/enemy.bmp",renderer);

    textures->missile = load_image("ressources/missile.bmp", renderer);
}
void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
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
    
    //on vide le renderer
    clear_renderer(renderer);

    
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer,textures->skin_ship,&(world->ship));
    apply_sprite(renderer,textures->skin_ennemy,&(world->ennemi));
    if(world->missile.is_apply){
    apply_sprite(renderer,textures->missile,&world->missile);
   }

    
    
    // on met à jour l'écran
    update_screen(renderer);
}

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}
void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}

