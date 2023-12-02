
# ifndef __MAP__H
# define __MAP__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>

# include "../def.h"

# define TEST_MAP_WIDTH             46
# define TEST_MAP_HEIGHT            16
# define TEST_MAP_SHRINK_RATIO      30

int TestMap[TEST_MAP_HEIGHT][TEST_MAP_WIDTH] = {
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1 },
    { 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1 }
};

/**
 * @brief   A structure to contain data of map. The map data must be shrinked by `Shrink_ratio`.
 *  
 * @param   `Map_data`      2D `int` array that contains the data of map, `Map_data[Y][X] - Map_data[Height][Width]`
 * @param   `Arr_Height`    the height of an array, equals to number of `rows`
 * @param   `Arr_Width`     the width of an array, equals to number of `columns`
 * @param   `Shrink_ratio`  the ratio of data of array & actual data, equals to `UNIT_PIXEL`
 *  
 * @warning `Arr_Height` <--> `ROWS` <--> `Y`    ,   `Arr_Width` <--> `COLUMNS` <--> `X`
 */
typedef struct Map
{
    int **Map_data;
    int Arr_Height;
    int Arr_Width;
    int Shrink_ratio;
} Map;

/**
 * @brief   Load map from given array `head_of_data_arr[arr_height][arr_width]`.
 * 
 * @param   `head_of_data_arr`  2D array of map data
 * @param   `arr_height`        `rows` of given data
 * @param   `arr_width`         `columns` of given data
 *  
 * @return  `Map *`         :   allocated `Map *`
 * @warning `head_of_data_arr` is 2D array. In order to use this function with `int [][]` types, you need give the address of first element.
 * Likewise `(int *) &head_of_data_arr` or `&head_of_data_arr[0][0]`
 */
Map *Load_Map(int *head_of_data_arr, int arr_height, int arr_width);

/**
 * @brief   Render the map data to given `render`, fitted with global position & window (relative) position.
 *  
 * @param   `map`           data to render map
 * @param   `render`        render to show
 * @param   `global_x`      current `X` global position of character
 * @param   `window_x`      current `X` window (relative) position of character
 *  
 * * @warning Either `map` or `render` wasn't initialized, it will shows error.
 */
void Render_Map(Map *map, SDL_Renderer *render, float global_x, float window_x);

// @brief   Free allocated memory assigned to `map`.
void dispose_map(Map *map);

extern SDL_Texture *Load_Texture(char *path, SDL_Renderer *render, int *w, int *h);
extern SDL_Renderer *Main_Window_Renderer;

SDL_Texture *Block;
SDL_Rect Block_src_rect;

# endif