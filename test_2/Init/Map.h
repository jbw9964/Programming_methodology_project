
# ifndef __MAP__H
# define __MAP__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>

# include "../def.h"

int Stage_1_Map[STAGE_1_COL][STAGE_1_ROW] = {
    { 1,0,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,9,0,0,0,0,0, 0,0,9,0,0,0,0,0,0,0, 0,0,0,0,9,0,0,0,0,0, 1,1,1,1,1,0,0,0,0,0, 0,0,0,0,0,9,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,0,0,0, 0,2,2,2,1},
    { 1,0,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,9,0,0,0,0,0, 0,0,9,0,0,0,0,0,0,0, 0,0,0,0,9,0,0,0,0,0, 0,1,1,1,1,0,0,0,0,0, 0,0,0,0,0,9,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,0,0,0, 0,2,7,2,1},
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,9,1,0,0,0,0, 0,0,9,0,0,0,0,0,0,0, 0,0,0,0,9,0,0,0,1,0, 0,0,1,1,1,0,0,0,0,0, 0,5,0,5,0,9,0,0,0,0, 0,0,0,1,1,1,1,1,1,0, 0,1,0,0,0,0,0,0,0,0, 0,2,0,2,1},
    { 1,0,0,0,2,1,1,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,9,0,0,0,1,0, 0,0,0,1,1,0,0,0,1,0, 1,1,1,1,1,0,1,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,1,0,0,1,1,1,1,1,0, 0,2,2,2,1},
    { 1,0,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,1,1,1,0, 0,0,0,0,0,0,0,0,9,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,9,9,0,1,0, 0,0,0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,0,0,0, 0,1,0,0,0,0,0,0,0,0, 9,0,0,0,1},
    { 1,1,1,0,0,0,0,0,0,0, 0,9,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,9, 0,0,0,0,0,0,0,1,1,0, 0,0,0,0,0,0,0,0,0,5, 0,0,4,0,0,0,0,0,0,0, 0,0,0,0,0,0,9,0,0,0, 0,0,0,0,0,0,0,4,0,0, 0,0,0,0,5,0,0,0,2,0, 0,1,0,0,0,0,0,0,0,0, 0,9,0,0,1},
    { 1,0,0,0,0,6,0,0,0,0, 0,0,1,9,9,0,0,0,0,0, 0,0,1,1,1,0,0,1,0,2, 1,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 5,0,5,0,5,0,0,1,0,0, 0,0,0,1,1,0,0,0,2,0, 0,1,0,0,0,0,0,0,0,0, 0,1,2,1,1},
    { 1,0,0,0,1,1,0,0,1,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,5,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,0,1,0, 0,0,0,0,0,0,0,0,0,1, 1,1,1,1,1,0,0,0,0,0, 0,0,0,9,0,0,0,0,0,0, 0,1,0,0,0,0,2,2,2,0, 0,0,0,0,1},
    { 1,0,0,0,0,0,0,0,0,0, 1,0,0,0,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,2,0,0,1,9,0,0,1, 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,1,0,1,0, 0,0,0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,0,0, 0,0,0,9,0,0,0,0,0,0, 0,1,0,0,0,0,0,0,0,0, 0,0,0,0,1},
    { 1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,1,1,0,0,0, 0,0,2,0,0,1,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,1,0,1,0,2,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,0,0,0,0,0,1,0,0,0, 0,0,0,9,0,0,0,1,1,1, 0,1,1,1,0,0,0,0,0,1, 1,0,0,0,1},
    { 1,0,0,0,0,5,0,0,0,0, 0,5,1,0,0,0,0,0,0,1, 1,1,0,0,0,0,0,0,0,3, 0,0,2,1,1,0,0,0,0,0, 0,0,0,0,0,1,0,0,0,0, 1,0,1,0,1,0,2,0,0,0, 0,0,0,0,0,1,0,0,0,0, 0,5,5,5,0,0,1,0,0,0, 0,1,1,0,0,0,0,0,2,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1},
    { 1,0,1,0,9,1,9,0,0,0, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,3,3, 0,0,0,0,0,0,0,1,1,0, 0,0,0,0,0,0,0,0,1,0, 1,0,0,0,0,0,2,0,0,0, 1,0,0,0,1,1,1,0,0,0, 1,1,1,1,1,0,1,0,0,0, 0,0,0,0,0,0,0,0,2,0, 0,0,0,0,0,1,1,1,1,0, 0,0,1,1,1},
    { 1,0,0,0,0,0,0,0,0,1, 0,0,1,0,1,0,0,0,0,0, 0,0,0,0,0,0,5,3,3,3, 0,0,0,0,0,0,0,0,0,0, 0,0,1,1,0,0,0,0,1,0, 0,0,0,0,0,0,2,9,1,0, 1,0,0,0,1,1,1,5,0,0, 0,0,0,0,0,0,0,0,1,1, 0,0,0,0,1,1,0,0,2,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1},
    { 1,0,0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,3,3,3,3, 0,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,9, 0,0,0,0,1},
    { 1,0,0,0,0,0,0,0,0,4, 0,0,1,4,0,0,0,0,0,0, 0,0,5,0,0,3,3,3,3,3, 0,1,1,0,0,0,0,0,0,0, 0,0,0,0,4,5,0,0,0,0, 0,4,4,0,0,0,0,0,0,0, 0,0,0,1,1,1,1,1,1,0, 0,0,5,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,5,0,0,0,0,0,0,0, 0,0,0,0,1},
    { 1,3,3,3,3,3,0,0,0,3, 3,3,3,3,0,3,3,3,3,3, 0,0,3,3,3,3,3,3,3,3, 3,3,3,3,0,0,3,3,3,3, 3,0,0,0,3,3,3,3,3,0, 0,3,3,3,3,3,3,0,0,3, 3,3,0,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,0,0,3, 3,3,0,0,0,3,3,3,3,0, 0,3,3,3,3,3,3,0,0,3, 3,3,3,3,1}
};

/*
0 : Empty Space       |
1 : Unbreakable Block |
2 : breakable Block   |
3 : Base              |
4 : Thorn             |
5 : Mine              |    -> Same Numbering with "SDL_Rect"
6 : Black-Hole        |
7 : Flag              |
8 : free space        |
9 : Invisible Block   |     
*/

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

SDL_Texture *Block_texture_WHOLE;           // texture that holds every block
SDL_Texture *Block_texture_INVISIBLE;       // texture that holds invisible block
SDL_Texture *Message_texture_WHOLE;         // texture that holds every message image

SDL_Rect Block_src_rects[NUM_OF_BLOCK_KIND];
SDL_Rect Message_src_rects[NUM_OF_MSG_TEXT];

SDL_Rect Message_src_rect1; // clear
SDL_Rect Message_src_rect2; // dead

# endif