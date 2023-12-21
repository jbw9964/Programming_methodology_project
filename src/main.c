
# ifndef __MAIN__C
# define __MAIN__C

# include "./main.h"

int main()
{
    if (!Init_sdl())
    {
        printf("Shutting down program...\n");
        return 1;
    }
    
    Init_block_tesxtures();
    Init_msg_textures();
    Init_map();
    Init_player();

    Init_enemy();

    Init_sounds();
    Mix_PlayMusic(Bgm, -1);

    bool quit_flag = false;
    SDL_Event event;

    bool flag = false;
    while (!quit_flag)
    {
        Uint64 start = SDL_GetTicks();
        SDL_RenderClear(Main_Window_Renderer);

        Receive_Keyboard_input(Character, Stage_1, &event, &quit_flag);

        Act_Enemy();
        Act_player();

        Stop_BGM(&flag);
        Rewind_BGM(&flag);

        Render();

        Uint64 end = SDL_GetTicks();

        int time_milli = 1 / FPS * 1000;
        if (end - start < time_milli)
        {
            SDL_Delay(time_milli - (end - start));
        }
    }

    Quit();

    # ifdef DEBUG
        printf("\nProgram ended with no error\n");
    # endif

    return 0;
}

# endif
