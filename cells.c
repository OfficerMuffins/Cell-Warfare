#include <stdlib.h>
#include "myLib.h"
#include "graphics.h"
#include "cells.h"
#include "main.h"

extern OamEntry shadow[128];
extern GAME_STATE state;
cell cell_array[128];
int obj_cnt = 0;
extern int remaining;
/*
    More cells and stronger cells are spawned at higher levels
*/
void spawn() {
    int x;
    int y;
    int vector[2];;

    // Can either be 1 or 0. Decides which wall the cell spwans
    // from
    switch (rand() % 4) {
        // left wall
        case 3:
            x = 5;
            y = rand() % 149 + 1;
            vector[0] = 1;
            vector[1] = 0;
            break;
        // upper wall
        case 1:
            x = rand() % 229 + 1;
            y = 1;
            vector[0] = 0;
            vector[1] = 1;
            break;
        // right wall
        case 2:
            x = 235;
            y = rand() % 149 + 1;
            vector[0] = -1;
            vector[1] = 0;
            break;
        // bottom wall
        case 0:
            x = rand() % 229 + 1;
            y = 155;
            vector[0] = 0;
            vector[1] = -1;
            break;
    }
    switch (state) {
        case LEVEL1:
            if ((rand() % 7000 + 1) < 50){
                cell_array[obj_cnt] = create_cell(RED, x ,y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            } if ((rand() % 8000 + 1) < 25) {
                cell_array[obj_cnt] = create_cell(GRAY, x, y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            }
            break;
        // Adds pink cells to the spawn rate
        case LEVEL2:
            if ((rand() % 7000 + 1) < 75){
                cell_array[obj_cnt] = create_cell(RED, x, y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            } if ((rand() % 10000 + 1) < 50) {
                cell_array[obj_cnt] = create_cell(GRAY, x, y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            }
            if ((rand() % 13000 + 1) < 25) {
                cell_array[obj_cnt] = create_cell(PINK, x, y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            }
            break;
        case LEVEL3:
            if ((rand() % 9000 + 1) < 80) {
                cell_array[obj_cnt] = create_cell(RED, x, y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            } if ((rand() % 18000 + 1) < 75) {
                cell_array[obj_cnt] = create_cell(GRAY, x, y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            } if ((rand() % 18000 + 1) < 25) {
                cell_array[obj_cnt] = create_cell(PINK, x, y);
                cell_array[obj_cnt - 1].vecx = vector[0];
                cell_array[obj_cnt - 1].vecy = vector[1];
            } if ((rand() % 6000 + 1) < 50) {
                cell_array[obj_cnt] = create_cell(BLUE, x, y);
                cell_array[obj_cnt - 1].vecx = 5 * vector[0];
                cell_array[obj_cnt - 1].vecy = 5 * vector[1];
            }
            break;
        default:
            return;
    }
}

/*
    @return a copy of the created cell.
    minipulates OAM and shadow
 */
cell create_cell(TYPE type, int x, int y) {
    OamEntry* cell_sprite_ptr;
    cell newCell;
    // int vector[0][2]; // x, y velocity
    switch(type) {
        case PINK:
            cell_sprite_ptr = (shadow + obj_cnt);
            cell_sprite_ptr->attr0 = y | GRAPHICS_PALETTE_TYPE | PINK_CELL_SPRITE_SHAPE;
            cell_sprite_ptr->attr1 = x | PINK_CELL_SPRITE_SIZE;
            cell_sprite_ptr->attr2 = PINK_CELL_PALETTE_ID | PINK_CELL_ID;
            newCell.type = PINK;
            newCell.attack = TRACK;
            newCell.health_pool = 200;
            newCell.health = newCell.health_pool;
            newCell.OAM_ptr = cell_sprite_ptr;
            break;
        case GRAY:
            cell_sprite_ptr = (shadow + obj_cnt);
            cell_sprite_ptr->attr0 = y | GRAPHICS_PALETTE_TYPE | GRAY_CELL_SPRITE_SHAPE;
            cell_sprite_ptr->attr1 = x | GRAY_CELL_SPRITE_SIZE;
            cell_sprite_ptr->attr2 = GRAY_CELL_PALETTE_ID | GRAY_CELL_ID;

            newCell.type = GRAY;
            newCell.attack = TRACK;
            newCell.health_pool = 200;
            newCell.health = newCell.health_pool;
            newCell.OAM_ptr = cell_sprite_ptr;
            break;
        case RED:
            cell_sprite_ptr = (shadow + obj_cnt);
            cell_sprite_ptr->attr0 = y | GRAPHICS_PALETTE_TYPE | RED_CELL_SPRITE_SHAPE;
            cell_sprite_ptr->attr1 = x | RED_CELL_SPRITE_SIZE;
            cell_sprite_ptr->attr2 = RED_CELL_PALETTE_ID | RED_CELL_ID;

            newCell.type = RED;
            newCell.attack = NONE;
            newCell.health_pool = 2;
            newCell.health = newCell.health_pool;
            newCell.OAM_ptr = cell_sprite_ptr;
            break;
        case SMALL_PINK:
            cell_sprite_ptr = (shadow + obj_cnt);
            cell_sprite_ptr->attr0 = y | GRAPHICS_PALETTE_TYPE | SMALL_PINK_SPRITE_SHAPE;
            cell_sprite_ptr->attr1 = x | SMALL_PINK_SPRITE_SIZE;
            cell_sprite_ptr->attr2 = SMALL_PINK_PALETTE_ID | SMALL_PINK_ID;

            newCell.type = SMALL_PINK;
            newCell.attack = TRACK;
            newCell.health_pool = 100;
            newCell.health = newCell.health_pool;
            newCell.OAM_ptr = cell_sprite_ptr;
            break;
        case BLUE:
            cell_sprite_ptr = (shadow + obj_cnt);
            cell_sprite_ptr->attr0 = y | GRAPHICS_PALETTE_TYPE | PLAYER_SPRITE_SHAPE;
            cell_sprite_ptr->attr1 = x | PLAYER_SPRITE_SIZE;
            cell_sprite_ptr->attr2 = PLAYER_PALETTE_ID | PLAYER_ID;

            newCell.type = BLUE;
            newCell.attack = NONE;
            newCell.health_pool = 600;
            newCell.health = newCell.health_pool;
            newCell.OAM_ptr = cell_sprite_ptr;
            break;
    }

    newCell.status = ALIVE;
    obj_cnt = obj_cnt + 1;
    return newCell;
}

/*
    -Only used for blue and gray cells
 */
void chase(OamEntry *self, OamEntry *target) {
    if (target->attr0 > self->attr0) {
        self->attr0 = (self->attr0) + 1;
    } else {
        self->attr0 = (self->attr0) - 1;
    }

    int x = target -> attr1 & 0x1FF;
    int chasex = self -> attr1 & 0x1FF;
    if (x < chasex) {
        self->attr1 = (self->attr1) - 1;
    } else {
         self->attr1 = (self->attr1) + 1;
    }
}

/*
    Moves every single cell from the cell array but the player's
 */
int update() {
    int countDead;
    for (int i = 1; i < obj_cnt; i++) {
        if (cell_array[i].attack == TRACK) {
            chase(cell_array[i].OAM_ptr, shadow);
            cell_array[i].health = cell_array[i].health - 1;
        } else {
            SET_X(cell_array[i].OAM_ptr,
                GRAB_X(cell_array[i].OAM_ptr)
                + cell_array[i].vecx);
            SET_Y(cell_array[i].OAM_ptr,
                GRAB_Y(cell_array[i].OAM_ptr)
                + cell_array[i].vecy);
        }

        /*
            Detects if the AI cell has moved out of the screen
         */
        if (GRAB_X(cell_array[i].OAM_ptr) <= 0
            || GRAB_X(cell_array[i].OAM_ptr) >= 240
            || GRAB_Y(cell_array[i].OAM_ptr) <= 0
            || GRAB_Y(cell_array[i].OAM_ptr) >= 160)
        {
            countDead++;
            cell_array[i].status = DEAD;
            SET_X(cell_array[i].OAM_ptr, 245);
        }

        if (cell_array[i].health == 0) {
            countDead++;
            cell_array[i].status = DEAD;
            if (cell_array[i].type == PINK) {
                cell left;
                cell right;
                cell up;
                cell down;

                OamEntry *ptr = cell_array[i].OAM_ptr;
                left = create_cell(SMALL_PINK, GRAB_X(ptr) - 25, GRAB_Y(ptr));
                cell_array[obj_cnt - 1] = left;
                right = create_cell(SMALL_PINK, GRAB_X(ptr) + 25, GRAB_Y(ptr));
                cell_array[obj_cnt - 1] = right;
                up = create_cell(SMALL_PINK, GRAB_X(ptr), GRAB_Y(ptr) + 25);
                cell_array[obj_cnt - 1] = up;
                down = create_cell(SMALL_PINK, GRAB_X(ptr), GRAB_Y(ptr) - 25);
                cell_array[obj_cnt - 1] = down;

                left.vecx = -4; left.vecy = 0;
                right.vecx = 4; right.vecy = 0;
                up.vecx = 0; up.vecy = -4;
                down.vecx = 0; down.vecy = 4;

                SET_X(cell_array[i].OAM_ptr, 245);
            } else {
                SET_X(cell_array[i].OAM_ptr, 245);
            }
        }

        // Player will always be the first index of the array.
        // Only works for 16x16 square pixel cells. Doesnt work for
        // small pink cells. This detects collisions
        if ((abs((GRAB_X(cell_array[0].OAM_ptr) + 4) - (GRAB_X(cell_array[i].OAM_ptr) + 8)) < 12)
            && (abs((GRAB_Y(cell_array[0].OAM_ptr) + 4) - (GRAB_Y(cell_array[i].OAM_ptr) + 8)) < 12))
        {
            return 1;
            SET_X(cell_array[0].OAM_ptr, 245);
        }
    }
    remaining = state - countDead;
    return 0;
}


/*
    Do nothing to cell array because already handled by setting obj_cnt to 0
 */
void clear_OAM(volatile int i) {
    OamEntry *ptr;
    for (i; i < 128; i++) {
        ptr = shadow + i;
        ptr -> attr0 = 0;
        ptr -> attr1 = 0;
        ptr -> attr2 = 0;
    }

    obj_cnt = 0;
}
