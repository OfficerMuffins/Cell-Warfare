#ifndef MAIN_H
#define MAIN_H

typedef enum {
    STAND_BY,
    LEVEL1 = 20,
    LEVEL2 = 30,
    LEVEL3 = 40,
    WIN,
    LOSE,
    RETURN,
} GAME_STATE;

#define BG_COLOR (0x3100)

GAME_STATE start_game();

#endif
