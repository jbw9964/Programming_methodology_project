
# ifndef __MAIN__C
# define __MAIN__C

# include "./main.h"

int FPS = 60;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    IMG_Init(IMG_INIT_PNG);

    Main_Window = SDL_CreateWindow(
        "main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WIN_WIDTH, WIN_HEIGHT, 
        SDL_WINDOW_SHOWN
        // SDL_WINDOW_RESIZABLE
    );
    
    Main_Window_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);

    Map *test_map = Load_Map(&TestMap[0][0], TEST_MAP_HEIGHT, TEST_MAP_WIDTH);
    init_block();

    Player *character = Create_Player("../asset/image/character.png", Main_Window_Renderer);
    {
        SDL_Rect *src_rects[NUM_OF_PLAYER_STATE];

        src_rects[NORMAL] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[NORMAL]->x = 15;
        src_rects[NORMAL]->y = 30;
        src_rects[NORMAL]->w = 30;
        src_rects[NORMAL]->h = 30;

        src_rects[RUN] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[RUN]->x = 45;
        src_rects[RUN]->y = 30;
        src_rects[RUN]->w = 30;
        src_rects[RUN]->h = 30;

        src_rects[JUMP] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[JUMP]->x = 45;
        src_rects[JUMP]->y = 30;
        src_rects[JUMP]->w = 30;
        src_rects[JUMP]->h = 30;

        Assign_Player_Rect(character, src_rects);

        for (int i = 0; i < NUM_OF_PLAYER_STATE; i++)
        {
            free(src_rects[i]);
            src_rects[i] = NULL;
        }
    }

    init_enemy();


    bool quit_flag = false;
    SDL_Event event;

    while (!quit_flag)
    {
        Uint64 start = SDL_GetTicks64();

        SDL_SetRenderDrawColor(Main_Window_Renderer, 255, 255, 255, 255);
        SDL_RenderClear(Main_Window_Renderer);

        Receive_Keyboard_input(character, test_map, &event, &quit_flag);
        Accelerate_Player(character, 0, -1 * MAX_SPEED_Y / 50);
        Apply_physics(character, test_map);
        Apply_Enemy_Player_physics(character, test_enemy);
        Apply_Enemy_Player_physics(character, test_enemy_2);

        Move_Player(character);
        Patrol_Enemy(test_enemy, test_map);
        Patrol_Enemy(test_enemy_2, test_map);

        Render_Map(test_map, Main_Window_Renderer, character->GlobalPos_x, character->WindowPos_x);
        Render_Enemy(test_enemy, Main_Window_Renderer, character->GlobalPos_x, character->WindowPos_x);
        Render_Enemy(test_enemy_2, Main_Window_Renderer, character->GlobalPos_x, character->WindowPos_x);
        Render_Player(character, Main_Window_Renderer);

        if (character->GlobalPos_y >= MAP_HEIGTH)       {quit_flag = true;}
        if (character->is_dead)                         {quit_flag = true;}

        SDL_RenderPresent(Main_Window_Renderer);

        Uint64 end = SDL_GetTicks64();

        int time_milli = (float) 1 / FPS * 1000;
        if (end - start < time_milli)
        {
            SDL_Delay(time_milli - (end - start));
        }

        # ifdef DEBUG
            printf("%5.2f\t%5.2f\n", character->Speed_x, character->Speed_y);
            printf("%5.2f\t%5.2f\n", character->WindowPos_x, character->WindowPos_y);
            printf("%5.2f\t%5.2f\n", character->GlobalPos_x, character->GlobalPos_y);
            printf("%llu\n", time_milli - (end - start));
            printf("\n");
        # endif
    }

    dispose_enemy(test_enemy);
    dispose_enemy(test_enemy_2);
    dispose_player(character);
    dispose_map(test_map);

    SDL_DestroyRenderer(Main_Window_Renderer);
    SDL_DestroyWindow(Main_Window);
    SDL_Quit();

    printf("\nProgram ended with no error\n");

    return 0;
}

# endif
