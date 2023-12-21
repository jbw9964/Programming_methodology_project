
# ifndef __ENEMY__H
# define __ENEMY__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>

# include "../def.h"
# include "./Player.h"
# include "../Init/Map.h"


// @brief   A enumerate that represent the moving direction of enemy
typedef enum Enemy_Direction{
    ENEMY_LEFT,
    ENEMY_RIGHT
} Enemy_Direction;

/**
 * @brief   A structure that represent the enemy.
 *  
 * @param   `Tex`               the texture to render enemy
 * @param   `Src_rect[]`        the array of `SDL_Rect *`, each `rect` represent the position of `Tex` depends on `Current_direction`
 * @param   `Current_direction` the moving direction of enemy (`ENEMY_LEFT`, `ENEMY_RIGHT`)
 *  
 * @param   `GlobalPos_~`       the global position of enemy (`MAP`)
 * @param   `WindowPos_~`       the relative position of enemy with window (`WINDOW`, `RELATIVE`)
 *  
 * @param   `Moving_speed`      the moving speed of enemy
 * @param   `is_dead`           represent enemy is dead or not
 *  
 * @details The `GlobalPos_x` will be calculated by `+= Moving_speed * UNIT_TIME_STEP` in `Patrol_Enemy` function.
 */
typedef struct Enemy_Object
{
    SDL_Texture *Tex;
    SDL_Rect Src_rect[NUM_OF_ENEMY_DIRECTION];
    Enemy_Direction Current_direction;
    
    float GlobalPos_x;
    float GlobalPos_y;
    float WindowPos_x;
    float WindowPos_y;

    float Moving_speed;
    bool is_dead;
} Enemy_Object;


/**
 * @brief   Create `Enemy_Object` structure with given arguments.
 * 
 * @param   `path`              path to load PNG image 
 * @param   `render`            `SDL_Renderer *` to render image
 * @param   `global_~`          the global coordinate to spawn enemy
 *  
 * @return  `Enemy_Object *`    :   allocated memory
 */
Enemy_Object *Create_Enemy_Object(char *path, SDL_Renderer *render, float global_x, float global_y);

// @brief   Assign `enemy->Src_rect[]` with each `Enemy_Direction`.
void Assign_Enemy_Rect(Enemy_Object *enemy, SDL_Rect *src_rect_arr[NUM_OF_ENEMY_DIRECTION]);

/**
 * @brief   Move `enemy` left or rigth with it's coordinate.
 *  
 * @param   `enemy`     `Enemy_Object *` to patrol
 * @param   `map`       `Map *` to read map data 
 *  
 * @details `enemy` will patrol left or right. If `enemy` encounter obstacle or clif, it will change direction and keep moving.
 * And if `enemy` is dead (`is_dead=true`), it will do nothing.
 * @warning If `enemy` or `map` or `map->Map_data` wasn't initialized, it will do nothing.
 */
void Patrol_Enemy(Enemy_Object *enemy, Map *map);

/**
 * @brief   Apply `Enemy & character physics`.
 * 
 * @details If `character` steps on `enemy`, it will kill enemy & bouns a bit. Else if `character` encounters `enemy`, it will kill `character`.
 * Kill means `is_dead=true`.
 */
void Apply_Enemy_Player_physics(Player *character, Enemy_Object *enemy);

// @brief   Render `enemy` to given arguments. It acquire chracter's `global position` & `window position`.
void Render_Enemy(Enemy_Object *enemy, SDL_Renderer *render, float character_global_x, float character_window_x);

// @brief   Free allocated memory assigned to `enemy`.
void dispose_enemy(Enemy_Object *enemy);

extern SDL_Texture *Load_Texture(char *path, SDL_Renderer *render, int *w, int *h);

Enemy_Object *Enemy_arr_stage_1[NUM_OF_ENEMYS_STAGE_1];

extern SDL_Renderer *Main_Window_Renderer;

extern Mix_Chunk   *Death_effect;
extern Mix_Chunk   *Jump_effect;
extern Mix_Chunk   *Item_effect;
extern Mix_Chunk   *Step_effect;
extern Mix_Chunk   *Block_break_effect;
extern Mix_Chunk   *Block_blocked_effect;

# endif