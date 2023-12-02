
# ifndef __UTILS__C
# define __UTILS__C

# include "./Utils.h"


SDL_Texture *Load_Texture(char *path, SDL_Renderer *render, int *w, int *h)
{
    if (!render)                // given renderer wasn't initialized
    {
        // show error
        fprintf(
            stderr, "%s%s[Error] Render must be initialized. Failed to load texture.%s\n", 
            ANSI_BOLD, ANSI_RED, ANSI_RESET
        );
        fflush(stderr);
        return NULL;
    }

    SDL_Texture *new_texture = NULL;
    SDL_Surface *loaded_img = IMG_Load(path);   // load image from path

    if (!loaded_img)        // failed to load image
    {
        // show error
        char *err_msg[2] = {
            "[Error] Failed to load image from ",
            path
        };
        Shows_SDL_error(err_msg, 2, ANSI_RED);
    }
    else                    // loaded image
    {
        // create & assign texture
        new_texture = SDL_CreateTextureFromSurface(render, loaded_img);

        if (!new_texture)   // failed to create texture
        {
            // show error
            char *err_msg[1] = {
                "[Error] Failed to create texture from surface"
            };
            Shows_SDL_error(err_msg, 1, ANSI_RED);
        }
        else if (w && h)    // created texture & `w` and `h` were given
        {
            // store width & heigth to it
            *w = loaded_img->w;
            *h = loaded_img->h;
        }
        
        SDL_FreeSurface(loaded_img);    // free loaded image
    }

    // if it failed to create texture, `NULL` will be returned
    return new_texture;
}


void Shows_SDL_error(char **head_of_err_msg, int len, char *color)
{
    FILE *fp = stderr;                  // a file pointer that represent `stderr`

    for (int i = 0; i < len; i++)
    {
        fprintf(                                // print given error message to `stderr`
            fp, "%s%s%s", 
            ANSI_BOLD, color, head_of_err_msg[i]
        );     
    }

    fprintf(                                    // print `SDL_GetError()` at the end of `stderr`
        fp, "\t: %s%s%s\n", 
        ANSI_UNDERLINE, SDL_GetError(), ANSI_RESET
    );
    
    fflush(fp);                                 // fflush `stderr` to show every error message
}


# endif