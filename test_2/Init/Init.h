
# ifndef __INIT__H
# define __INIT__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include "../def.h"

extern SDL_Window   *Main_Window;
extern SDL_Renderer *Main_Window_Renderer;

extern SDL_Texture *Block_texture_WHOLE;
extern SDL_Texture *Block_texture_INVISIBLE;
extern SDL_Texture *Message_texture_WHOLE;

extern SDL_Rect Block_src_rects[NUM_OF_BLOCK_KIND];
extern SDL_Rect Message_src_rects[NUM_OF_MSG_TEXT];

extern Player   *Character;
extern Map      *Stage_1;

void Init_block_tesxtures();

void Init_msg_textures();

bool Init_sdl();

void Init_player();

void Init_map();

extern void Shows_SDL_error(char **head_of_err_msg, int len, char *color);

# endif