
# ifndef __MAP__C
# define __MAP__C

# include "./Map.h"

// temporary function to load block texture
void init_block()
{
    Block = Load_Texture("../asset/image/blocks_1.png", Main_Window_Renderer, NULL, NULL);
    Block_src_rect.x = 30;
    Block_src_rect.y = 0;
    Block_src_rect.w = 30;
    Block_src_rect.h = 30;
}

Map *Load_Map(int *head_of_data_arr, int arr_height, int arr_width)
{
    if (!head_of_data_arr)      // invalid argument
    {
        // show error
        fprintf(
            stderr, "%s%s[Error] Failed to assign map data due to invalid argument.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
        );
        fflush(stderr);
        return NULL;
    }

    Map *new_map = (Map *) malloc(sizeof(Map));     // allocate memory to structure

    if (!new_map)       // failed to allocate memory
    {
        // show error
        fprintf(
            stderr, "%s%s[Error] Failed to allocate memory with loading map.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
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
            stderr, "%s%s[Error] Failed to map. Map and renderer must be initialized.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
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
            if (map->Map_data[i][j])                // data to render
            {
                // --------------------------------------------------------------------------------------------- //
                dst_rect.x = j * map->Shrink_ratio - global_x + window_x;       // i don't know why but it works    why???????
                // --------------------------------------------------------------------------------------------- //
                dst_rect.y = i * map->Shrink_ratio;
                SDL_RenderCopyF(render, Block, &Block_src_rect, &dst_rect);     // render
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
