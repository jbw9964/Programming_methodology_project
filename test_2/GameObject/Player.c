
# ifndef __PLAYER__C
# define __PLAYER__C

# include "./Player.h"

Player *Create_Player(char *path, SDL_Renderer *render)
{
    if (!render)            // invalid argument
    {
        fprintf(
            stderr, "%s%s[Error] Given renderer must be initialized.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
        );
        fflush(stderr);
        return NULL;
    }

    Player *new_player = NULL;
    SDL_Texture *loaded_texture = Load_Texture(path, render, NULL, NULL);

    if (!loaded_texture)        // failed to load texture
    {
        fprintf(
            stderr, "%s%s[Error] Failed to create player.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
        );
        fflush(stderr);
    }
    else if (!(new_player = (Player *) malloc(sizeof(Player))))     // failed to allocate memory
    {
        fprintf(
            stderr, "%s%s[Error] Failed to create new player, failed to allocate memory.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
        );
        fflush(stderr);

        SDL_DestroyTexture(loaded_texture);
    }
    else            // succeed to allocate memory
    {
        new_player->Tex = loaded_texture;               // assign loaded texture
        new_player->Current_state = NORMAL;             // set initial state

        // set initial position
        new_player->GlobalPos_x = WIN_WIDTH / 2;
        new_player->GlobalPos_y = WIN_HEIGHT / 2;
        new_player->WindowPos_x = WIN_WIDTH / 2;
        new_player->WindowPos_y = WIN_HEIGHT / 2;
        
        // set initial speed
        new_player->Speed_x = 0;
        new_player->Speed_y = 0;
    }

    // if it failed to create texture, `NULL` will be returned
    return new_player;
}

void Adjust_Player_position(Player *character, float global_x, float global_y)
{
    if (!character)     {return;}       // invalid argument

    // set spped as zero
    character->Speed_x = 0;
    character->Speed_y = 0;
    
    // set global position
    character->GlobalPos_x = global_x;
    character->GlobalPos_y = global_y;

    // set relative position to window
    character->WindowPos_x = WIN_WIDTH / 2;     // middle of WIDTH
    character->WindowPos_y = global_y;

    // set state normal
    character->Current_state = NORMAL;
}

void Accelerate_Player(Player *character, float speed_x, float speed_y)
{
    if (!character)     {return;}       // invalid argument
    
    // add speed
    character->Speed_x += speed_x;
    character->Speed_y += speed_y;

    // speed exceed it's limit
    // adjust to maxima or minima
    if (character->Speed_x > MAX_SPEED_X)       {character->Speed_x = MAX_SPEED_X;}
    if (character->Speed_x < -1 * MAX_SPEED_X)  {character->Speed_x = -1 * MAX_SPEED_X;}
    if (character->Speed_y > MAX_SPEED_Y)       {character->Speed_y = MAX_SPEED_Y;}
    if (character->Speed_y < -1 * MAX_SPEED_Y)  {character->Speed_y = -1 * MAX_SPEED_Y;}
}

void Stop_Player_x(Player *character)
{
    if (character)  {character->Speed_x = 0;}       // set speed 0
}
void Stop_Player_y(Player *character)
{
    if (character)  {character->Speed_y = 0;}       // set speed 0
}
void Stop_Player(Player *character)
{
    if (character)                                  // set speed 0
    {
        character->Speed_x = 0;
        character->Speed_y = 0;
    }
}

void Move_Player(Player *character)
{
    if (!character)     {return;}       // invalid argument

    // pull out values for convenience
    float speed_x = character->Speed_x;
    float speed_y = character->Speed_y;

    // calculate displacement of character
    character->GlobalPos_x += speed_x * UNIT_TIME_STEP;
    character->GlobalPos_y -= speed_y * UNIT_TIME_STEP;

    character->WindowPos_x += speed_x * UNIT_TIME_STEP;
    character->WindowPos_y -= speed_y * UNIT_TIME_STEP;

    // pull out values for convenience
    float global_x = character->GlobalPos_x;
    float global_y = character->GlobalPos_y;
    float window_x = character->WindowPos_x;
    float window_y = character->WindowPos_y;

    // relative window exceeded it's limit
    if (window_x < WIN_WIDTH * VIEW_PORTION_LEFT)           // exceeded middle-left line(?)
    {
        character->WindowPos_x = WIN_WIDTH * VIEW_PORTION_LEFT;
    }
    else if (window_x > WIN_WIDTH * VIEW_PORTION_RIGHT)     // exceeded middle-right line(?)
    {
        character->WindowPos_x = WIN_WIDTH * VIEW_PORTION_RIGHT;
    }

    // relative window exceeded it's limit,
    // BUT it's on edge of map so keep change relative position
    if (global_x < WIN_WIDTH * VIEW_PORTION_LEFT)                                   // on the left-edge of map
    {
        character->WindowPos_x = global_x;
    }
    else if (global_x > (MAP_WIDTH - WIN_WIDTH) + WIN_WIDTH * VIEW_PORTION_RIGHT)   // on the right-edge of map
    {
        character->WindowPos_x = global_x - (MAP_WIDTH - WIN_WIDTH);
    }

    // global position exceeded it's limit
    if (global_x < 0)                           // left-edge of map
    {
        character->GlobalPos_x = 0;
        character->WindowPos_x = 0;             // relative position must be intialized too
    }
    else if (global_x > MAP_WIDTH)              // right-edge of map
    {
        character->GlobalPos_x = MAP_WIDTH;
        character->WindowPos_x = WIN_WIDTH;     // relative position must be intialized too
    }

    // set character's state according to it's speed
    if (character->Speed_y)         {character->Current_state = JUMP;}      // hovering or falling or jumping
    else if (character->Speed_x)    {character->Current_state = RUN;}       // moving on the ground
    else                            {character->Current_state = NORMAL;}    // stand still
}

void Apply_physics(Player *character, Map *map)
{
    if (!character || !map || !map->Map_data)   {return;}       // invalid argument

    // pull out values for convenience
    float global_x = character->GlobalPos_x;
    float global_y = character->GlobalPos_y;

    // the indexes of interest
    int index_x = (int) global_x / map->Shrink_ratio;
    int index_y = (int) global_y / map->Shrink_ratio;

    if (index_y < 0)        {return;}                   // no need to apply physics to upper(?) region
    if (                                                // calculated index is out of range to map data
        (index_x < 0 || index_x >= map->Arr_Width)
        || (index_y >= map->Arr_Height) 
    )
    {
        // shows error & abort
        fprintf(
            stderr, "%s%s[Error] Unexpected error occured while applying Map physics to chracter.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
        );
        fflush(stderr);
        return;
    }
    

/*
//                      [upper block]
//      [left block]    [Character]     [right block]
//                      [lower block]
*/

    // index of upper block
    int index_up_x = index_x;
    int index_up_y = index_y - 1;

    // index of lower block
    int index_down_x = index_x;
    int index_down_y = index_y + 1;

    // index of left block
    int index_left_x = index_x - 1;
    int index_left_y = index_y;

    // index of right block
    int index_right_x = index_x + 1;
    int index_right_y = index_y;

    if (index_up_y > 0 && map->Map_data[index_up_y][index_up_x])        // if upper block index is proper & block exists,
    {
        if (character->Speed_y > 0)         // & if `character` has [+y] velocity,
        {
            character->Speed_y = 0;         // set [y] velocity as `zero`
            // and adjust it's position, preventing "Slip out"
            // both global & window (relative) position
            character->GlobalPos_y = (index_up_y + 1) * map->Shrink_ratio;
            character->WindowPos_y = (index_up_y + 1) * map->Shrink_ratio;
        }
    }

    if (index_down_y < map->Arr_Height && map->Map_data[index_down_y][index_down_x])    // if lower block index is proper & block exists,
    {
        if (character->Speed_y < 0)         // & if `character` has [+y] velocity,
        {
            character->Speed_y = 0;         // set [y] velocity as `zero`
            // and adjust it's position, preventing "Slip out"
            // both global & window (relative) position
            character->GlobalPos_y = (index_down_y - 1) * map->Shrink_ratio;
            character->WindowPos_y = (index_down_y - 1) * map->Shrink_ratio;
        }
    }

    if (index_left_x > 0 && map->Map_data[index_left_y][index_left_x])                  // if left block index is proper & block exists,
    {
        if (character->Speed_x < 0)
        {
            character->Speed_x = 0;     // set [x] velocity as `zero`
            // and adjust it's position, preventing "Slip out"
            // both global & window (relative) position
            character->GlobalPos_x = (index_left_x + 1) * map->Shrink_ratio;
            character->WindowPos_x = (index_left_x + 1) * map->Shrink_ratio;
        }
    }

    if (index_right_x < map->Arr_Width && map->Map_data[index_right_y][index_right_x])  // if right block index is proper & block exists,
    {
        if (character->Speed_x > 0)
        {
            character->Speed_x = 0;     // set [x] velocity as `zero`
            // and adjust it's position, preventing "Slip out"
            // both global & window (relative) position
            character->GlobalPos_x = (index_right_x - 1) * map->Shrink_ratio;
            character->WindowPos_x = (index_right_x - 1) * map->Shrink_ratio;
        }
    }
}

void dispose_player(Player *character)
{
    if (character)          // good to dispose
    {
        // good to dispose
        if (character->Tex)     {SDL_DestroyTexture(character->Tex);}   // free texture
        character->Tex = NULL;

        for (int i = 0; i < NUM_OF_PLAYER_STATE; i++)       // free allocated array
        {
            if (character->Src_rect[i])     {free(character->Src_rect[i]);}
            character->Src_rect[i] = NULL;
        }
        
        free(character);    // free allocated memory
    }
}

# endif