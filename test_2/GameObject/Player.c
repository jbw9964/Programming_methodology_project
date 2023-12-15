
# ifndef __PLAYER__C
# define __PLAYER__C

# include "./Player.h"

Player *Create_Player(char *path, SDL_Renderer *render)
{
    if (!render)            // invalid argument
    {
        fprintf(
            stderr, "%s%s[Error] Given renderer must be initialized.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return NULL;
    }

    Player *new_player = NULL;
    SDL_Texture *loaded_texture = Load_Texture(path, render, NULL, NULL);

    if (!loaded_texture)        // failed to load texture
    {
        fprintf(
            stderr, "%s%s[Error] Failed to create player.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else if (!(new_player = (Player *) malloc(sizeof(Player))))     // failed to allocate memory
    {
        fprintf(
            stderr, "%s%s[Error] Failed to create new player, failed to allocate memory.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);

        SDL_DestroyTexture(loaded_texture);
    }
    else            // succeed to allocate memory
    {
        new_player->Tex = loaded_texture;               // assign loaded texture
        new_player->Current_state = RIGHT;             // set initial state
        
        // set initial keyboard state
        new_player->Key.Up = false;
        new_player->Key.Down = false;
        new_player->Key.Left = false;
        new_player->Key.Right = false;

        // initialize `Src_rect`
        for (int i = 0; i < NUM_OF_PLAYER_STATE; i++)
        {
            new_player->Src_rect[i].x = 0;
            new_player->Src_rect[i].y = 0;
            new_player->Src_rect[i].w = 0;
            new_player->Src_rect[i].h = 0;
        }

        // set initial position
        new_player->GlobalPos_x = WIN_WIDTH / 2;
        new_player->GlobalPos_y = WIN_HEIGHT / 2;
        new_player->WindowPos_x = WIN_WIDTH / 2;
        new_player->WindowPos_y = WIN_HEIGHT / 2;
        
        // set initial speed
        new_player->Speed_x = 0;
        new_player->Speed_y = 0;

        // set initial keyboard state
        new_player->Key.Up = false;
        new_player->Key.Down = false;
        new_player->Key.Left = false;
        new_player->Key.Right = false;

        new_player->is_dead = false;
        new_player->is_clear = false;
    }

    // if it failed to create texture, `NULL` will be returned
    return new_player;
}

void Kill_Player(Player *character)
{
    if (!character)     {return;}
    character->is_dead = true;
}

void Assign_Player_Rect(Player *character, SDL_Rect *src_rect_arr[NUM_OF_PLAYER_STATE])
{
    if (!character || !src_rect_arr)
    {
        fprintf(
            stderr, "%s%s[Error] Given `character` or `src_rect_arr` hasn't initalized.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return;
    }

    for (int i = 0; i < NUM_OF_PLAYER_STATE; i++)
    {
        if (!src_rect_arr[i])
        {
            fprintf(
                stderr, "%s%s[Error] Invalid array element in `src_rect_arr`.%s\n%s:%d\n", 
                ANSI_BOLD, ANSI_RED, ANSI_RESET,
                __FILE__, __LINE__
            );
            fflush(stderr);
            return;
        }
    }

    for (int i = 0; i < NUM_OF_PLAYER_STATE; i++)
    {
        character->Src_rect[i].x = src_rect_arr[i]->x;
        character->Src_rect[i].y = src_rect_arr[i]->y;
        character->Src_rect[i].w = src_rect_arr[i]->w;
        character->Src_rect[i].h = src_rect_arr[i]->h;
    }
}

void Record_KeyState(Keyboard *record, SDL_Event *event)
{
    if (!record || !event)          // invalid argument
    {
        // shows error
        fprintf(
            stderr, "%s%s[Error] Given parameter wasn't initialized.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return;
    }

    // received duplicated input, do nothing since it's duplicated
    if (event->key.repeat)      {return;}
    // received input is not a keyboard input, something else
    else if (event->type != SDL_KEYUP && event->type != SDL_KEYDOWN)    {return;}

    // received keyboard input (arrow, direction)
    SDL_Scancode direction = event->key.keysym.scancode;

    if (event->type == SDL_KEYUP)       // keyboard were pressed
    {
        // set internal data in case
        if (direction == KEY_UP)       {record->Up = false;}
        if (direction == KEY_DOWN)     {record->Down = false;}
        if (direction == KEY_LEFT)     {record->Left = false;}
        if (direction == KEY_RIGHT)    {record->Right = false;}
    }
    else                                // keyboard were pulled
    {
        // set internal data in case
        if (direction == KEY_UP)       {record->Up = true;}
        if (direction == KEY_DOWN)     {record->Down = true;}
        if (direction == KEY_LEFT)     {record->Left = true;}
        if (direction == KEY_RIGHT)    {record->Right = true;}
    }

    if (direction == KEY_RESTART)       {record->Restart = true;}
}

void Receive_Keyboard_input(Player *character, Map *map, SDL_Event *event, bool *quit_flag)
{
    // invalid argument
    if (!character || !map || !map->Map_data || !event)     {return;}

    while (SDL_PollEvent(event))        // receive event
    {
        // window was closed, set `quit_flag` if possible
        if (event->type == SDL_QUIT && quit_flag)   {*quit_flag = true;}
        // record keyboard state in character when it's not dead
        else                                        {Record_KeyState(&character->Key, event);}
    }

    if (character->Key.Restart)
    {
        Adjust_Player_position(character, WIN_WIDTH / 2, WIN_HEIGHT / 2);
        character->Key.Restart = false;
        character->is_dead = false;
        character->is_clear = false;
    }

    // both left & right key were pressed
    if (character->Key.Left == character->Key.Right)    {Stop_Player_x(character);}
    // only left key were pressed
    else if (character->Key.Left)                       {Accelerate_Player(character, -1 * MAX_SPEED_X, 0);}
    // only right key were pressed
    else if (character->Key.Right)                      {Accelerate_Player(character, MAX_SPEED_X, 0);}
    
    // if (character->Key.Down)    {Accelerate_Player(character, 0, -1 * MAX_SPEED_Y);}
    if (character->Key.Up)
    {
        // pull out values for convenience
        float global_x = character->GlobalPos_x;
        float global_y = character->GlobalPos_y;

        // the indexes of interest
        int index_x = Round(global_x / map->Shrink_ratio);
        int index_y = Round(global_y / map->Shrink_ratio);

        // index of lower block
        int index_down_x = index_x;
        int index_down_y = index_y + 1;

        if (global_y <= 0) {return;}
        if (
            !((index_x < 0 || index_x >= map->Arr_Width) || (index_y >= map->Arr_Height))
            && map->Map_data[index_down_y][index_down_x]
        )
        {
            Accelerate_Player(character, 0, MAX_SPEED_Y * 4 / 5);
        }
    }
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
    character->Current_state = RIGHT;
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

    if (character->Speed_x > 0)         {character->Current_state = RIGHT;}
    else if (character->Speed_x < 0)    {character->Current_state = LEFT;}
}

void Apply_Block_Interruption(Player *character, Map *map)
{
    if (!character || !map || !map->Map_data)   {return;}       // invalid argument

    if (character->GlobalPos_y > WIN_HEIGHT)    {return;}       // no need to interrupt player, since there's no block out of the window

    // the map index where player exists
    int index_x = Round(character->GlobalPos_x / map->Shrink_ratio);
    int index_y = Round(character->GlobalPos_y / map->Shrink_ratio);

    // global position of player's left & right side
    float character_lside_pos = character->GlobalPos_x - UNIT_PIXEL / 2 + 1;
    float character_rside_pos = character->GlobalPos_x + UNIT_PIXEL / 2 - 1;

/*
//      [up left]       [up block]      [up right]
//      [left block]    [Character]     [right block]
//      [down left]     [down block]    [down right]
*/

    // up blocks
    int index_up_y = index_y - 1;
    int index_up_left_x = Round(character_lside_pos / map->Shrink_ratio);
    int index_up_left_y = index_up_y;
    int index_up_right_x = Round(character_rside_pos / map->Shrink_ratio);
    int index_up_right_y = index_up_y;

    // down blocks
    int index_down_y = index_y + 1;
    int index_down_left_x = Round(character_lside_pos / map->Shrink_ratio);
    int index_down_left_y = index_down_y;
    int index_down_right_x = Round(character_rside_pos / map->Shrink_ratio);
    int index_down_right_y = index_down_y;

    // left block
    int index_left_x = Round(character_lside_pos / map->Shrink_ratio);
    int index_left_y = index_y;

    // right block
    int index_right_x = Round(character_rside_pos / map->Shrink_ratio);
    int index_right_y = index_y;

    // map data
    int block;

    if (InRange(index_up_y, 0, map->Arr_Height - 1))            // if upper block index is proper
    {
        if (InRange(index_up_left_x, 0, map->Arr_Width - 1))    // upper left block
        {
            block = map->Map_data[index_up_left_y][index_up_left_x];    // load map data
            if (
                (block == BLOCK_UNBREAKABLE || block == BLOCK_SOIL || block == BLOCK_INVISIBLE)     // if player encountered impassible block,
                && character->Speed_y > 0                       // & if player has [+y] speed
            )
            {   // stop player & adjust coordinates
                character->Speed_y = 0;
                character->GlobalPos_y = (index_up_y + 1) * map->Shrink_ratio;
                character->WindowPos_y = (index_up_y + 1) * map->Shrink_ratio;
            }
        }

        if (InRange(index_up_right_x, 0, map->Arr_Width - 1))   // upper right block
        {
            block = map->Map_data[index_up_right_y][index_up_right_x];  // load map data
            if (
                (block == BLOCK_UNBREAKABLE || block == BLOCK_SOIL || block == BLOCK_INVISIBLE)     // if player encountered impassible block,
                && character->Speed_y > 0                       // & if player has [+y] speed
            )
            {   // stop player & adjust coordinates
                character->Speed_y = 0;
                character->GlobalPos_y = (index_up_y + 1) * map->Shrink_ratio;
                character->WindowPos_y = (index_up_y + 1) * map->Shrink_ratio;
            }
        }
    }

    if (InRange(index_down_y, 0, map->Arr_Height - 1))          // if lower block index is proper
    {
        if (InRange(index_down_left_x, 0, map->Arr_Width - 1))  // lower left block 
        {
            block = map->Map_data[index_down_left_y][index_down_left_x];    // load map data
            if (
                (block == BLOCK_UNBREAKABLE || block == BLOCK_SOIL          // if player encountered impassible block,
                || block == BLOCK_INVISIBLE || block == BLOCK_BREAKABLE) 
                && character->Speed_y < 0                   // & if player has [-y] speed
            )
            {   // stop player & adjust coordinates
                character->Speed_y = 0;
                character->GlobalPos_y = (index_down_y - 1) * map->Shrink_ratio;
                character->WindowPos_y = (index_down_y - 1) * map->Shrink_ratio;
            }
        }

        if (InRange(index_down_right_x, 0, map->Arr_Width - 1)) // lower right block 
        {
            block = map->Map_data[index_down_right_y][index_down_right_x];  // load map data
            if (
                (block == BLOCK_UNBREAKABLE || block == BLOCK_SOIL 
                || block == BLOCK_INVISIBLE || block == BLOCK_BREAKABLE)    // if player encountered impassible block,
                && character->Speed_y < 0
            )
            {   // stop player & adjust coordinates
                character->Speed_y = 0;
                character->GlobalPos_y = (index_down_y - 1) * map->Shrink_ratio;
                character->WindowPos_y = (index_down_y - 1) * map->Shrink_ratio;
            }
        }
    }

    if (                                                            // if left block index is proper
        InRange(index_left_x, 0, map->Arr_Width - 1) 
        && InRange(index_left_y, 0, map->Arr_Height - 1)
    )
    {
        block = map->Map_data[index_left_y][index_left_x];          // load map data
        if (
            (block == BLOCK_UNBREAKABLE || block == BLOCK_BREAKABLE     // if player encountered impassible block,
            || block == BLOCK_SOIL || block == BLOCK_INVISIBLE)
            && character->Speed_x < 0                                   // & if player has [-x] speed
        )
        {   // stop player
            character->Speed_x = 0;
        }
    }

    if (                                                            // if right block index is proper
        InRange(index_right_x, 0, map->Arr_Width - 1) 
        && InRange(index_right_y, 0, map->Arr_Height - 1)
    )  
    {
        block = map->Map_data[index_right_y][index_right_x];        // load map data
        if (
            (block == BLOCK_UNBREAKABLE || block == BLOCK_BREAKABLE     // if player encountered impassible block,
            || block == BLOCK_SOIL || block == BLOCK_INVISIBLE)
            && character->Speed_x > 0                                   // & if player has [+x] speed
        )
        {   // stop player
            character->Speed_x = 0;
        }
    }
}

void Apply_Block_Object_logic(Player *character, Map *map)
{
    if (!character || !map || !map->Map_data)   {return;}       // invalid argument

    // the map index where player exists
    int index_x = Round(character->GlobalPos_x / map->Shrink_ratio);
    int index_y = Round(character->GlobalPos_y / map->Shrink_ratio);

    if (index_y < 0)        {return;}                   // no need to interrupt player, since there's no block out of the window
    if (                                                // calculated index is out of range to map data
        (index_x < 0 || index_x >= map->Arr_Width)
        || (index_y >= map->Arr_Height) 
    )
    {
        // shows error & abort
        fprintf(
            stderr, "%s%s[Error] Unexpected error occured while applying Map physics to character.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return;
    }

    if (index_y > 0)
    {
        int block_up = map->Map_data[index_y - 1][index_x];

        if (block_up == BLOCK_BREAKABLE && character->Speed_y > 0)
        {
            map->Map_data[index_y - 1][index_x] = BLOCK_EMPTY;
            character->Speed_y = 0;
        }
    }

    int block = map->Map_data[index_y][index_x];

    if (block == BLOCK_THRON || block == BLOCK_MINE || block == BLOCK_BLACK_HOLE)
    {
        character->is_dead = true;
        character->Current_state = character->Speed_x < 0 ? DEATH_LEFT : DEATH_RIGHT;
        Stop_Player(character);
    }
    else if (block == BLOCK_FLAG)
    {
        map->Map_data[STAGE_1_GOAL_COL][STAGE_1_GOAL_ROW] = BLOCK_BLACK_HOLE_GOAL;
        map->Map_data[index_y][index_x] = BLOCK_EMPTY;
    }
    else if (block == BLOCK_BLACK_HOLE_GOAL)
    {
        character->is_clear = true;
    }
}

void Render_Player(Player *character, SDL_Renderer *render)
{
    if (!character || !render)  {return;}
    
    SDL_FRect dst_rect = {
        character->WindowPos_x + UNIT_PIXEL / 2, 
        character->WindowPos_y + UNIT_PIXEL / 2, 
        UNIT_PIXEL, UNIT_PIXEL
    };

    Player_State state = character->Current_state;
    SDL_RenderCopyF(render, character->Tex, &character->Src_rect[state], &dst_rect);
}

void dispose_player(Player *character)
{
    if (character)          // good to dispose
    {
        // good to dispose
        if (character->Tex)     {SDL_DestroyTexture(character->Tex);}   // free texture
        character->Tex = NULL;
        free(character);    // free allocated memory
        character = NULL;
    }
}

# endif