/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=8 --for_bitmap graphics red_cell.png player.png gray_cell.png pink_cell.png small_pink.png 
 * Time-stamp: Wednesday 11/08/2017, 18:00:51
 * 
 * Image Information
 * -----------------
 * red_cell.png 16@16
 * player.png 8@8
 * gray_cell.png 16@16
 * pink_cell.png 16@16
 * small_pink.png 8@8
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GRAPHICS_PALETTE_TYPE (1 << 13)
#define GRAPHICS_DIMENSION_TYPE (1 << 6)

extern const unsigned short graphics_palette[256];
#define GRAPHICS_PALETTE_SIZE 512
#define GRAPHICS_PALETTE_LENGTH 256

extern const unsigned short graphics[448];
#define GRAPHICS_SIZE 896
#define GRAPHICS_LENGTH 448

#define RED_CELL_PALETTE_ID (0 << 12)
#define RED_CELL_SPRITE_SHAPE (0 << 14)
#define RED_CELL_SPRITE_SIZE (1 << 14)
#define RED_CELL_ID 512

#define PLAYER_PALETTE_ID (0 << 12)
#define PLAYER_SPRITE_SHAPE (0 << 14)
#define PLAYER_SPRITE_SIZE (0 << 14)
#define PLAYER_ID 520

#define GRAY_CELL_PALETTE_ID (0 << 12)
#define GRAY_CELL_SPRITE_SHAPE (0 << 14)
#define GRAY_CELL_SPRITE_SIZE (1 << 14)
#define GRAY_CELL_ID 522

#define PINK_CELL_PALETTE_ID (0 << 12)
#define PINK_CELL_SPRITE_SHAPE (0 << 14)
#define PINK_CELL_SPRITE_SIZE (1 << 14)
#define PINK_CELL_ID 530

#define SMALL_PINK_PALETTE_ID (0 << 12)
#define SMALL_PINK_SPRITE_SHAPE (0 << 14)
#define SMALL_PINK_SPRITE_SIZE (0 << 14)
#define SMALL_PINK_ID 538

#endif

