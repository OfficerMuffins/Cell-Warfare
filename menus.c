#include "myLib.h"
#include "backgrounds.h"
#include "main.h"
#include "menus.h"
#include "graphics.h"
#include "cells.h"
#include <stdio.h>

extern GAME_STATE state;
extern OamEntry shadow[128];


/*
    When return hit, executes start_game() in the main of main.c
 */
void raiseMainMenu()
{
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    drawImage3(0, 0, 240, 160, mainMenu);
    drawString(110, 84, "PLAY GAME [A]", YELLOW);

    while(1) {
        if (KEY_DOWN_NOW(BUTTON_A)) {
            state = LEVEL1;
            return;
        }
    }
}

int raiseLoseMenu()
{
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    drawImage3(0, 0, 240, 160, gameOver);
    drawString(70, 70, "[A] to Play again", YELLOW);
    drawString(120, 60, "[B] to go to main menu", YELLOW);

    while(1) {
        if (KEY_DOWN_NOW(BUTTON_A)) {
            state = LEVEL1;
            return 0;
        } else if (KEY_DOWN_NOW(BUTTON_B)) {
            state = RETURN;
            return 1;
        }
    }
}

void raiseTransition()
{
    REG_DISPCTL = MODE3 | BG2_ENABLE;

    int bgcolor = BG_COLOR;
    DMA[3].src = &bgcolor;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (240 * 160) | DMA_ON | DMA_SOURCE_FIXED;

    char temp[10];
    int level;
    switch (state) {
        case LEVEL1:
            level = 2;
            break;
        case LEVEL2:
            level = 3;
            break;
        default:
            break;
    }
    sprintf(temp, "LEVEL %d", level);
    drawString(20, 95, temp, YELLOW);
    volatile int timer = 0;

    while(timer < 999999) {
        if (KEY_DOWN_NOW(BUTTON_A)) {
            return;
        }
        timer++;
    }
}

/*
    0 if continue the game, 1 if return to main menu
 */
int raisePause()
{
    drawImage3(0, 0, 240, 160, pauseMenu);
    while(1) {
        if (KEY_DOWN_NOW(BUTTON_A)) {
            return 0;
        } else if(KEY_DOWN_NOW(BUTTON_B)) {
            return 1;
        }
    }
}

void raiseCredits() {
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    drawString(30, 70, "Congratulations!", YELLOW);
    drawString(40, 40, "You beat all three levels.", YELLOW);
    drawString(100, 82, "You must be...", YELLOW);
    while(1) {
        if (KEY_DOWN_NOW(BUTTON_A)) {
            drawImage3(0, 0, 240, 160, bill);
            drawString(80, 62, "A HELLUVA engineer!", YELLOW);
            while(1) {
                waitForVblank();
                waitForVblank();
                waitForVblank();
                waitForVblank();
                if (KEY_DOWN_NOW(BUTTON_A)) {
                    break;
                }
            }
            return;
        }
        waitForVblank();
    }
}

void setPixel(int row, int col, unsigned short color) {
    videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawChar(int row, int col, char ch, unsigned short color) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 6; c++) {
            if(fontdata_6x8[OFFSET(r, c, 6) + ch*48] == 1) {
                setPixel(r + row, c + col, color);
            }
        }
    }
}

void drawString(int row, int col, char str[], unsigned short color) {
    while (*str) {
        drawChar(row, col, *str++, color);
        col += 6;
    }
}

/*
    Used to block out words
 */
void drawRect(int row, int col, int height, int width, volatile unsigned short color)
{
    for(int r=0; r<height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = videoBuffer + OFFSET(row + r, col, 240);
        DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_FIXED;
    }
}


void drawImage3(int row, int col, int width, int height, const u16* image) {
    for (int r = 0; r < height; r++) {
        DMA[3].src = (image + r * width);
        DMA[3].dst = videoBuffer + OFFSET(row + r, col, 240);
        DMA[3].cnt = (width) | DMA_ON;
    }
}