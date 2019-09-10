#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "myLib.h"
#include "cells.h"
#include "main.h"
#include "menus.h"
#include "backgrounds.h"

OamEntry shadow[128];
extern cell cell_array[128];
extern int obj_cnt;
GAME_STATE state = STAND_BY;
GAME_STATE next;
int remaining;


int main() {
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    /*
        Sets up background as a simple color
     */
    DMA[3].src = graphics_palette;
    DMA[3].dst = SPRITEPAL;
    DMA[3].cnt = GRAPHICS_PALETTE_LENGTH | DMA_ON;

    DMA[3].src = graphics;
    DMA[3].dst = &CHARBLOCKBASE[5];
    DMA[3].cnt = GRAPHICS_LENGTH | DMA_ON;

    for(int i = 0; i < 128; i++)
        shadow[i].attr0 = ATTR0_HIDE;

    int finished;
    while (1) {
        finished = 0;
        raiseMainMenu();
        while (!finished) {
            next = start_game();
            obj_cnt = 0;
            if (next == WIN) {
                switch (state) {
                    case LEVEL1:
                        raiseTransition();
                        state = LEVEL2;
                        break;
                    case LEVEL2:
                        raiseTransition();
                        state = LEVEL3;
                        break;
                    case LEVEL3:
                        state = RETURN;
                        finished = 1;
                        raiseCredits();
                        waitForVblank();
                        waitForVblank();
                        waitForVblank();
                        waitForVblank();
                        break;
                    default:
                        break;
                }
            } else if (next == LOSE) {
                if (raiseLoseMenu()) {
                    break;
                }
            } else if (next == RETURN) {
                break;
            }
        }
    }

    return 0;
}

/*
    Runs the game and determines spawn rate via the static enum state.
    Initializes one cell that will be used for the player.

    when timer == 70, that's roughly one second. So the level goes on for
    30 seconds.
 */
GAME_STATE start_game() {
    REG_DISPCTL = MODE3 | BG2_ENABLE | OBJ_ENABLE | GRAPHICS_DIMENSION_TYPE;
    obj_cnt = 0;
    clear_OAM(0);

    int bgcolor = BG_COLOR;
    DMA[3].src = &bgcolor;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (240 * 160) | DMA_ON | DMA_SOURCE_FIXED;

    remaining = state;
    int oldRemaining = remaining;

    OamEntry* player = (shadow + obj_cnt);
    player->attr0 = (160 / 2) | GRAPHICS_PALETTE_TYPE | PLAYER_SPRITE_SHAPE;
    player->attr1 = (240 / 2) | PLAYER_SPRITE_SIZE;
    player->attr2 = PLAYER_PALETTE_ID | PLAYER_ID;
    cell player_cell = {BLUE, ALIVE, NONE, player, 5, 5, 0, 0};
    cell_array[obj_cnt] = player_cell;
    obj_cnt = obj_cnt + 1;

    while(1) {
        if (KEY_DOWN_NOW(BUTTON_UP)) {
            player->attr0 = (player->attr0) - 3;
        }
        if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            player->attr0 = (player->attr0) + 3;
        }
        if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            player->attr1 = (player->attr1) - 3;
        }
        if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
            player->attr1 = (player->attr1) + 3;
        }

        if (GRAB_X(cell_array[0].OAM_ptr) < 0
            || GRAB_X(cell_array[0].OAM_ptr) > 240
            || GRAB_Y(cell_array[0].OAM_ptr) < 0
            || GRAB_Y(cell_array[0].OAM_ptr) > 160)
        {
            clear_OAM(0);
            return LOSE;
        }

        spawn();
        if (update()) {
            return LOSE;
        }

        DMA[3].src = shadow;
        DMA[3].dst = SPRITEMEM;
        DMA[3].cnt = 128 * 4 | DMA_ON;
        waitForVblank();

        if (oldRemaining == 0) {
            return WIN;
        }

        if (KEY_DOWN_NOW(BUTTON_SELECT)) {
            // Disables all sprites
            REG_DISPCTL = MODE3 | BG2_ENABLE;

            if (raisePause()) {
                return RETURN;
            }

            // reenables graphics
            int bgcolor = BG_COLOR;
            DMA[3].src = &bgcolor;
            DMA[3].dst = videoBuffer;
            DMA[3].cnt = (240 * 160) | DMA_ON | DMA_SOURCE_FIXED;
            // Reenable graphics
            REG_DISPCTL = MODE3 | BG2_ENABLE | OBJ_ENABLE | GRAPHICS_DIMENSION_TYPE;
        }

        char str[18];
        remaining = state - (obj_cnt - 1);
        sprintf(str, "Remaining: %d", remaining);
        drawString(150, 5, str, YELLOW);
        if (oldRemaining != remaining) {
            drawRect(150, 5, 8, 80, 0x3100);
        }

        oldRemaining = remaining;
    }
}
