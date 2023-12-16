
# ifndef __MAIN__C
# define __MAIN__C

# include "./main.h"



int main()
{
    Init_sdl();
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

        if (Character->is_dead)
        {
            printf("hi\n");
        }
        
        for (int i = 0; i < NUM_OF_ENEMYS_STAGE_1; i++)
        {
            Apply_Enemy_Player_physics(Character, Enemy_arr_stage_1[i]);
            Patrol_Enemy(Enemy_arr_stage_1[i], Stage_1);
        }

        Act_player();

        if (Character->is_dead && !flag)
        {
            Mix_PauseMusic();
            flag = true;
        }

        if (!Character->is_dead && flag)
        {
            Mix_PlayMusic(Bgm, -1);
            flag = false;
        }

        for (int i = 0; i < NUM_OF_ENEMYS_STAGE_1; i++)
        {
            Render_Enemy(Enemy_arr_stage_1[i], Main_Window_Renderer, Character->GlobalPos_x, Character->WindowPos_x);
        }
        Render();

        Uint64 end = SDL_GetTicks();

        int time_milli = 1 / FPS * 1000;
        if (end - start < time_milli)
        {
            SDL_Delay(time_milli - (end - start));
        }

        # ifdef DEBUG
            printf("%5.2f\t%5.2f\n", Character->Speed_x, Character->Speed_y);
            printf("%5.2f\t%5.2f\n", Character->WindowPos_x, Character->WindowPos_y);
            printf("%5.2f\t%5.2f\n", Character->GlobalPos_x, Character->GlobalPos_y);
            printf("%llu\n", time_milli - (end - start));
            printf("\n");
        # endif
    }

    dispose_player(Character);
    dispose_map(Stage_1);

    SDL_DestroyRenderer(Main_Window_Renderer);
    SDL_DestroyWindow(Main_Window);
    SDL_Quit();

    printf("\nProgram ended with no error\n");

    return 0;
}

# endif
