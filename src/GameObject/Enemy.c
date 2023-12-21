
# ifndef __ENEMY__C
# define __ENEMY__C

# include "./Enemy.h"

// temporary function to test
void init_enemy()
{
    SDL_Rect *src_rects_1[NUM_OF_ENEMY_DIRECTION];
    src_rects_1[ENEMY_LEFT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_1[ENEMY_LEFT]->x = 120;
    src_rects_1[ENEMY_LEFT]->y = 30;
    src_rects_1[ENEMY_LEFT]->w = 45;
    src_rects_1[ENEMY_LEFT]->h = 45;

    src_rects_1[ENEMY_RIGHT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_1[ENEMY_RIGHT]->x = 200;
    src_rects_1[ENEMY_RIGHT]->y = 30;
    src_rects_1[ENEMY_RIGHT]->w = 45;
    src_rects_1[ENEMY_RIGHT]->h = 45;

    SDL_Rect *src_rects_2[NUM_OF_ENEMY_DIRECTION];

    src_rects_2[ENEMY_LEFT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_2[ENEMY_LEFT]->x = 30;
    src_rects_2[ENEMY_LEFT]->y = 30;
    src_rects_2[ENEMY_LEFT]->w = 45;
    src_rects_2[ENEMY_LEFT]->h = 45;

    src_rects_2[ENEMY_RIGHT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_2[ENEMY_RIGHT]->x = 30;
    src_rects_2[ENEMY_RIGHT]->y = 30;
    src_rects_2[ENEMY_RIGHT]->w = 45;
    src_rects_2[ENEMY_RIGHT]->h = 45;

    int i;
    for (i = 0; i < NUM_OF_ENEMYS_STAGE_1; i++)
    {
        Enemy_arr_stage_1[i] = Create_Enemy_Object("../asset/image/enemy.png", Main_Window_Renderer, 0, 0);
    }
    for (i = 0; i < NUM_OF_ENEMYS_STAGE_1 / 2; i++)
    {
        Assign_Enemy_Rect(Enemy_arr_stage_1[i], src_rects_1);
    }
    for (; i < NUM_OF_ENEMYS_STAGE_1; i++)
    {
        Assign_Enemy_Rect(Enemy_arr_stage_1[i], src_rects_2);
    }

    {
        Enemy_arr_stage_1[0]->GlobalPos_x = 80;
        Enemy_arr_stage_1[0]->GlobalPos_y = 420;

        Enemy_arr_stage_1[1]->GlobalPos_x = 145;
        Enemy_arr_stage_1[1]->GlobalPos_y = 60;

        Enemy_arr_stage_1[2]->GlobalPos_x = 510;
        Enemy_arr_stage_1[2]->GlobalPos_y = 420;

        Enemy_arr_stage_1[3]->GlobalPos_x = 600;
        Enemy_arr_stage_1[3]->GlobalPos_y = 270;

        Enemy_arr_stage_1[4]->GlobalPos_x = 505;
        Enemy_arr_stage_1[4]->GlobalPos_y = 90;

        Enemy_arr_stage_1[5]->GlobalPos_x = 675;
        Enemy_arr_stage_1[5]->GlobalPos_y = 150;

        Enemy_arr_stage_1[6]->GlobalPos_x = 945;
        Enemy_arr_stage_1[6]->GlobalPos_y = 150;

        Enemy_arr_stage_1[7]->GlobalPos_x = 1005;
        Enemy_arr_stage_1[7]->GlobalPos_y = 270;

        Enemy_arr_stage_1[8]->GlobalPos_x = 1135;
        Enemy_arr_stage_1[8]->GlobalPos_y = 420;

        Enemy_arr_stage_1[9]->GlobalPos_x = 1410;
        Enemy_arr_stage_1[9]->GlobalPos_y = 150;

        Enemy_arr_stage_1[10]->GlobalPos_x = 1610;
        Enemy_arr_stage_1[10]->GlobalPos_y = 420;

        Enemy_arr_stage_1[11]->GlobalPos_x = 1805;
        Enemy_arr_stage_1[11]->GlobalPos_y = 420;

        Enemy_arr_stage_1[12]->GlobalPos_x = 1975;
        Enemy_arr_stage_1[12]->GlobalPos_y = 90;

        Enemy_arr_stage_1[13]->GlobalPos_x = 2100;
        Enemy_arr_stage_1[13]->GlobalPos_y = 420;

        Enemy_arr_stage_1[14]->GlobalPos_x = 2240;
        Enemy_arr_stage_1[14]->GlobalPos_y = 420;

        Enemy_arr_stage_1[15]->GlobalPos_x = 2400;
        Enemy_arr_stage_1[15]->GlobalPos_y = 420;

        Enemy_arr_stage_1[16]->GlobalPos_x = 2365;
        Enemy_arr_stage_1[16]->GlobalPos_y = 330;

        Enemy_arr_stage_1[17]->GlobalPos_x = 2610;
        Enemy_arr_stage_1[17]->GlobalPos_y = 420;

        Enemy_arr_stage_1[18]->GlobalPos_x = 2850;
        Enemy_arr_stage_1[18]->GlobalPos_y = 300;

        Enemy_arr_stage_1[19]->GlobalPos_x = 2860;
        Enemy_arr_stage_1[19]->GlobalPos_y = 60;
    }

    for (int i = 0; i < NUM_OF_ENEMY_DIRECTION; i++)
    {
        free(src_rects_1[i]);
        free(src_rects_2[i]);
        src_rects_1[i] = NULL;
        src_rects_2[i] = NULL;
    }
}

Enemy_Object *Create_Enemy_Object(char *path, SDL_Renderer *render, float global_x, float global_y)
{
    if (!render)            // invalid argument
    {
        // show error & abort
        fprintf(
            stderr, "%s%s[Error] Given renderer must be initialized.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return NULL;
    }

    Enemy_Object *new_enemy = NULL;
    SDL_Texture *loaded_texture = Load_Texture(path, render, NULL, NULL);

    if (!loaded_texture)        // failed to load texture
    {
        fprintf(
            stderr, "%s%s[Error] Failed to create enemy object.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else if (!(new_enemy = (Enemy_Object *) malloc(sizeof(Enemy_Object))))     // failed to allocate memory
    {
        fprintf(
            stderr, "%s%s[Error] Failed to create new enemy object, failed to allocate memory.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);

        SDL_DestroyTexture(loaded_texture);
    }
    else            // succeed to allocate memory
    {
        new_enemy->Tex = loaded_texture;                // assign loaded texture
        new_enemy->Current_direction = ENEMY_LEFT;      // set initial direction

        // initialize `Src_rect`
        for (int i = 0; i < NUM_OF_ENEMY_DIRECTION; i++)
        {
            new_enemy->Src_rect[i].x = 0;
            new_enemy->Src_rect[i].y = 0;
            new_enemy->Src_rect[i].w = UNIT_PIXEL;
            new_enemy->Src_rect[i].h = UNIT_PIXEL;
        }

        // set initial position
        new_enemy->GlobalPos_x = global_x;
        new_enemy->GlobalPos_y = global_y;
        new_enemy->WindowPos_x = -10;
        new_enemy->WindowPos_y = -10;
        
        // set initial speed
        new_enemy->Moving_speed = ENEMY_MAX_SPEED_X;

        // enemy was created
        new_enemy->is_dead = false;
    }

    // if it failed to create texture, `NULL` will be returned
    return new_enemy;
}

void Assign_Enemy_Rect(Enemy_Object *enemy, SDL_Rect *src_rect_arr[NUM_OF_ENEMY_DIRECTION])
{
    if (!enemy || !src_rect_arr)        // invalid arguments
    {
        // show error & abort
        fprintf(
            stderr, "%s%s[Error] Given `enemy` or `src_rect_arr` hasn't initalized.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return;
    }

    // check whether `*src_rect_arr` is valid
    for (int i = 0; i < NUM_OF_ENEMY_DIRECTION; i++)
    {
        if (!src_rect_arr[i])       // some what invalid elements, probably due to wrong memory allocation or reference of pointer
        {
            // show error & abbort
            fprintf(
                stderr, "%s%s[Error] Invalid array element in `src_rect_arr`.%s\n%s:%d\n", 
                ANSI_BOLD, ANSI_RED, ANSI_RESET,
                __FILE__, __LINE__
            );
            fflush(stderr);
            return;
        }
    }

    // assign `Src_rect` elements to given values
    for (int i = 0; i < NUM_OF_ENEMY_DIRECTION; i++)
    {
        enemy->Src_rect[i].x = src_rect_arr[i]->x;
        enemy->Src_rect[i].y = src_rect_arr[i]->y;
        enemy->Src_rect[i].w = src_rect_arr[i]->w;
        enemy->Src_rect[i].h = src_rect_arr[i]->h;
    }
}

void Patrol_Enemy(Enemy_Object *enemy, Map *map)
{
    if (!enemy || !map || !map->Map_data)   {return;}       // invalid arguments
    else if (enemy->is_dead)                {return;}       // `enemy` is dead, don't patrol

    // pull out values for convenience
    float global_x = enemy->GlobalPos_x;
    float global_y = enemy->GlobalPos_y;

    // the indexes of interest
    int index_x = Round(global_x / map->Shrink_ratio);
    int index_y = Round(global_y / map->Shrink_ratio);

    if (                                                // calculated index is out of range to map data
        (index_x < 0 || index_x >= map->Arr_Width)
        || (index_y >= map->Arr_Height) 
    )
    {
        // show error & abort
        fprintf(
            stderr, "%s%s[Error] Unexpected error occured while patrolling enemy.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return;
    }

/*
//         [left block]            [Enemy]             [right block]
//      [lower left block]      [lower block]       [lower right block]
*/

    // index of left block
    int index_left_x = index_x - 1;
    int index_left_y = index_y;

    // index of right block
    int index_right_x = index_x + 1;
    int index_right_y = index_y;

    // index of lower block
    int index_lower_x = index_x;
    int index_lower_y = index_y + 1;

    // index of lower left block
    int index_lower_left_x = index_x - 1;
    int index_lower_left_y = index_y + 1;

    // index of lower right block
    int index_lower_right_x = index_x + 1;
    int index_lower_right_y = index_y + 1;

    // map data to it's coordinates
    // if `data=true` there's a block in coordinate
    int data_left = map->Map_data[index_left_y][index_left_x];
    int data_right = map->Map_data[index_right_y][index_right_x];
    int data_lower = map->Map_data[index_lower_y][index_lower_x];
    int data_lower_left = map->Map_data[index_lower_left_y][index_lower_left_x];
    int data_lower_right = map->Map_data[index_lower_right_y][index_lower_right_x];

    // lower block is missing, drop enemy to ground
    if (!data_lower)    {enemy->GlobalPos_y += ENEMY_MAX_SPEED_Y * UNIT_TIME_STEP;}

    // both left & right block is missing, available to move both side
    if (!data_left && !data_right)
    {
        if (data_lower_left && !data_lower_right)           // it can move left
        {
            enemy->Moving_speed = -1 * ENEMY_MAX_SPEED_X;   // assign speed
            enemy->Current_direction = ENEMY_LEFT;          // set direction
        }
        else if (!data_lower_left && data_lower_right)      // it can move right
        {
            enemy->Moving_speed = ENEMY_MAX_SPEED_X;        // assign speed
            enemy->Current_direction = ENEMY_RIGHT;         // set direction
        }
    }
    else if (data_left && data_right)           // both left & right direction were blocked
    {
        enemy->Moving_speed = 0;                // enemy can't move any direction
    }
    else if (data_left)                         // only right block is missing
    {
        if (data_lower_right && !data_right)    // can move right
        {
            enemy->Moving_speed = ENEMY_MAX_SPEED_X;    // assign speed
            enemy->Current_direction = ENEMY_RIGHT;     // set direction
        }
        else
        {
            enemy->Moving_speed = 0;            // enemy can't move any direction
        }
    }
    else                                        // only left block is missing
    {
        if (data_lower_left && !data_left)      // can move left
        {
            enemy->Moving_speed = -1 * ENEMY_MAX_SPEED_X;   // assign speed
            enemy->Current_direction = ENEMY_LEFT;          // set direction
        }
        else                                    // enemy can't move any direction
        {
            enemy->Moving_speed = 0;
        }
    }

    // move enemy with it's speed
    enemy->GlobalPos_x += enemy->Moving_speed * UNIT_TIME_STEP;
}

void Apply_Enemy_Player_physics(Player *character, Enemy_Object *enemy)
{
    if (!character || !enemy)        {return;}      // invalid arguments
    else if (enemy->is_dead)        {return;}       // enemy is dead, don't apply physics

    // coordinate of character
    SDL_Rect char_rect = {
        character->GlobalPos_x - UNIT_PIXEL / 2,
        character->GlobalPos_y - UNIT_PIXEL / 2,
        UNIT_PIXEL, UNIT_PIXEL
    };

    // coordinate of enemy
    SDL_Rect enemy_rect = {
        enemy->GlobalPos_x - UNIT_PIXEL / 2,
        enemy->GlobalPos_y - UNIT_PIXEL / 2,
        UNIT_PIXEL, UNIT_PIXEL
    };

    if (SDL_HasIntersection(&char_rect, &enemy_rect))      // if character & enemy were encountered,
    {
        if (enemy->GlobalPos_y - character->GlobalPos_y > UNIT_PIXEL / 2)   // and if character stepped on enemy,
        {
            if (!enemy->is_dead && Step_effect)     {Mix_PlayChannel(-1, Step_effect, 0);}
            enemy->is_dead = true;                              // kill enemy
            character->Speed_y = MAX_SPEED_Y / 2;               // bounce character
        }
        else            // character crashed with enemy
        {
            if (!character->is_dead && Death_effect) {Mix_PlayChannel(-1, Death_effect, 0);}
            character->is_dead = true;  // kill player
            
            
            if (character->Current_state == LEFT)       {character->Current_state = DEATH_LEFT;}
            else if (character->Current_state == RIGHT) {character->Current_state = DEATH_RIGHT;}
        }
    }
}

void Render_Enemy(Enemy_Object *enemy, SDL_Renderer *render, float character_global_x, float character_window_x)
{
    if (!enemy || !render)      {return;}       // invalid arguments

    // pull out values for convenience
    float enemy_global_x = enemy->GlobalPos_x;
    float enemy_global_y = enemy->GlobalPos_y;

    // establish the window coordinate to render `enemy`
    enemy->WindowPos_x = enemy_global_x - character_global_x + character_window_x;
    enemy->WindowPos_y = enemy_global_y;

    // the window coordinate is beyond current window, don't render
    if (enemy->WindowPos_x > WIN_WIDTH || enemy->WindowPos_x < 0)   {return;}
    // enemy is dead, don't render
    else if (enemy->is_dead)                                        {return;}   

    // the window coordinate to render character
    SDL_FRect dst_rect = {
        enemy->WindowPos_x + UNIT_PIXEL / 2,
        enemy->WindowPos_y + UNIT_PIXEL / 2,
        UNIT_PIXEL, UNIT_PIXEL
    };

    Enemy_Direction direction = enemy->Current_direction;

    // render enemy texture with it's current direction to window coordinate
    SDL_RenderCopyF(render, enemy->Tex, &enemy->Src_rect[direction], &dst_rect);
}

void dispose_enemy(Enemy_Object *enemy)
{
    if (enemy)          // good to dispose
    {
        // good to dispose
        if (enemy->Tex)     {SDL_DestroyTexture(enemy->Tex);}   // free texture
        enemy->Tex = NULL;
        free(enemy);        // free allocated memory
    }
}

# endif