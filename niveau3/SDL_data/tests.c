#include "SDL_data.h"
#include "../struct/struct.h"
#include "../constantes/constantes.h"cd


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
    left_limit(&sprite.x);
    printf("gauche x=%d \n",sprite.x);
    sprite.x=SCREEN_WIDTH;
    printf("x=%d, ",sprite.x);
    right_limit(&sprite.x);
    printf("droite x=%d \n",sprite.x);
}

void test_vertical_limit_param(sprite_t* sprite){
    printf("y=%d, ",sprite->y);
    bottom_limit(sprite);
    printf("y=%d \n",sprite->y);
}
void test_vertical_limit(){
    sprite_t sprite;
    for(int i=SCREEN_HEIGHT-SHIP_SIZE;i<SCREEN_HEIGHT;i++){
        sprite.y=i;
        printf("%d ",sprite.y);
        test_vertical_limit_param(&sprite);
    }
}

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

void test_handle_sprites_collision_param(sprite_t *sp2, sprite_t *sp1){
    printf("Vsp1 = %d, Vsp2= %d \n",sp1->v, sp2->v);
    handle_sprites_collision(sp1,sp2);
}

void test_handle_sprites_collision(){
    sprite_t sp1;
    sprite_t sp2;
    sp1.x=0;
    sp1.y=0; 
    sp2.x=0;
    sp2.y=0;
    test_handle_sprites_collision_param(&sp1,&sp2);
    sp2.x=0;
    sp2.y=SCREEN_HEIGHT;
    test_handle_sprites_collision_param(&sp1,&sp2);

}

int WinMain( int argc, char* args[] ){
    test_init_sprite();
    test_ship_screen_limit();
    test_vertical_limit();
}
