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
    init_sprite(&(world->ship), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-3*SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, 0);
    init_boss(&(world->mboss),0,-30,MBOSS_SIZE,MBOSS_SIZE-10,1);
    init_boss(&(world->boss),0,0,BOSS_SIZE,BOSS_SIZE,0);
    init_sprite(&world->missile_mboss,30,MBOSS_SIZE,MISSILE_SIZE,MBOSS_MISSILE_SIZE,MISSILE_SPEED); 
    set_invisible(&(world->missile));
    set_invisible(&(world->missile_mboss));
             /*---------------------------------------------------------------------------------------------*/
    //on n'est pas à la fin du jeu
    world->gameover = 0;   
    world->nb_enemies_left = NB_ENEMIES; //il reste tous les ennemies au début
    world->nb_enemies_survived = 0;      
    world->score = 0;
    world->state = menu;                 //on ne lance pas le jeu au démarrage de l'application mais le menu
    world->timer_end = 0;                //compte à rebours de la fermeture de la fenêtre
    world->life=LIFE_NUMBER;
    world->menu_courant = 0;             //le premier bouton du menu est sélectionné
    world->playable = 1;
    world->mboss_shoot_cooldown = 0;
    world->pause = 0;
    world->explosion_counter = 0;
    world->pseudo[0]='\0';
    read_highscore(world);

}


/**
 * @brief afficher les données d'un sprite
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
    if(get_y(&(world->missile)) <= 0 || !get_is_apply(&(world->missile)) ){ 
        //on le cache afin de la replacer
        set_apply(&(world->missile));
        set_invisible(&(world->missile));  
    }
}
/**
 * @brief retourne la vague actuelle du jeu
 * @param world le monde du jeu
 */
void set_wave(world_t* world){
    world->wave = floor(100*(NB_ENEMIES - world->nb_enemies_left)/NB_ENEMIES);
    
    
}
/**
 * @brief retourne 0,1 ou 2 selon la vague actuelle
 * 
 * @param world 
 * @return int 0,1 ou 2
 */
int check_wave(world_t* world){
    if (world->wave <= 0 && world->wave <  50 || world->wave > 50 && world->wave < 100){
        return 0;               //pas de boss
    }
    if (world->wave == 50){
        return 1;           //mini boss
    }
    if (world->wave >= 100){
        return 2;           
    }      //boss final
}
/**
 * @brief initialise le sprite du boss
 * @param boss le sprite du boss
 * @param x le x de départ
 * @param y le y de départ
 * @param w la largeur du boss
 * @param h la hauteur du boss
 * @param v la vitesse horizontale du boss
 */
void init_boss(sprite_t* boss,int x,int y,int w, int h,int v){
    init_sprite(boss,x,y,w,h,v);
    set_invisible(boss); //il est invisible au départ
    boss->life_points = NB_BOSS_LIFE;
    boss->direction = 1; //sens de déplacement du mini boss
}
/**
 * @brief gere le missile du boss intermédiaire
 * @param world 
 */
void move_missile_mboss(world_t* world){
    //si le projectile du boss intermédiaire est visible 
    if(get_is_visible(&(world->missile_mboss))){
    //il est déplacé
    set_y(&(world->missile_mboss),get_y(&(world->missile_mboss)) + MISSILE_SPEED); /*!< Si le missile est visible, c'est qu'il doit se déplacer */
    }
    //sinon il est placé au niveau de la tête du boss
    else{
        //selon qu'il soit à droite ou gauche, le missile n'est pas placé au même endroit
        if(world->mboss.direction == 1){
        set_x(&(world->missile_mboss),get_x(&(world->mboss)) + 120 - MBOSS_MISSILE_SIZE / 2); /*!< sinon il doit être placer au dessus du vaisseau*/
        set_y(&(world->missile_mboss),get_y(&(world->mboss)) + MBOSS_SIZE);
        }
        else{
        set_x(&(world->missile_mboss),get_x(&(world->mboss)) + 16 - MBOSS_MISSILE_SIZE / 2); /*!< sinon il doit être placer au dessus du vaisseau*/
        set_y(&(world->missile_mboss),get_y(&(world->mboss)) + MBOSS_SIZE);
        }
    }
}
/**
 * @brief gére le missile du boss
 * 
 * @param world 
 */
void replace_missile_mboss(world_t* world){
    //
    if(get_y(&(world->missile_mboss)) >= SCREEN_HEIGHT){ 
        //on le cache afin de la replacer
        set_invisible(&(world->missile_mboss));  
    }
}
/**
 * @brief gére le déplacement du boss intermédiaire
 * 
 * @param world 
 */
void move_mboss(world_t* world){
    //si le boss dépasse à gauche il fait demi-tour
    if(world->mboss.x <= -MBOSS_SIZE){
        world->mboss.direction=1;
    }
    if(world->mboss.x>=SCREEN_WIDTH){
        world->mboss.direction = -1;
    }
    if(world->mboss.direction==1){
        world->mboss.x += world->mboss.v;
    } 
    else{
        world->mboss.x -= world->mboss.v;
    }
}
void handle_shot_mboss(world_t* world){
    if(world->mboss_shoot_cooldown<=0){
        world->mboss_shoot_cooldown = 50;
        int shoot_chance = generate_number(1,101);
        if(shoot_chance>=1 && shoot_chance <= 80 && world->mboss.x >= 0 && world->mboss.x <= SCREEN_WIDTH-MBOSS_SIZE){
            set_visible(&world->missile_mboss);
        }
    }
    else{
        world->mboss_shoot_cooldown--;
    }
}
void handle_mboss_collision(world_t* world){
     if(sprites_collide(&(world->missile),&(world->mboss))){
        set_not_apply(&world->missile);
        set_invisible(&world->missile);
        if(world->mboss.life_points==1){
            set_not_apply(&world->mboss);
            set_invisible(&world->mboss);
            set_not_apply(&world->missile_mboss);
            set_invisible(&world->missile_mboss);
            add_animation(world->mboss.x,world->mboss.y,world);
        }   
        world->mboss.life_points--;
        //si le boss est mort, on l'enlève du jeu
            
    }
    //si le missile du boss nous touche on ne meurt pas mais on perd une vie
    if(sprites_collide(&world->missile_mboss,&world->ship)){
        world->life--;
        set_invisible(&world->missile_mboss);
    }
}
/**
 * @brief gestion du boss intermédiaire
 * @param world 
 */
void handle_mboss(world_t* world){
    set_visible(&world->mboss);
    //on gére le déplacement du boss
    move_mboss(world);
    // on gére le missile du boss
    move_missile_mboss(world);
    replace_missile_mboss(world);
    handle_mboss_collision(world);
    handle_shot_mboss(world);   
}
void update_waves_boss(world_t* world){
    int i;
    for(i = 0 ; i<NB_BOSS_SBIRES;i++){
        world->sbires[i].y+=world->sbires[i].v;
    }
}
void handle_boss_collision(world_t* world){
    if(sprites_collide(&(world->missile),&(world->boss))){
        set_not_apply(&world->missile);
        set_invisible(&world->missile);
        world->boss.life_points--;
        if(world->boss.life_points==0){
            printf("le boss est mort");
            set_not_apply(&(world->boss));
            set_invisible(&(world->boss));
            add_animation(world->mboss.x,world->mboss.y,world);
            for(int i; i<NB_BOSS_SBIRES;i++){
                set_invisible(&world->sbires[i]);
            }
        }   
        //si le boss est mort, on l'enlève du jeu
            
    }
}
void handle_sbires_collision(world_t* world, audio_t* audio){
    for(int i; i<NB_BOSS_SBIRES;i++){
        if(world->sbires[i].is_apply&&world->sbires[i].y>-SHIP_SIZE/2){
            handle_sprites_collision(&(world->ship),&(world->sbires[i]),world,audio);
            if(world->missile.is_visible){
                handle_sprites_collision(&(world->missile),&(world->sbires[i]),world,audio);
            }
        }
    }
}
void handle_boss(world_t* world,audio_t* audio){
    update_waves_boss(world); //gère la génération des ennemis
    handle_boss_collision(world);
    handle_sbires_collision(world,audio);
}
/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world,audio_t* audio){
    int i;
    int replace_coeff=0;
    switch (world->state)
    {
        case menu:
            //si le logo est à la limite on le bloque
            if(world->x_logo >= SCREEN_HEIGHT/5-10){ 
                world->x_logo = SCREEN_HEIGHT/5-10;
            }
            //Sinon on le bouge
            else world->x_logo += 3;
            break;
        case jeu:
            if(!world->pause){
            //la vague actuelle est enregistré
                set_wave(world);
                if(!world->ship.is_apply){
                    play_music(2,audio->death,0);
                }
            //si c'est la vague du boss
                if(check_wave(world) == 1){
                //on replace les ennemies restant en haut de l'écran à l'apparition du boss
                    if(world->mboss.is_visible == 0){
                        for (i = 0; i<NB_ENEMIES; i++){
                             if(world->enemies[i].is_apply && world->enemies[i].is_visible){
                                 world->enemies[i].y = -(replace_coeff*VERTICAL_DIST)-SHIP_SIZE;
                                replace_coeff++;
                            }
                         
                        }
                        // le boss apparait
                        set_visible(&(world->mboss));
                }
                //on gére le boss que s'il est en vie 
                if(world->mboss.life_points <= 0){
                    update_ennemies(world);
                    handle_ennemies(world,audio);
                }
                else{
                handle_mboss(world);
                    }
                }
            if(check_wave(world)==2){
                if(world->boss.is_visible){
                handle_boss(world,audio);
                }
                set_visible(&world->boss);
            };
            if(check_wave(world) == 0){
                update_ennemies(world);
                handle_ennemies(world,audio);
            };
            replace_missile(world);
            move_missile(world);
            left_limit(&(world->ship));
            right_limit(&(world->ship));
            compute_game(world);
            
        }
            break;
        case perdu:
            if(!world->playable){
                play_music(0,audio->Game_over,0);
                world->playable = 1;
            }
        compute_game(world);
        break;
        case gagnant:
            compute_game(world);
            break;
        case fin:
            compute_game(world);
            break;
    } 
}

/**
 * @brief gère la position des ennemies
 * @param world le monde du jeu
 */
void handle_ennemies(world_t* world,audio_t* audio){
    //si le vaisseau n'a pas été détruit
    if(get_is_apply(&(world->ship))){
        //on vérifie les collision avec les ennemis
        for(int i = 0; i<NB_ENEMIES;i++){
            //si l'ennemi n'a pas été détruit on vérifie la collison
            if(get_is_apply(&(world->enemies[i]))&&world->enemies[i].y>-SHIP_SIZE/2){
                handle_sprites_collision(&(world->ship),&(world->enemies[i]),world,audio);
               
                //si le missile n'est pas visible il doit être ignoré
                if(get_is_visible(&(world->missile))){
                    handle_sprites_collision(&(world->missile),&(world->enemies[i]),world,audio);
                }
            }
            //si le vaisseau enemi est en dehors de l'ecran
            //il a survécu
            //et on le retire du jeu et on enleve une vie au joueur
            if(get_y(&(world->enemies[i])) >= SCREEN_HEIGHT && world->enemies[i].is_apply){
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
        set_x(&(world->missile),get_x(&(world->ship))+SHIP_SIZE/2-MISSILE_SIZE/2); 
        set_y(&(world->missile),get_y(&(world->ship))); 
    }
}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world,audio_t* audio){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
         //Si l'utilisateur a cliqué sur le X de la fenêtre
        switch(event->type){
            
            case SDL_QUIT:
                //On indique la fin du jeu
                world->gameover = 1;
                break;
            case SDL_TEXTINPUT:
                if(strlen(world->pseudo) < SIZE_PSEUDO_MAX){
                    strcat(world->pseudo,event->text.text);
                }
                break;
            case SDL_KEYDOWN:
                switch (world->state) //selon l'état du jeu les touches ne font pas la même action
                {
                case highscore:
                    switch (event->key.keysym.sym)
                    {
                    case SDLK_BACKSPACE:
                        world->state=menu;
                        break;
                    
                    }
                case saisie:
                    switch (event->key.keysym.sym)
                    {
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        if(strlen(world->pseudo) > 0){
                        world->state = jeu;
                        SDL_StopTextInput();
                        }
                        break;
                    
                    case SDLK_BACKSPACE:
                        if(strlen(world->pseudo)>0){
                            world->pseudo[strlen(world->pseudo) - 1] = '\0';
                        }
                        break;
                    }
                break;
                case menu:
                    switch (event->key.keysym.sym){
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            switch (world->menu_courant)
                            {
                            case 0:
                                SDL_StartTextInput();
                                world->state = saisie;
                                play_music(0,audio->game_theme,-1);
                                break;
                            case 1:
                                world->state = highscore;
                                break;
                            case 2:
                                world->gameover = 1;
                                break;
                            }
                            break;
                        case SDLK_DOWN:
                            play_music(1,audio->menu_select,0);
                            world->menu_courant++;
                            if(world->menu_courant > 2){
                                world->menu_courant = 0;
                            }
                            break;
                        case SDLK_UP:
                            play_music(1,audio->menu_select,0);
                            if(world->menu_courant == 0){
                                world->menu_courant = 2;
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
                        case SDLK_RIGHT:
                            set_x(&(world->ship),get_x(&world->ship)+10);
                            break;
                        case SDLK_LEFT:
                            set_x(&(world->ship),get_x(&world->ship)-10);
                            break;
                        case SDLK_SPACE:
                            if(get_is_visible(&(world->ship))){ // on peut tirer seulement si le vaisseau est visible
                                set_visible(&(world->missile));
                                if(!Mix_Playing(1) && get_y(&(world->missile))==get_y(&(world->ship))){
                                play_music(1,audio->missile_shot,0);
                                }
                            }
                            break;
                        case SDLK_ESCAPE:
                            world->pause = !world->pause;
                            break;
                    }
                break;
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
    set_apply(sprite);
    set_visible(sprite);
    set_x(sprite,x);
    set_y(sprite,y);
    set_w(sprite,w);
    set_h(sprite,h);
    set_v(sprite,v);   
}
/**
 * @brief la fonction bloque le vaisseau sur la gauche pour qu'il ne sorte pas de l'écran
 * @param sprite le vaisseau
 */
void left_limit(sprite_t* sprite){
    if(sprite->x <= 0){
        sprite->x = 0;
    }
}
/**
 * @brief la fonction bloque le vaisseau sur la droite pour qu'il ne sorte pas de l'écran
 * @param sprite le vaisseau
 */
void right_limit(sprite_t* sprite){
    //si la droite du sprite arrive au bord il est bloqué
    if(sprite->x >= SCREEN_WIDTH-SHIP_SIZE){
        sprite->x = SCREEN_WIDTH-SHIP_SIZE;
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
    int distance  = sqrt(distanceX * distanceX + distanceY * distanceY);
    return (distance <= sp1->w/2 + sp2->w/2); 
}
/**
 * @brief efface les sprites en cas de collision
 * @param sp2 
 * @param sp1 
 */
void handle_sprites_collision(sprite_t *sp1, sprite_t *sp2, world_t* world,audio_t* audio){
    if (sprites_collide(sp2,sp1)){
        sp1->is_visible = 0; 
        sp2->is_visible = 0;
        sp1->is_apply = 0;
        sp2->is_apply = 0;
        world->nb_enemies_left--;
        play_music(2,audio->enemy_destruction,0);
        world->score++;
        add_animation(sp2->x,sp2->y,world);     
    }
}
/**
 * @brief génère un nombre entre a et b
 * @param a 
 * @param b 
 * @return int un nombre aléatoire
 */
int generate_number(int a, int b){
    return rand() % (b-a) + a;
    }
/**
 * @brief initialise les ennemies 
 * @param world 
 */   
void init_ennemies(world_t* world){
    int i;
    int x;
    int y;
    world->enemies=(sprite_t*)malloc(sizeof(sprite_t)*NB_ENEMIES);
    world->sbires =(sprite_t*)malloc(sizeof(sprite_t)*NB_BOSS_SBIRES);
    for(i = 0; i < NB_ENEMIES; i++){
        x = generate_number(0,SCREEN_WIDTH-SHIP_SIZE);
        y = -(SHIP_SIZE + i* VERTICAL_DIST);
        init_sprite(&(world->enemies[i]),x,y,SHIP_SIZE,SHIP_SIZE,ENEMY_SPEED);
    }
    for(i = 0; i < NB_ENEMIES; i++){
        x = generate_number(0,SCREEN_WIDTH-SHIP_SIZE);
        y = -(SHIP_SIZE + i* VERTICAL_DIST);
        init_sprite(&(world->sbires[i]),x,y,SHIP_SIZE,SHIP_SIZE,BOSS_SBIRES_SPEED);
    }
}
/**
 * @brief mise à jour de la position des ennnemies
 * 
 * @param world 
 */
void update_ennemies(world_t* world){
    int i;
    for(i = 0; i < NB_ENEMIES; i++){
        world->enemies[i].y += world->enemies[i].v;
    }
}
/**
 * @brief compteur du nombre de vies
 *
 * @param world
 */
void lose_life(world_t* world){
    world->life -= 1;
}
/**
 * @brief retourne 1 si l'etat = perdu,gagnant ou fin
 * @param world 
 */
int CheckState(world_t* world){
    return world->state == perdu || world->state == gagnant || world->state == fin;
}
/**
 * @brief returne 1 si le nombre de vie égal à 0 sinon 0
 * @param world 
 * @return int 
 */
int CheckLife(world_t* world){
    return world->life == 0;
}
/**
 * @brief retourne 1 si le nombre d'ennemi restant = 0
 * @param world 
 * @return int 
 */
int CheckEnemiesLeft(world_t* world){
    return world->nb_enemies_left == 0;
}

/**
 * @brief retourne 1 si le nombre d'ennemi qui à survécu = 0
 * @param world 
 * @return int 
 */
int CheckEnemiesSurvived(world_t* world){
    return world->nb_enemies_survived == 0;
}
void assign_new_highscore(world_t* world, highscore_t highscore_array[], int size){
    
    highscore_t tmp;
    int tableau_trie;
    int k=1;
    for(int i = size-1; i > 0;i--){
        tableau_trie=1;
        for(int j = 0; j < i; j++){
            if(atoi(highscore_array[j+1].score) > atoi(highscore_array[j].score)){
                tableau_trie=0;
                tmp=highscore_array[j+1];
                highscore_array[j+1] = highscore_array[j];
                highscore_array[j] = tmp;
            }
            if(tableau_trie){
                i=0;
            }
        }
    }
    
    
    for(int i = 0; i<world->nb_player; i++){
        world->rank[i] = highscore_array[i];
    }
    
    
}
/**
 * @brief
 * @param world 
 */
void read_highscore(world_t* world){
    int locations = 0;
    int j = 0;
    int linecpt = 0; //nombre de cellule du tableau
    int i;
    int k = 0;
    char* File_name = "SDL_data/Highscore_board.txt";
    struct stat stat_file;
    FILE* file = fopen(File_name,"r"); //ouverture en mode lecture
    if(file==NULL){
        printf("erreur");
    }
    stat(File_name, &stat_file);
    long long size = stat_file.st_size;
    char score[size+1];
    fread(score,1,size,file);
    score[size]='\0';
    for(i = 0; i < size; i++){
        if(score[i] == '\n'){
        linecpt++;
        }
    }
    int array_size=linecpt/2;
    if(array_size<10){
        world->nb_player=array_size;
    }
    else{
        world->nb_player=10;
    }
    printf("%d",world->nb_player);
    highscore_t* highscore_table = malloc(sizeof(highscore_t)*array_size);
   for(i = 0; i < size; i++){
        if(score[i]!='\n'){
         if(locations == 0){
               highscore_table[k].pseudo[j]=score[i];
               j++;
            }
            else{
                highscore_table[k].score[j]=score[i];
                j++;
            }
        }
        else{
            if(locations){
                k++; 
            }
            locations=1-locations;
            j=0;
        }
    }
    fclose(file);
}
    



void write_new_best_score(world_t* world){
    char score[15];
    char record[SIZE_PSEUDO_MAX+16];
    sprintf(score,"%d", world->score);
    char* FileName = "SDL_data/highscore_board.txt";
    FILE* File = fopen(FileName, "a");
    if(File == NULL){
        printf("Erreur : %s",strerror(errno));
    }
    strcat(record, world->pseudo);
    strcat(record,"\n");
    strcat(record, score);
    strcat(record, "\n");
    fwrite(record,1,strlen(record), File);
}
/**
 * @brief met un terme au jeu et enregiste le nouveau score
 * @param world 
 */
void conclude_game(world_t* world){
    world->gameover = 1;
    if(world->score!=0){
    write_new_best_score(world);
    }
}
/**
 * @brief change l'état de la partie en fonction de la situation
 * @param world 
 */
void compute_game(world_t* world){
    if(world->timer_end == TIME_ENDING){
            conclude_game(world);
             
        }
    else if(CheckState(world)){   
            //si on est en fin de partie le compte à rebours progresse
            world->timer_end++;
    }
    else{
        if(CheckLife(world) || !get_is_visible(&(world->ship))){
            //la partie est perdu
                world->score = 0;
                world->state = perdu;
        }
        //sinon si tous les ennemis sont mort ou ont survécu
         if(!world->boss.is_apply&&!world->boss.is_visible){
            //on regarde combien d'ennemis ont survécu
            //s'ils ont eté tous détruits
            if(CheckEnemiesSurvived(world)){
                //le joueur a gagné
                world->state = gagnant;
                world->score *= 2;
                }
            //sinon la partie est juste terminé
            else{
                world->state = fin;   
                }
        }
    }
}
void add_animation(int x, int y, world_t* world){
    if(world->explosion_counter<10){ //si la liste d'attente n'est pas complète 
        world->explosion[world->explosion_counter].frame_number = 0; 
        world->explosion[world->explosion_counter].frame_timer = TIMER_BETWEEN_2_FRAMES;
        world->explosion[world->explosion_counter].x = x;
        world->explosion[world->explosion_counter].y = y;
        world->explosion[world->explosion_counter].w = 64;
        world->explosion[world->explosion_counter].h = 64;
        world->explosion_counter++;
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
 * @param sprite 
 * @return int 
 */
int get_y(sprite_t* sprite){
    return sprite->y;
}
/**
 * @brief retourne la valeur de h
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
    sprite->is_visible = 1;
}
/**
 * @brief met is_visible à 0
 * 
 */
void set_invisible(sprite_t* sprite){
    sprite->is_visible = 0;
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
void set_x(sprite_t* sprite, int x){
    sprite->x = x;
}
/**
 * @brief change la valeur de y
 * 
 * @param sprite 
 * @param y
 */
void set_y(sprite_t* sprite, int y){
    sprite->y = y;
}
/**
 * @brief change la valeur de h
 * 
 * @param sprite 
 * @param h
 */
void set_h(sprite_t* sprite, int h){
    sprite->h = h;
}
/**
 * @brief change la valeur de w
 * 
 * @param sprite 
 * @param w 
 */
void set_w(sprite_t* sprite, int w){
    sprite->w = w;
}
/**
 * @brief change la valeur de v
 * 
 * @param sprite 
 * @param v
 */
void set_v(sprite_t* sprite, int v ){
    sprite->v = v;
    }