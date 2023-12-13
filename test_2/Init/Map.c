
# ifndef __MAP__C
# define __MAP__C

# include "./Map.h"
# include "../GameObject/Player.h" //추가


// temporary function to load block texture
void init_block()
{
    Block_texture_WHOLE = Load_Texture("../asset/image/block2.png", Main_Window_Renderer, NULL, NULL);

    // Texture Loading for Invisible Block
    Block_texture_INVISIBLE = Load_Texture("../asset/image/block2.png", Main_Window_Renderer, NULL, NULL);
    // Invisible Block's Alpha modulating
    SDL_SetTextureAlphaMod(Block_texture_INVISIBLE, 16); 

    {   // assign rectangular coordinates to each block
        // Unbreakable Block
        Block_src_rects[BLOCK_UNBREAKABLE].x = 123;
        Block_src_rects[BLOCK_UNBREAKABLE].y = 45;
        Block_src_rects[BLOCK_UNBREAKABLE].w = 30;
        Block_src_rects[BLOCK_UNBREAKABLE].h = 30;

        // breakable Block
        Block_src_rects[BLOCK_BREAKABLE].x = 200;
        Block_src_rects[BLOCK_BREAKABLE].y = 43;
        Block_src_rects[BLOCK_BREAKABLE].w = 30;
        Block_src_rects[BLOCK_BREAKABLE].h = 30;
        
        // Base
        Block_src_rects[BLOCK_SOIL].x = 278;
        Block_src_rects[BLOCK_SOIL].y = 45;
        Block_src_rects[BLOCK_SOIL].w = 30;
        Block_src_rects[BLOCK_SOIL].h = 30;

        // Thorn
        Block_src_rects[BLOCK_THRON].x = 45;
        Block_src_rects[BLOCK_THRON].y = 123;
        Block_src_rects[BLOCK_THRON].w = 30;
        Block_src_rects[BLOCK_THRON].h = 30;

        // Mine
        Block_src_rects[BLOCK_MINE].x = 123;
        Block_src_rects[BLOCK_MINE].y = 123;
        Block_src_rects[BLOCK_MINE].w = 30;
        Block_src_rects[BLOCK_MINE].h = 30/2;
        
        // Black-Hole
        Block_src_rects[BLOCK_BLACK_HOLE].x = 200;
        Block_src_rects[BLOCK_BLACK_HOLE].y = 123;
        Block_src_rects[BLOCK_BLACK_HOLE].w = 30;
        Block_src_rects[BLOCK_BLACK_HOLE].h = 30;
        
        // Flag
        Block_src_rects[BLOCK_FLAG].x = 278;
        Block_src_rects[BLOCK_FLAG].y = 123;
        Block_src_rects[BLOCK_FLAG].w = 30;
        Block_src_rects[BLOCK_FLAG].h = 30;
        
        // Ending Black-Hole
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].x = 200;
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].y = 123;
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].w = 30;
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].h = 30;
        
        // Invisible Bolck
        Block_src_rects[BLOCK_INVISIBLE].x = 45;
        Block_src_rects[BLOCK_INVISIBLE].y = 45;
        Block_src_rects[BLOCK_INVISIBLE].w = 30;
        Block_src_rects[BLOCK_INVISIBLE].h = 30;
    }
}

// 추가
void init_message()
{
    Message_texture_WHOLE = Load_Texture("../asset/image/clear_dead.png", Main_Window_Renderer, NULL, NULL);

    // clear : 1
    Message_src_rect1.x = 27;
    Message_src_rect1.y = 33;
    Message_src_rect1.w = 30 * 23;
    Message_src_rect1.h = 30 * 2.6;

    // dead : 0
    Message_src_rect2.x = 27;
    Message_src_rect2.y = 140;
    Message_src_rect2.w = 30 * 23;
    Message_src_rect2.h = 30 * 2.6;
}

Map *Load_Map(int *head_of_data_arr, int arr_height, int arr_width)
{
    if (!head_of_data_arr)      // invalid argument
    {
        // show error
        fprintf(
            stderr, "%s%s[Error] Failed to assign map data due to invalid argument.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return NULL;
    }

    Map *new_map = (Map *) malloc(sizeof(Map));     // allocate memory to structure

    if (!new_map)       // failed to allocate memory
    {
        // show error
        fprintf(
            stderr, "%s%s[Error] Failed to allocate memory with loading map.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else                // succeed to allocate memory
    {
        new_map->Map_data = (int **) malloc(sizeof(int *) * arr_height);        // allocate new 2D array
        
        for (int i = 0; i < arr_height; i++)
        {
            new_map->Map_data[i] = (int *) malloc(sizeof(int) * arr_width);     // allocate new 2D array
            
            for (int j = 0; j < arr_width; j++)
            {
                new_map->Map_data[i][j] = head_of_data_arr[i * arr_width + j];  // store data to allocated array
            }
        }
        
        // store additional data
        new_map->Arr_Width = arr_width;
        new_map->Arr_Height = arr_height;
        new_map->Shrink_ratio = UNIT_PIXEL;
    }

    return new_map;
}

void Render_Map(Map *map, SDL_Renderer *render, float global_x, float window_x)
{
    if (!map || !map->Map_data || !render)      // invalid argument
    {
        // show error
        fprintf(
            stderr, "%s%s[Error] Failed to map. Map and renderer must be initialized.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return;
    }

    int x_left = global_x - window_x;                   // left global x position to render
    int x_right = global_x + (WIN_WIDTH - window_x);    // right global x position to render
    
    if (x_left < 0)         // left boundary exceed the limit
    {
        // avoid to show off the limits
        x_left = 0;
        x_right = WIN_WIDTH;
    }
    else if (x_right > map->Arr_Width * map->Shrink_ratio)  // right boundary exceed the limit
    {
        // avoid to show off the limits
        x_left = map->Arr_Width * map->Shrink_ratio - WIN_WIDTH;
        x_right = map->Arr_Width * map->Shrink_ratio;
    }

    // the index to render
    x_left /= map->Shrink_ratio;
    x_right /= map->Shrink_ratio;

    // the destination to render
    SDL_FRect dst_rect;             // using float-rectangle
    dst_rect.w = UNIT_PIXEL;
    dst_rect.h = UNIT_PIXEL;

    for (int i = 0; i < map->Arr_Height; i++)       // row
    {
        for (int j = x_left; j < x_right + 1; j++)  // column   --> add 1 more column to render (x_right + 1), it looks smoother
        {
            // --------------------------------------------------------------------------------------------- //
                dst_rect.x = j * map->Shrink_ratio - global_x + window_x + UNIT_PIXEL / 2;      // i don't know why but it works    why???????
                // --------------------------------------------------------------------------------------------- //
                dst_rect.y = i * map->Shrink_ratio + UNIT_PIXEL / 2;

                int block_index = map->Map_data[i][j];

                if (InRange(block_index, 0, NUM_OF_BLOCK_KIND))
                {
                    if (block_index == BLOCK_INVISIBLE)
                    {
                        SDL_RenderCopyF(render, Block_texture_INVISIBLE, &Block_src_rects[block_index], &dst_rect);
                    }
                    else
                    {
                        SDL_RenderCopyF(render, Block_texture_WHOLE, &Block_src_rects[block_index], &dst_rect);
                    }
                }
                else
                {
                    fprintf(
                        stderr, 
                        "%s%s[Error] Unexpected block encoutnered while rendering map.%s\n%s:%d\n", 
                        ANSI_BOLD, ANSI_RED, ANSI_RESET, 
                        __FILE__, __LINE__
                    );
                    fflush(stderr);
                    return;
                }
        }
    }
}

// 추가
void Render_Message(SDL_Renderer *render, float WindowPos_x, float WindowPos_y)
{
    if (!render)      // invalid argument
    {
        // show error
        fprintf(
            stderr, "%s%s[Error] Failed to open message. Message must be initialized.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
        return;
    }

    // the destination to render
    SDL_FRect dst_rect_message;             // using float-rectangle
    dst_rect_message.x = 20;
    dst_rect_message.y = WindowPos_y;
    dst_rect_message.w = WIN_WIDTH;
    dst_rect_message.h = UNIT_PIXEL * 2.6;

    if (Condition == 1)      {
        printf("true\n");
        SDL_RenderCopyF(render, Message_texture_WHOLE, &Message_src_rect1, &dst_rect_message);
    } // clear : 1
    else if (Condition == 0) {
        printf("False\n");
        SDL_RenderCopyF(render, Message_texture_WHOLE, &Message_src_rect2, &dst_rect_message);
    } // dead : 0
}

void dispose_map(Map *map)
{
    if (map)                // good to free memory
    {
        if (map->Map_data)  // good to free memory
        {
            for (int i = 0; i < map->Arr_Height; i++)
            {
                free(map->Map_data[i]);     // free allocated memory
                map->Map_data[i] = NULL;
            }
            free(map->Map_data);            // free allocated memory
            map->Map_data = NULL;
        }
        free(map);          // free allocated memory
    }
}

# endif
