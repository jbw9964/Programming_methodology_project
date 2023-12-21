
# ifndef __UTILS__H
# define __UTILS__H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include "../def.h"


/**
 * @brief   Load texture from `path`. If `w` & `h` were given, store the width and heigth of image to it.
 * 
 * @param   `path`      path to PNG image
 * @param   `render`    `SDL_Renderer *` to create texture
 * @param   `w`         integer pointer to store width of texture
 * @param   `h`         integer pointer to store height of texture
 * 
 * @return  `SDL_Texture *`     :   loaded texture
 */
SDL_Texture *Load_Texture(char *path, SDL_Renderer *render, int *w, int *h);


/**
 * @brief   A function to shows `SDL_GetError()` with given strings. It can be used to show `error` or `warnings`.
 *  
 * @param   `head_of_err_msg`   An array of `char *` that represent the custom messages.
 * @param   `len`               The length of an array, `char **heads_of_err_msg`.
 * @param   `color`             The color to display messages.
 * 
 * @details This function shows `SDL_GetError()` with given strings. The strings are passed to `stderr`.
 *          The given strings will be printed first, and `SDL_GetError()` will be last.
 *          For example,
 *  
 *          ```c
 *          char *err_msgs[2] = {"MSG_1", "MSG_2"};
 *          shows_SDL_error(err_msgs, 2);
 *          ```
 *  
 *          ```
 *          "`MSG_1``MSG_2`\t: `SDL_GetError()`\n"
 *          ```
 *          
 *          will be printed to `stderr`.
 *  
 *          "`MSG_1``MSG_2`\t:" will be printed BOLD & COLORED
 *          "`SDL_GetError()`"  will be printed BOLD & COLORED & UNDERLINED
 */
void Shows_SDL_error(char **head_of_err_msg, int len, char *color);


# endif
