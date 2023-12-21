
# ifndef __DEF__H
# define __DEF__H

//  <Utils/Utils.h>
    # define ANSI_BOLD      "\x1b[1m"       // ANSI escape codes that make BOLD strings
    # define ANSI_UNDERLINE "\x1b[4m"       // ANSI escape codes that make UNDERLINED strings
    # define ANSI_RED       "\x1b[31m"      // ANSI escape codes that color the string RED
    # define ANSI_YELLOW    "\x1b[33m"      // ANSI escape codes that color the string YELLOW
    # define ANSI_RESET     "\x1b[0m"       // ANSI escape codes that RESET all attributes



// <Init/Map.h>
    # define MAP_WIDTH      3150            // the global width of map, must be multiple of `UNIT_PIXEL` (30 * 105)
    # define MAP_HEIGTH     480      // the global height of map, must be multiple of `UNIT_PIXEL`

    # define UNIT_PIXEL     30              // a unit pixel to render

    # define NUM_OF_BLOCK_KIND      10      // number of all block kinds to render

    # define InRange(x, a, b)       ((a) <= (x) && (x) <= (b) ? true : false)

    # define STAGE_1_ROW                105
    # define STAGE_1_COL                16
    # define MAP_SHRINK_RATIO           30

    # define STAGE_1_GOAL_ROW           5
    # define STAGE_1_GOAL_COL           6
    
    # define BLOCK_EMPTY            0       // empty space
    # define BLOCK_UNBREAKABLE      1       // unbreakable brick block      player CAN NOT pass through
    # define BLOCK_BREAKABLE        2       // breakable brick block        player CAN NOT pass through
    # define BLOCK_SOIL             3       // soil (dirt) block            player CAN NOT pass through
    # define BLOCK_THRON            4       // thron (spike) block 
    # define BLOCK_MINE             5       // mine block
    # define BLOCK_BLACK_HOLE       6       // black hole block
    # define BLOCK_FLAG             7       // flag block
    # define BLOCK_BLACK_HOLE_GOAL  8       // black hole goal block
    # define BLOCK_INVISIBLE        9       // invisible block              player CAN NOT pass through

    # define NUM_OF_MSG_TEXT        4     

    # define MSG_CLEAR              0
    # define MSG_DEATH              1
    # define MSG_RESTART            2
    # define MSG_QUIT               3


// <GameObject/Player.h>
    # define Round(fnum)    ((fnum) - (int) (fnum) >= 0.5 ? (int) (fnum + 1) : (int) (fnum))
    # define MAX_SPEED_X    300              // maximum speed that player can have
    # define MAX_SPEED_Y    600              // maximum speed that player can have
    # define GRAVITY        (-1 * MAX_SPEED_Y / 35)

    # define NUM_OF_PLAYER_STATE    4       // maximum state that player can have (Left, Right, DEATH_LEFT, DEATH_RIGHT)

    # define KEY_UP         SDL_SCANCODE_UP     // a `SDL_Scancode` that represent `UP` keyboard direction
    # define KEY_DOWN       SDL_SCANCODE_DOWN   // a `SDL_Scancode` that represent `DOWN` keyboard direction
    # define KEY_LEFT       SDL_SCANCODE_LEFT   // a `SDL_Scancode` that represent `LEFT` keyboard direction
    # define KEY_RIGHT      SDL_SCANCODE_RIGHT  // a `SDL_Scancode` that represent `RIGHT` keyboard direction
    # define KEY_RESTART    SDL_SCANCODE_R      // a `SDL_Scancode` that represent `R'

    # define UNIT_TIME_STEP         (1 / 60.)   // time step to calculate position (60 FPS)

    # define VIEW_PORTION_LEFT      (2 / 5.)    // the portion of character position that cause the left edge to render
    # define VIEW_PORTION_RIGHT     (3 / 5.)    // the portion of character position that cause the right edge to render

// <GameObject/Enemy.h>
    # define ENEMY_MAX_SPEED_X          (MAX_SPEED_X / 5)   // maximum speed that enemy can have
    # define ENEMY_MAX_SPEED_Y          MAX_SPEED_Y         // maximum speed that enemy can have
    # define NUM_OF_ENEMY_DIRECTION     2                   // number of direction that enemy can have

    # define NUM_OF_ENEMYS_STAGE_1      20


// <main.h>
    # define WIN_WIDTH      690             // width of window that will be shown to user
    # define WIN_HEIGHT     MAP_HEIGTH             // height of window that will be shown to user

    # define FPS            (60.)
    
    # define BGM_VOLUME     (MIX_MAX_VOLUME / 4)
    # define EFFECT_VOLUME  (MIX_MAX_VOLUME / 2)


# endif