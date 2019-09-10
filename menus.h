#ifndef MENUS_H
#define MENUS_H

void raiseMainMenu();
int raiseLoseMenu();
void raiseTransition();
void raiseTutorial();
int raisePause();
void raiseCredits();

void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char str[], unsigned short color);
void drawRect(int row, int col, int height, int width, volatile unsigned short color);
void drawImage3(int row, int col, int width, int height, const u16* image);

extern const unsigned char fontdata_6x8[12288];

#define RED_COLOR COLOR(31, 0, 0)
#define GREEN COLOR(0, 31, 0) // define red as a call to other macro
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0

#endif