#ifndef DRAW_HEADER
#define DRAW_HEADER
#include "gl.h"

#define SCREEN_W 128 // in pixels
#define SCREEN_H 128 // in pixels
#define RESOLUTION_FACTOR 2

#define NUM_COLS 16

// 16 colors from PICO-8
enum {
    BLACK,
    NAVY,
    MAGENTA,
    DARKGREEN,
    BROWN,
    DARKGRAY,
    GRAY,
    WHITE,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    PINK,
    PEACH,
};

// initialize graphics library and frame buffer.
void draw_init();

// swap buffers.
void flip();

// palette reset
// set all indices of pico_colors to their original values.
void pal_reset();

// palette transparent
// toggle `col`'s transparency. sprites will not render this color if it is
// transparent.
void palt(int col, int transparent);

// palette substitute
// after this function is called, color 2 will be substituted color 1
// in all draw calls. Use pal_reset to reset the palette.
void pal_sub(int col1, int col2);

int is_transparent(int col);

// Colors wrap, e.g., col = 0, 16, 32,... are all black.
void clear_screen(int col);

void draw_pixel(int x, int y, int col);

color_t get_pixel(int x, int y);

void draw_rectfill(int x, int y, int w, int h, int col);

void draw_circ(int x, int y, int r, int col);

void draw_circfill(int x, int y, int r, int col);

void draw_string(int x, int y, const char *str, int col);

void draw_line(int x1, int x2, int y1, int y2, int col);

#endif
