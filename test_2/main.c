
# ifndef __MAIN__C
# define __MAIN__C

# include "./main.h"

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

    Player *character = Create_Player("../asset/image/player.png", Main_Window_Renderer);

    Map *test_map = Load_Map(&TestMap[0][0], TEST_MAP_HEIGHT, TEST_MAP_WIDTH);
    init_block();

    bool quit_flag = false;
    SDL_Event event;

    const Uint8 *pKey = SDL_GetKeyboardState(NULL);

    while (!quit_flag)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)     {quit_flag = true;}
            else if (event.type == SDL_KEYUP)
            {
                Stop_Player(character);
            }
        }
        
        SDL_SetRenderDrawColor(Main_Window_Renderer, 255, 255, 255, 255);
        SDL_RenderClear(Main_Window_Renderer);

        if (pKey[SDL_SCANCODE_UP])
        {
            Accelerate_Player(character, 0, MAX_SPEED_Y);
        }
        if (pKey[SDL_SCANCODE_LEFT])
        {
            Accelerate_Player(character, -1 * MAX_SPEED_X / 20, 0);
        }
        if (pKey[SDL_SCANCODE_RIGHT])
        {
            Accelerate_Player(character, MAX_SPEED_X / 20, 0);
        }

        Accelerate_Player(character, 0, -1 * MAX_SPEED_Y / 10);
        Apply_physics(character, test_map);

        Move_Player(character);
        SDL_Rect src_rect = {0, 0, 30, 30};

        if (character->Current_state == RUN)
        {
            src_rect.x = 30;
        }
        else if (character->Current_state == JUMP)
        {
            src_rect.x = 60;
        }

        SDL_FRect dst_rect = {character->WindowPos_x, character->WindowPos_y, 30, 30};

        // printf("%5.2f\t%5.2f\n", character->Speed_x, character->Speed_y);
        // printf("%5.2f\t%5.2f\n", character->WindowPos_x, character->WindowPos_y);
        // printf("%5.2f\t%5.2f\n", character->GlobalPos_x, character->GlobalPos_y);
        // printf("\n");

        Render_Map(test_map, Main_Window_Renderer, character->GlobalPos_x, character->WindowPos_x);
        SDL_RenderCopyF(Main_Window_Renderer, character->Tex, &src_rect, &dst_rect);

        SDL_RenderPresent(Main_Window_Renderer);

        SDL_Delay(10);
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