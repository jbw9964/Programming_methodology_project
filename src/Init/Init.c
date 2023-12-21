
# ifndef __INIT__C
# define __INIT__C

# include "./Init.h"
# include "../GameObject/Enemy.h"

void Init_block_tesxtures()
{
    Block_texture_WHOLE = Load_Texture("../asset/image/block2.png", Main_Window_Renderer, NULL, NULL);

    // Texture Loading for Invisible Block
    Block_texture_INVISIBLE = Load_Texture("../asset/image/block2.png", Main_Window_Renderer, NULL, NULL);
    // Invisible Block's Alpha modulating
    SDL_SetTextureAlphaMod(Block_texture_INVISIBLE, 35); 

    {   // assign rectangular coordinates to each block
        // Unbreakable Block
        Block_src_rects[BLOCK_UNBREAKABLE].x = 123;
        Block_src_rects[BLOCK_UNBREAKABLE].y = 45;
        Block_src_rects[BLOCK_UNBREAKABLE].w = 30;
        Block_src_rects[BLOCK_UNBREAKABLE].h = 30;

        // breakable Block
        Block_src_rects[BLOCK_BREAKABLE].x = 200;
        Block_src_rects[BLOCK_BREAKABLE].y = 43;
        Block_src_rects[BLOCK_BREAKABLE].w = 30;
        Block_src_rects[BLOCK_BREAKABLE].h = 30;
        
        // Base
        Block_src_rects[BLOCK_SOIL].x = 278;
        Block_src_rects[BLOCK_SOIL].y = 45;
        Block_src_rects[BLOCK_SOIL].w = 30;
        Block_src_rects[BLOCK_SOIL].h = 30;

        // Thorn
        Block_src_rects[BLOCK_THRON].x = 45;
        Block_src_rects[BLOCK_THRON].y = 123;
        Block_src_rects[BLOCK_THRON].w = 30;
        Block_src_rects[BLOCK_THRON].h = 30;

        // Mine
        Block_src_rects[BLOCK_MINE].x = 123;
        Block_src_rects[BLOCK_MINE].y = 123;
        Block_src_rects[BLOCK_MINE].w = 30;
        Block_src_rects[BLOCK_MINE].h = 30/2;
        
        // Black-Hole
        Block_src_rects[BLOCK_BLACK_HOLE].x = 200;
        Block_src_rects[BLOCK_BLACK_HOLE].y = 123;
        Block_src_rects[BLOCK_BLACK_HOLE].w = 30;
        Block_src_rects[BLOCK_BLACK_HOLE].h = 30;
        
        // Flag
        Block_src_rects[BLOCK_FLAG].x = 278;
        Block_src_rects[BLOCK_FLAG].y = 123;
        Block_src_rects[BLOCK_FLAG].w = 30;
        Block_src_rects[BLOCK_FLAG].h = 30;
        
        // Ending Black-Hole
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].x = 200;
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].y = 123;
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].w = 30;
        Block_src_rects[BLOCK_BLACK_HOLE_GOAL].h = 30;
        
        // Invisible Bolck
        Block_src_rects[BLOCK_INVISIBLE].x = 45;
        Block_src_rects[BLOCK_INVISIBLE].y = 45;
        Block_src_rects[BLOCK_INVISIBLE].w = 30;
        Block_src_rects[BLOCK_INVISIBLE].h = 30;
    }
}

void Init_msg_textures()
{
    Message_texture_WHOLE = Load_Texture("../asset/image/clear_dead.png", Main_Window_Renderer, NULL, NULL);
    
    {
        Message_src_rects[MSG_CLEAR].x = 27;
        Message_src_rects[MSG_CLEAR].y = 33;
        Message_src_rects[MSG_CLEAR].w = 30 * 23;
        Message_src_rects[MSG_CLEAR].h = 30 * 2.6;

        Message_src_rects[MSG_DEATH].x = 27;
        Message_src_rects[MSG_DEATH].y = 140;
        Message_src_rects[MSG_DEATH].w = 30 * 23;
        Message_src_rects[MSG_DEATH].h = 30 * 2.6;

        Message_src_rects[MSG_RESTART].x = 27;
        Message_src_rects[MSG_RESTART].y = 114;
        Message_src_rects[MSG_RESTART].w = 190;
        Message_src_rects[MSG_RESTART].h = 25;
    }
}

void Init_sounds()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    Mix_VolumeMusic(BGM_VOLUME);
    
    if (!(Bgm = Mix_LoadMUS("../asset/sound/bgm/field.ogg")))
    {
        fprintf(
            stderr, "%s%s[Warning] Failed to load BGM.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_YELLOW, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }

    if (!(Death_effect = Mix_LoadWAV("../asset/sound/optional/death.ogg")))
    {
        fprintf(
            stderr, "%s%s[Warning] Failed to load BGM.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_YELLOW, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else    {Mix_VolumeChunk(Death_effect, EFFECT_VOLUME);}

    if (!(Jump_effect = Mix_LoadWAV("../asset/sound/object/jump.ogg")))
    {
        fprintf(
            stderr, "%s%s[Warning] Failed to load BGM.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_YELLOW, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else    {Mix_VolumeChunk(Jump_effect, EFFECT_VOLUME);}

    if (!(Item_effect = Mix_LoadWAV("../asset/sound/object/block_coin.ogg")))
    {
        fprintf(
            stderr, "%s%s[Warning] Failed to load BGM.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_YELLOW, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else    {Mix_VolumeChunk(Item_effect, EFFECT_VOLUME);}

    if (!(Step_effect = Mix_LoadWAV("../asset/sound/object/stepped.ogg")))
    {
        fprintf(
            stderr, "%s%s[Warning] Failed to load BGM.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_YELLOW, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else    {Mix_VolumeChunk(Step_effect, EFFECT_VOLUME);}

    if (!(Block_break_effect = Mix_LoadWAV("../asset/sound/object/block_destoryed.ogg")))
    {
        fprintf(
            stderr, "%s%s[Warning] Failed to load BGM.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_YELLOW, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else    {Mix_VolumeChunk(Block_break_effect, EFFECT_VOLUME);}

    if (!(Block_blocked_effect = Mix_LoadWAV("../asset/sound/object/jump_blocked.ogg")))
    {
        fprintf(
            stderr, "%s%s[Warning] Failed to load BGM.%s\n%s:%d\n", 
            ANSI_BOLD, ANSI_YELLOW, ANSI_RESET,
            __FILE__, __LINE__
        );
        fflush(stderr);
    }
    else    {Mix_VolumeChunk(Block_blocked_effect, EFFECT_VOLUME);}
}

bool Init_sdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        char *err_msg[1] = {"[Error] Failed to init SDL2"};
        Shows_SDL_error(err_msg, 1, ANSI_RED);
        return false;
    }
    
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        char *warn_msg[1] = {"[Warning] Failed to set linear filtering"};
        Shows_SDL_error(warn_msg, 1, ANSI_YELLOW);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        char *err_msg[1] = {"[Error] Failed to init SDL2_image with PNG flag"};
        Shows_SDL_error(err_msg, 1, ANSI_RED);
        return false;
    }

    if (!Main_Window)
    {
        Main_Window = SDL_CreateWindow(
            "Main window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            WIN_WIDTH, WIN_HEIGHT, 
            SDL_WINDOW_SHOWN
        );

        if (!Main_Window)
        {
            char *err_msg[1] = {"[Error] Failed to create main window"};
            Shows_SDL_error(err_msg, 1, ANSI_RED);
            return false;
        }

        Main_Window_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);

        if (!Main_Window_Renderer)
        {
            char *err_msg[1] = {"[Error] Failed to create main window renderer"};
            Shows_SDL_error(err_msg, 1, ANSI_RED);
            return false;
        }

        SDL_SetRenderDrawColor(Main_Window_Renderer, 255, 255, 255, 255);
    }

    if (!Main_Window_Renderer)
    {
        Main_Window_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);

        if (!Main_Window_Renderer)
        {
            char *err_msg[1] = {"[Error] Failed to create main window renderer"};
            Shows_SDL_error(err_msg, 1, ANSI_RED);
            return false;
        }
    }
    
    return true;
}

void Init_player()
{
    if (!Character)
    {
        Character = Create_Player("../asset/image/character2.png", Main_Window_Renderer);

        SDL_Rect *src_rects[NUM_OF_PLAYER_STATE];

        src_rects[LEFT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[LEFT]->x = 37;
        src_rects[LEFT]->y = 37;
        src_rects[LEFT]->w = 30 * 1.25;
        src_rects[LEFT]->h = 30 * 1.25;

        src_rects[RIGHT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[RIGHT]->x = 120;
        src_rects[RIGHT]->y = 37;
        src_rects[RIGHT]->w = 30 * 1.1;
        src_rects[RIGHT]->h = 30 * 1.1;

        src_rects[DEATH_LEFT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[DEATH_LEFT]->x = 203;
        src_rects[DEATH_LEFT]->y = 37;
        src_rects[DEATH_LEFT]->w = 30 * 1.1;
        src_rects[DEATH_LEFT]->h = 30 * 1.1;

        src_rects[DEATH_RIGHT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
        src_rects[DEATH_RIGHT]->x = 285;
        src_rects[DEATH_RIGHT]->y = 37;
        src_rects[DEATH_RIGHT]->w = 30 * 1.1;
        src_rects[DEATH_RIGHT]->h = 30 * 1.1;

        Assign_Player_Rect(Character, src_rects);

        for (int i = 0; i < NUM_OF_PLAYER_STATE; i++)
        {
            free(src_rects[i]);
            src_rects[i] = NULL;
        }
    }
}

void Init_map()
{
    if (!Stage_1)
    {
        Stage_1 = Load_Map(&Stage_1_Map[0][0], STAGE_1_COL, STAGE_1_ROW);
    }
    else
    {
        dispose_map(Stage_1);
        Stage_1 = Load_Map(&Stage_1_Map[0][0], STAGE_1_COL, STAGE_1_ROW);
    }
}

void Init_enemy()
{
    SDL_Rect *src_rects_1[NUM_OF_ENEMY_DIRECTION];
    src_rects_1[ENEMY_LEFT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_1[ENEMY_LEFT]->x = 120;
    src_rects_1[ENEMY_LEFT]->y = 30;
    src_rects_1[ENEMY_LEFT]->w = 45;
    src_rects_1[ENEMY_LEFT]->h = 45;

    src_rects_1[ENEMY_RIGHT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_1[ENEMY_RIGHT]->x = 200;
    src_rects_1[ENEMY_RIGHT]->y = 30;
    src_rects_1[ENEMY_RIGHT]->w = 45;
    src_rects_1[ENEMY_RIGHT]->h = 45;

    SDL_Rect *src_rects_2[NUM_OF_ENEMY_DIRECTION];

    src_rects_2[ENEMY_LEFT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_2[ENEMY_LEFT]->x = 30;
    src_rects_2[ENEMY_LEFT]->y = 30;
    src_rects_2[ENEMY_LEFT]->w = 45;
    src_rects_2[ENEMY_LEFT]->h = 45;

    src_rects_2[ENEMY_RIGHT] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    src_rects_2[ENEMY_RIGHT]->x = 30;
    src_rects_2[ENEMY_RIGHT]->y = 30;
    src_rects_2[ENEMY_RIGHT]->w = 45;
    src_rects_2[ENEMY_RIGHT]->h = 45;

    int i;
    for (i = 0; i < NUM_OF_ENEMYS_STAGE_1; i++)
    {
        Enemy_arr_stage_1[i] = Create_Enemy_Object("../asset/image/enemy.png", Main_Window_Renderer, 0, 0);
    }
    for (i = 0; i < NUM_OF_ENEMYS_STAGE_1 / 2; i++)
    {
        Assign_Enemy_Rect(Enemy_arr_stage_1[i], src_rects_1);
    }
    for (; i < NUM_OF_ENEMYS_STAGE_1; i++)
    {
        Assign_Enemy_Rect(Enemy_arr_stage_1[i], src_rects_2);
    }

    {
        Enemy_arr_stage_1[0]->GlobalPos_x = 80;
        Enemy_arr_stage_1[0]->GlobalPos_y = 420;

        Enemy_arr_stage_1[1]->GlobalPos_x = 145;
        Enemy_arr_stage_1[1]->GlobalPos_y = 60;

        Enemy_arr_stage_1[2]->GlobalPos_x = 510;
        Enemy_arr_stage_1[2]->GlobalPos_y = 420;

        Enemy_arr_stage_1[3]->GlobalPos_x = 600;
        Enemy_arr_stage_1[3]->GlobalPos_y = 270;

        Enemy_arr_stage_1[4]->GlobalPos_x = 505;
        Enemy_arr_stage_1[4]->GlobalPos_y = 90;

        Enemy_arr_stage_1[5]->GlobalPos_x = 675;
        Enemy_arr_stage_1[5]->GlobalPos_y = 150;

        Enemy_arr_stage_1[6]->GlobalPos_x = 945;
        Enemy_arr_stage_1[6]->GlobalPos_y = 150;

        Enemy_arr_stage_1[7]->GlobalPos_x = 1005;
        Enemy_arr_stage_1[7]->GlobalPos_y = 270;

        Enemy_arr_stage_1[8]->GlobalPos_x = 1135;
        Enemy_arr_stage_1[8]->GlobalPos_y = 420;

        Enemy_arr_stage_1[9]->GlobalPos_x = 1410;
        Enemy_arr_stage_1[9]->GlobalPos_y = 150;

        Enemy_arr_stage_1[10]->GlobalPos_x = 1610;
        Enemy_arr_stage_1[10]->GlobalPos_y = 420;

        Enemy_arr_stage_1[11]->GlobalPos_x = 1805;
        Enemy_arr_stage_1[11]->GlobalPos_y = 420;

        Enemy_arr_stage_1[12]->GlobalPos_x = 1975;
        Enemy_arr_stage_1[12]->GlobalPos_y = 90;

        Enemy_arr_stage_1[13]->GlobalPos_x = 2100;
        Enemy_arr_stage_1[13]->GlobalPos_y = 420;

        Enemy_arr_stage_1[14]->GlobalPos_x = 2240;
        Enemy_arr_stage_1[14]->GlobalPos_y = 420;

        Enemy_arr_stage_1[15]->GlobalPos_x = 2400;
        Enemy_arr_stage_1[15]->GlobalPos_y = 420;

        Enemy_arr_stage_1[16]->GlobalPos_x = 2365;
        Enemy_arr_stage_1[16]->GlobalPos_y = 330;

        Enemy_arr_stage_1[17]->GlobalPos_x = 2610;
        Enemy_arr_stage_1[17]->GlobalPos_y = 420;

        Enemy_arr_stage_1[18]->GlobalPos_x = 2850;
        Enemy_arr_stage_1[18]->GlobalPos_y = 300;

        Enemy_arr_stage_1[19]->GlobalPos_x = 2860;
        Enemy_arr_stage_1[19]->GlobalPos_y = 60;
    }

    for (int i = 0; i < NUM_OF_ENEMY_DIRECTION; i++)
    {
        free(src_rects_1[i]);
        free(src_rects_2[i]);
        src_rects_1[i] = NULL;
        src_rects_2[i] = NULL;
    }
}

# endif