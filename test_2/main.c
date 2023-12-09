
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

    Player *character = Create_Player("../asset/image/player.png", Main_Window_Renderer);    
    {
        SDL_Rect *src_rects[NUM_OF_PLAYER_STATE];

        src_rects[NORMAL] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[NORMAL]->x = 45;
        src_rects[NORMAL]->y = 36;
        src_rects[NORMAL]->w = UNIT_PIXEL*1.1;
        src_rects[NORMAL]->h = UNIT_PIXEL*1.1;

        src_rects[RUN] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[RUN]->x = 45;
        src_rects[RUN]->y = 36;
        src_rects[RUN]->w = UNIT_PIXEL*1.1;
        src_rects[RUN]->h = UNIT_PIXEL*1.1;

        src_rects[JUMP] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[JUMP]->x = 45;
        src_rects[JUMP]->y = 36;
        src_rects[JUMP]->w = UNIT_PIXEL*1.1;
        src_rects[JUMP]->h = UNIT_PIXEL*1.1;

        // Now, Same Image for Three state

        Assign_Player_Rect(character, src_rects);

        for (int i = 0; i < NUM_OF_PLAYER_STATE; i++)
        {
            free(src_rects[i]);
            src_rects[i] = NULL;
        }
    }

    bool quit_flag = false;
    SDL_Event event;

    while (!quit_flag)
    {
        Uint64 start = SDL_GetTicks();
        Receive_Keyboard_input(character, test_map, &event, &quit_flag);

        if (character->GlobalPos_y >= MAP_HEIGTH)    {quit_flag = true;}
        
        SDL_SetRenderDrawColor(Main_Window_Renderer, 255, 255, 255, 255);
        SDL_RenderClear(Main_Window_Renderer);

        Accelerate_Player(character, 0, -1 * MAX_SPEED_Y / 50);
        Apply_physics(character, test_map);

        Move_Player(character);

        Render_Map(test_map, Main_Window_Renderer, character->GlobalPos_x, character->WindowPos_x);
        Render_Player(character, Main_Window_Renderer);

        SDL_RenderPresent(Main_Window_Renderer);

        Uint64 end = SDL_GetTicks();

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

    dispose_player(character);
    dispose_map(test_map);

    SDL_DestroyRenderer(Main_Window_Renderer);
    SDL_DestroyWindow(Main_Window);
    SDL_Quit();

    printf("\nProgram ended with no error\n");

    return 0;
}

# endif
