
# ifndef __MAIN__H
# define __MAIN__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>

# include "./def.h"
# include "./GameObject/Player.c"
# include "./GameObject/Enemy.c"
# include "./Utils/Utils.c"
# include "./Init/Map.c"
# include "./Init/Init.c"

// @brief   A `SDL_Window *` to shows directly to user.
SDL_Window      *Main_Window;

// @brief   A `SDL_Renderer *` of \ref `Main_window`.
SDL_Renderer    *Main_Window_Renderer;

Player      *Character;
Map         *Stage_1;

Mix_Music   *Bgm;
Mix_Chunk   *Death_effect;
Mix_Chunk   *Jump_effect;
Mix_Chunk   *Item_effect;
Mix_Chunk   *Step_effect;
Mix_Chunk   *Block_break_effect;
Mix_Chunk   *Block_blocked_effect;

void Act_player()
{
    if (Character->GlobalPos_y >= MAP_HEIGTH)
    {
        if (!Character->is_dead && Death_effect)    {Mix_PlayChannel(-1, Death_effect, 0);}
        Character->is_dead = true;
    }

    if (Character->is_dead)     {Stop_Player(Character);}
    else
    {
        Accelerate_Player(Character, 0, GRAVITY);
        Apply_Block_Interruption(Character, Stage_1);
        Apply_Block_Object_logic(Character, Stage_1);
        Move_Player(Character);
    }
}

void Act_Enemy()
{
    for (int i = 0; i < NUM_OF_ENEMYS_STAGE_1; i++)
    {
        Apply_Enemy_Player_physics(Character, Enemy_arr_stage_1[i]);
        Patrol_Enemy(Enemy_arr_stage_1[i], Stage_1);
    }
}

void Stop_BGM(bool *flag)
{
    if (Character->is_dead && !(*flag))
    {
        Mix_PauseMusic();
        *flag = true;
    }
}
void Rewind_BGM(bool *flag)
{
    if (!Character->is_dead && *flag)
    {
        Mix_PlayMusic(Bgm, -1);
        *flag = false;
    }
}


void Render()
{
    Render_Map(Stage_1, Main_Window_Renderer, Character->GlobalPos_x, Character->WindowPos_x);
    Render_Player(Character, Main_Window_Renderer);

    SDL_FRect dst_rect_1 = {
        20, WIN_HEIGHT / 2 - 78,
        690, 78
    };

    SDL_FRect dst_rect_2 = {
        690 / 2 - 190 / 2, WIN_HEIGHT * 3 / 4 - 78,
        690 / 4, 39
    };

    for (int i = 0; i < NUM_OF_ENEMYS_STAGE_1; i++)
    {
        Render_Enemy(Enemy_arr_stage_1[i], Main_Window_Renderer, Character->GlobalPos_x, Character->WindowPos_x);
    }
    
    if (Character->is_dead)
    {
        SDL_RenderCopyF(Main_Window_Renderer, Message_texture_WHOLE, &Message_src_rects[MSG_DEATH], &dst_rect_1);
        SDL_RenderCopyF(Main_Window_Renderer, Message_texture_WHOLE, &Message_src_rects[MSG_RESTART], &dst_rect_2);
    }
    else if (Character->is_clear)
    {
        SDL_RenderCopyF(Main_Window_Renderer, Message_texture_WHOLE, &Message_src_rects[MSG_CLEAR], &dst_rect_1);
        SDL_RenderCopyF(Main_Window_Renderer, Message_texture_WHOLE, &Message_src_rects[MSG_RESTART], &dst_rect_2);
    }

    SDL_RenderPresent(Main_Window_Renderer);
}

void Quit()
{
    for (int i = 0; i < NUM_OF_ENEMYS_STAGE_1; i++)
    {
        dispose_enemy(Enemy_arr_stage_1[i]);
    }
    dispose_player(Character);
    dispose_map(Stage_1);
    SDL_DestroyRenderer(Main_Window_Renderer);
    SDL_DestroyWindow(Main_Window);
    SDL_Quit();
}

# endif