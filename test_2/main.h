
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

void Render()
{
    Render_Map(Stage_1, Main_Window_Renderer, Character->GlobalPos_x, Character->WindowPos_x);
    Render_Player(Character, Main_Window_Renderer);

    SDL_FRect dst_rect = {
        20, WIN_HEIGHT / 2 - 78,
        690, 78
    };

    if (Character->is_dead)
    {
        SDL_RenderCopyF(Main_Window_Renderer, Message_texture_WHOLE, &Message_src_rects[MSG_DEATH], &dst_rect);
    }
    else if (Character->is_clear)
    {
        SDL_RenderCopyF(Main_Window_Renderer, Message_texture_WHOLE, &Message_src_rects[MSG_CLEAR], &dst_rect);
    }

    SDL_RenderPresent(Main_Window_Renderer);
}

# endif