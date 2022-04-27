/**
 * \file SDL_data.c
 * \brief Module graphique du jeu
 * \author CHAPUSOT Alexis et ANDRE Jeffrey
 * \version 1.0
 * \date 7 AVRIL 2022
 */
#include "SDL_graphics.h"


/**
 * \brief La fonction nettoie les textures
 * \param ressources les ressources
*/
void clean_textures(ressources_t *ressources){
    clean_texture(ressources->background);
    clean_texture(ressources->skin_ship);
    clean_texture(ressources->skin_ennemy);
    clean_texture(ressources->missile);
}
/**
 * @brief 
 * 
 * @param renderer le renderer
 * @param ressources les ressources
 */
void init_textures_enemies(SDL_Renderer *renderer, ressources_t *ressources){
    for(int i = 0;i<NB_ENEMIES;i++){
        ressources->skin_ennemy[i]=load_image("ressources/enemy.bmp",renderer);
    }
}


/**
 * @brief charge les images liées au textures 
 * 
 * @param renderer le renderer
 * @param ressources les ressources
 */
void init_textures(SDL_Renderer *renderer, ressources_t *ressources){
    ressources->background = load_image( "ressources/space-background.bmp",renderer);
    
    ressources->skin_ship = load_image("ressources/spaceship.bmp",renderer);

    init_textures_enemies(renderer,ressources);

    ressources->missile = load_image("ressources/missile.bmp", renderer);
    
    ressources->font  = load_font("ressources/arial.ttf",14);

    ressources->menu_sprite = load_image("ressources/spacebattle.bmp",renderer);
}
/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *ressources, world_t * world){
    clean_data(world);
    clean_textures(ressources);
    clean_sdl(renderer,window);
    clean_font(ressources->font);
}
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
    else{
        if(!(sprite->is_apply)){ //s'il ne doit pas être appliqué on nettoie
        clean_texture(texture);
    }
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
    char number[15];
    //on vide le renderer
    clear_renderer(renderer);
    apply_background(renderer,ressources);
    //le score est transformé en chaine de caractéres
    sprintf(number,"%d",world->score);
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
        break;
    case gagnant:
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"congratulation ! ",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/3,SCREEN_HEIGHT/2-SCREEN_HEIGHT/8,SCREEN_WIDTH/6,40, "score;",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/3 + SCREEN_WIDTH/6 ,SCREEN_HEIGHT/2-SCREEN_HEIGHT/8,SCREEN_WIDTH/15,40,number,ressources->font);
        break;
    case perdu:
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"You Lose ! ",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,ressources->font);
        break;
    case fin:
        apply_text(renderer,SCREEN_WIDTH/2-SCREEN_WIDTH/7,SCREEN_HEIGHT/2,SCREEN_WIDTH/3,40,"Game Over ! ",ressources->font);
        apply_text(renderer,SCREEN_WIDTH/6+2,3*SCREEN_HEIGHT/4,SCREEN_WIDTH/15,40,number,ressources->font);
        break;
    case menu:
        apply_texture(ressources->menu_sprite,renderer,SCREEN_WIDTH/8,SCREEN_HEIGHT/5);
        apply_text(renderer,SCREEN_WIDTH/4,SCREEN_HEIGHT/5+100,SCREEN_WIDTH/3,50,"PRESS SPACE TO START ",ressources->font);
        break;
    }    
    // on met à jour l'écran
    update_screen(renderer);
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

/**
 * @brief initialise les différents module
 * 
 * @param window 
 * @param renderer 
 * @param ressources 
 * @param world 
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_ttf();
    init_textures(*renderer,ressources);
}