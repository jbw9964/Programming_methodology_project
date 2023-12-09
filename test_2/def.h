
# ifndef __DEF__H
# define __DEF__H

//  <Utils/Utils.h>
    # define ANSI_BOLD      "\x1b[1m"       // ANSI escape codes that make BOLD strings
    # define ANSI_UNDERLINE "\x1b[4m"       // ANSI escape codes that make UNDERLINED strings
    # define ANSI_RED       "\x1b[31m"      // ANSI escape codes that color the string RED
    # define ANSI_YELLOW    "\x1b[33m"      // ANSI escape codes that color the string YELLOW
    # define ANSI_RESET     "\x1b[0m"       // ANSI escape codes that RESET all attributes



// <Init/Map.h>
    # define MAP_WIDTH      1380            // the global width of map, must be multiple of `UNIT_PIXEL` (30 * 115, 690 * 3)
    // # define MAP_WIDTH      3450            // the global width of map, must be multiple of `UNIT_PIXEL` (30 * 115, 690 * 3)
    # define MAP_HEIGTH     WIN_HEIGHT      // the global height of map, must be multiple of `UNIT_PIXEL`

    # define UNIT_PIXEL     30              // a unit pixel to render



// <GameObject/Player.h>
    # define Round(fnum)    ((fnum) - (int) (fnum) >= 0.5 ? (int) (fnum + 1) : (int) (fnum))
    # define MAX_SPEED_X    300              // maximum speed that player can have
    # define MAX_SPEED_Y    600              // maximum speed that player can have

    # define NUM_OF_PLAYER_STATE    3       // maximum state that player can have (Normal, Jump, Run)

    # define KEY_UP     SDL_SCANCODE_UP     // a `SDL_Scancode` that represent `UP` keyboard direction
    # define KEY_DOWN   SDL_SCANCODE_DOWN   // a `SDL_Scancode` that represent `DOWN` keyboard direction
    # define KEY_LEFT   SDL_SCANCODE_LEFT   // a `SDL_Scancode` that represent `LEFT` keyboard direction
    # define KEY_RIGHT  SDL_SCANCODE_RIGHT  // a `SDL_Scancode` that represent `RIGHT` keyboard direction

    # define UNIT_TIME_STEP         (1 / 60.)   // time step to calculate position (60 FPS)

    # define VIEW_PORTION_LEFT      (2 / 5.)    // the portion of character position that cause the left edge to render
    # define VIEW_PORTION_RIGHT     (3 / 5.)    // the portion of character position that cause the right edge to render

// <GameObject/Enemy.h>
    # define ENEMY_MAX_SPEED_X          (MAX_SPEED_X / 5)   // maximum speed that enemy can have
    # define ENEMY_MAX_SPEED_Y          MAX_SPEED_Y         // maximum speed that enemy can have
    # define NUM_OF_ENEMY_DIRECTION     2                   // number of direction that enemy can have


// <main.h>
    # define WIN_WIDTH      690             // width of window that will be shown to user
    # define WIN_HEIGHT     480             // height of window that will be shown to user




# endif