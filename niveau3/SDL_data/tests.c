#include "SDL_data.h"
#include "../constantes/constantes.h"


void test_init_sprite_param(sprite_t *sprite, int x, int y, int w, int h, int v){
    init_sprite(sprite,x,y,w,h,v);
    print_sprite(sprite);
}
void test_init_sprite(){
    int i;
    sprite_t sprite;
    for(i=0;i<20;i++){
        test_init_sprite_param(&sprite,i,i,i,i,i);
}
}
void test_ship_screen_limit(){
    sprite_t sprite;
    sprite.x=-15;
    printf("x=%d, ",sprite.x);
    left_limit(&(sprite));
    printf("gauche x=%d \n",sprite.x);
    sprite.x=SCREEN_WIDTH;
    printf("x=%d, ",sprite.x);
    right_limit(&(sprite));
    printf("droite x=%d \n",sprite.x);
}

/*void test_vertical_limit_param(sprite_t* sprite){
    printf("y=%d, ",sprite->y);
    bottom_limit(sprite);
    printf("y=%d \n",sprite->y);
}
void test_vertical_limit(){
    sprite_t sprite;
    for(int i=SCREEN_HEIGHT;i<=SCREEN_HEIGHT+SHIP_SIZE;i++){
        sprite.y=i;
        printf("%d ",sprite.y);
        test_vertical_limit_param(&sprite);
    }
}*/

void test_sprites_collide_param(sprite_t* sp1, sprite_t* sp2 ){
    printf("%s \n",sprites_collide(sp1,sp2)==1 ? "il y a collision" : "il n'y a pas collsion");
}

void test_sprites_collide(){
    sprite_t sp1;
    sprite_t sp2;
    sp1.x=0;
    sp1.y=0; 
    sp2.x=0;
    sp2.y=0;
    test_sprites_collide_param(&sp1,&sp2);
    sp2.x=0;
    sp2.y=SCREEN_HEIGHT;
    test_sprites_collide_param(&sp1,&sp2);

}

void test_handle_sprites_collision_param(sprite_t *sp2, sprite_t *sp1, world_t* world){
    printf("Vsp1 = %d, Vsp2= %d \n",sp1->v, sp2->v);
    handle_sprites_collision(sp1,sp2,world);
}

void test_handle_sprites_collision(){
    sprite_t sp1;
    sprite_t sp2;
    world_t world;
    sp1.x=0;
    sp1.y=0; 
    sp2.x=0;
    sp2.y=0;
    test_handle_sprites_collision_param(&sp1,&sp2,&world);
    sp2.x=0;
    sp2.y=SCREEN_HEIGHT;
    test_handle_sprites_collision_param(&sp1,&sp2,&world);

}
void test_init_enemies_param(world_t* world){
    init_ennemies(world);
    int i; 
    for(i=0;i<NB_ENEMIES;i++){
        printf("vaisseau %d \n",i);
        printf("x:%d \n",world->enemies[i].x);
        printf("y:%d \n",world->enemies[i].y);
        printf("w:%d \n",world->enemies[i].w);
        printf("v:%d \n",world->enemies[i].v);
        printf("h:%d \n",world->enemies[i].h);
    }
}
void test_init_enemies(){
    world_t world;
    test_init_enemies_param(&world);
}
void test_update_enemies_param(world_t* world){
    int i;
    for(i=0;i<NB_ENEMIES;i++){
        printf("vaisseau N %d",i);
        printf("\n");
        printf("y avant:%d",world->enemies[i].y);
        printf("\n");
    }
    printf("\n");
    update_ennemies(world);
    for(i=0;i<NB_ENEMIES;i++){
        printf("vaisseau N %d",i);
        printf("\n");
        printf("y apres: %d",world->enemies[i].y);
        printf("\n");
    }
    
}
void test_update_enemies(){
    world_t world;
    int i;
    init_ennemies(&world);
    for(i=0;i<NB_ENEMIES;i++){
        printf("essai %d \n",i);
        test_update_enemies_param(&world);
        printf("\n");
    }
}
int WinMain( int argc, char* args[] ){
    world_t world;

    test_init_sprite();
    test_ship_screen_limit();
    //test_vertical_limit();
    test_init_enemies();
    test_update_enemies();
}
