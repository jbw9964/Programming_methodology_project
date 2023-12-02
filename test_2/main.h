
# ifndef __MAIN__H
# define __MAIN__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include "./def.h"

// @brief   A `SDL_Window *` to shows directly to user.
SDL_Window      *Main_Window;

// @brief   A `SDL_Renderer *` of \ref `Main_window`.
SDL_Renderer    *Main_Window_Renderer;

# include "./GameObject/Player.c"
# include "./Utils/Utils.c"
# include "./Init/Map.c"

# endif