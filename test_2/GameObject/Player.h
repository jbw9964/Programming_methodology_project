
# ifndef __PLAYER__H
# define __PLAYER__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include "../def.h"
# include "../Init/Map.h"


/**
 * @brief   The state that `Player` can have.
 *  
 * @param   `LEFT`    player is moving to left
 * @param   `RIGHT`   player is moving to right
 * @param   `DEATH`   player is dead
 */
typedef enum Player_State
{
    LEFT,
    RIGHT,
    DEATH_LEFT,
    DEATH_RIGHT
} Player_State;

/**
 * @brief   A structure that record keyboard input
 * @param   `directions`    if user pushes keyboard, structure will store the status
*/
typedef struct Keyboard
{
    bool Up, Down, Left, Right, Restart;
} Keyboard;

/**
 * @brief   A structure that represent the character of player.
 *  
 * @param   `Tex`           the texture to render character
 * @param   `Src_rect[]`    the array of `SDL_Rect *`, each `rect` represent the position of `Tex` depends on `Current_state`
 * @param   `Current_state` the state that character have (`NORMAL`, `JUMP`, `RUN`)
 * @param   `Key`           a structure that record keyboard input from user
 *  
 * @param   `GlobalPos_~`   the global position of character (`MAP`)
 * @param   `WindowPos_~`   the relative position of character with window (`WINDOW`, `RELATIVE`)
 * @param   `Speed_~`       the speed of character, it will be limited by `MAX_SPEED_X` & `MAX_SPEED_Y`
 * @param   `is_dead`       represent player is dead or not
 */
typedef struct Player
{
    SDL_Texture *Tex;
    SDL_Rect Src_rect[NUM_OF_PLAYER_STATE];
    Player_State Current_state;
    Keyboard Key;

    float GlobalPos_x;
    float GlobalPos_y;
    float WindowPos_x;
    float WindowPos_y;
    float Speed_x;
    float Speed_y;
    bool is_dead;
    bool is_clear;
} Player;

/*
 * @brief   Create `Player` structure with given arguments.
 *  
 * @param   `path`      path to PNG image
 * @param   `render`    `SDL_Renderer *` to render image
 *  
 * @return  `Player *`  :   allocated memory
 * @warning `Player` will be created (`WIN_WIDTH / 2`, `WIN_HEIGHT / 2`) (x, y) position initially, the middle of shown window.
 */
Player *Create_Player(char *path, SDL_Renderer *render);

void Kill_Player(Player *character);

// @brief   Assign `character->Src_rect[]` with each `Player` states.
void Assign_Player_Rect(Player *character, SDL_Rect *src_rect_arr[NUM_OF_PLAYER_STATE]);

/**
 * @brief   Record keyboard input to given `record` (`Keyboard *`).
 * 
 * @param   `record`    a `Keyboard *` to store user input from keyboard
 * @param   `event`     `SDL_Event *` to receive user input
 * 
 * @warning If `record` or `event` wasn't initialized, raise error.
 */
void Record_KeyState(Keyboard *record, SDL_Event *event);

/**
 * @brief   Receive a keyboard input & store the status to given parameters.
 * 
 * @param   `character` a `Player *` to store keyboard status, it also refresh other data (`Speed_~` member)
 * @param   `map`       a `Map *` that represent current map
 * @param   `event`     `SDL_Event` to receive user input
 * @param   `flag`      a `bool *` to quit, if given event is `SDL_QUIT`, `*flag` will be set to true
 */
void Receive_Keyboard_input(Player *character, Map *map, SDL_Event *event, bool *quit_flag);

/**
 * @brief   Move player to given coordinate. `character` will be shown to upper-middle window. (`X` : middle, `Y` : `global_y`)
 *  
 * @param   `character` `Player *` to adjust coordinate
 * @param   `global_~`  global position to move
 *  
 * @warning It will automatically set `character`'s `speed_~` to `zero`, and `Current_state` to `NORMAL`.
 */
void Adjust_Player_position(Player *character, float global_x, float global_y);

/**
 * @brief   Add given `speed_~` to `character`. Each velocity will be limited by `MAX_SPEED_X` & `MAX_SPEED_Y`, even if `speed_~` were given.
 *  
 * @param   `character`     `Player *` to add speed
 * @param   `speed_x`       speed x
 * @param   `speed_y`       speed y
 *  
 * @warning `Accelerate_Player` doesn't actually adjust the coordinates of `character`. 
 * It only gives the velocity. To adjust it, use `Move_Player` function.
 */
void Accelerate_Player(Player *character, float speed_x, float speed_y);

// @brief   Set `character`'s `speed_x` as `zero`.
void Stop_Player_x(Player *character);
// @brief   Set `character`'s `speed_y` as `zero`.
void Stop_Player_y(Player *character);
// @brief   Set `character`'s `speed_~` as `zero`.
void Stop_Player(Player *character);

// @brief   Adjust `character`'s position with it's `speed_~` member.
void Move_Player(Player *character);

/**
 * @brief   Apply `Block interruption` to character. It will prevents `character` from moving across the `Block`.
 *  
 * @details In four direction (`Up`, `Down`, `Left`, `Right`), if `Block` exists to these direction, and `character` has velocity forward to it, 
 * function will set thoese velocity to `zero` and adjust `character`'s global & window position.
 *  
 *  It prevents `character` from moving across the `Block`.
 *  
 * @param   `character`     `Player *` to apply physics
 * @param   `map`           `Map *` to load map data
 */
void Apply_Block_Interruption(Player *character, Map *map);

void Apply_Block_Object_logic(Player *character, Map *map);

// @brief   Render `character` to given `render`, using it's `GlobalPos`, `WindowPos` members.
void Render_Player(Player *character, SDL_Renderer *render);

// @brief   Free allocated memory assigned to `character`.
void dispose_player(Player *character);

extern SDL_Texture *Load_Texture(char *path, SDL_Renderer *render, int *w, int *h);

# endif