
# ifndef __MAP__C
# define __MAP__C

# include "./Map.h"

// temporary function to load block texture
void init_block()
{
    Block = Load_Texture("../asset/image/block2.png", Main_Window_Renderer, NULL, NULL);

    // Texture Loading for Invisible Block
    T_Block = Load_Texture("../asset/image/block2.png", Main_Window_Renderer, NULL, NULL);
    // Invisible Block's Alpha modulating
    SDL_SetTextureAlphaMod(T_Block, 16); 

    for (int i = 0 ; i < TEST_MAP_HEIGHT ; i++)
    {
        for (int j = 0 ; j < TEST_MAP_WIDTH ; j++)
        {
            switch (TestMap[i][j])
            {
                case 1: // Unbreakable Block
                    Block_src_rect1.x = 123;
                    Block_src_rect1.y = 45;
                    Block_src_rect1.w = UNIT_PIXEL;
                    Block_src_rect1.h = UNIT_PIXEL;
                    break;
                case 2: // breakable Block
                    Block_src_rect2.x = 200;
                    Block_src_rect2.y = 43;
                    Block_src_rect2.w = UNIT_PIXEL;
                    Block_src_rect2.h = UNIT_PIXEL;
                    break;
                case 3: // Base
                    Block_src_rect3.x = 278;
                    Block_src_rect3.y = 45;
                    Block_src_rect3.w = UNIT_PIXEL;
                    Block_src_rect3.h = UNIT_PIXEL;
                    break;
                case 4: // Thorn
                    Block_src_rect4.x = 45;
                    Block_src_rect4.y = 123;
                    Block_src_rect4.w = UNIT_PIXEL;
                    Block_src_rect4.h = UNIT_PIXEL;
                    break;
                case 5: // Mine
                    Block_src_rect5.x = 123;
                    Block_src_rect5.y = 123;
                    Block_src_rect5.w = UNIT_PIXEL;
                    Block_src_rect5.h = UNIT_PIXEL/2;
                    break;
                case 6: // Black-Hole
                    Block_src_rect6.x = 200;
                    Block_src_rect6.y = 123;
                    Block_src_rect6.w = UNIT_PIXEL;
                    Block_src_rect6.h = UNIT_PIXEL;
                    break;
                case 7: // Flag
                    Block_src_rect7.x = 278;
                    Block_src_rect7.y = 123;
                    Block_src_rect7.w = UNIT_PIXEL;
                    Block_src_rect7.h = UNIT_PIXEL;
                    break;
                case 9: // Invisible Bolck
                    T_Block_src_rect9.x = 45;
                    T_Block_src_rect9.y = 45;
                    T_Block_src_rect9.w = UNIT_PIXEL;
                    T_Block_src_rect9.h = UNIT_PIXEL;
                    break;
                default :
                    break;
            }
        }
    }
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

            switch (map->Map_data[i][j])                // data to render
            {
                case 0: break; // Not rendering for empty space

                case 1:
                SDL_RenderCopyF(render, Block, &Block_src_rect1, &dst_rect);       // render Unbreakable Block
                break;

                case 2:
                SDL_RenderCopyF(render, Block, &Block_src_rect2, &dst_rect);       // render breakable Block
                break;

                case 3:
                SDL_RenderCopyF(render, Block, &Block_src_rect3, &dst_rect);       // render Base 
                break;

                case 4:
                SDL_RenderCopyF(render, Block, &Block_src_rect4, &dst_rect);       // render Thorn
                break;                        

                case 5:
                SDL_RenderCopyF(render, Block, &Block_src_rect5, &dst_rect);       // render Mine 
                break;

                case 6:
                SDL_RenderCopyF(render, Block, &Block_src_rect6, &dst_rect);       // render Black-Hole
                break;

                case 7:
                SDL_RenderCopyF(render, Block, &Block_src_rect7, &dst_rect);       // render Flag
                break;

                case 9:
                SDL_RenderCopyF(render, T_Block, &T_Block_src_rect9, &dst_rect);   // render Invisible Block
                break;

                default :           // unexpected block
                fprintf(
                    stderr, 
                    "%s%s[Error] Unexpected block encoutnered.%s\n%s:%d\n", 
                    ANSI_BOLD, ANSI_RED, ANSI_RESET, 
                    __FILE__, __LINE__
                );
                fflush(stderr);
                return;
            }
        }
    }
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
