#include "sprite.h"
#include "draw.h"
#include "malloc.h"
#include "assert.h"
#include "gl.h"
#include "printf.h"
color_t const pico_colors[] = {
    0xff000000,
    0xff1d2b53,
    0xFF7E2553,
    0xFF008751,
    0XFFAB5236,
    0xFF5f574f,
    0xFFC2C3C7,
    0xFFFFF1E8,
    0xFFFF004D,
    0xFFFFA300,
    0xFFFFEC27,
    0xFF00E436,
    0xFF29ADFF,
    0xFF83769C,
    0xFFFF77A8,
    0xFFFFCCAA,
};

color_t palette[] = {
    0xff000000,
    0xff1d2b53,
    0xFF7E2553,
    0xFF008751,
    0XFFAB5236,
    0xFF5f574f,
    0xFFC2C3C7,
    0xFFFFF1E8,
    0xFFFF004D,
    0xFFFFA300,
    0xFFFFEC27,
    0xFF00E436,
    0xFF29ADFF,
    0xFF83769C,
    0xFFFF77A8,
    0xFFFFCCAA,
};

//static const double PI = 3.1415926535;


static uint16_t transparent_colors;

/* 
EXPLAIN * RESOLUTION_FACTOR
*/

void draw_init() 
{
	// do we want to init gl here?
	gl_init(SCREEN_W * RESOLUTION_FACTOR, SCREEN_H * RESOLUTION_FACTOR, GL_DOUBLEBUFFER);
}

static color_t get_color(int col) 
{
	return palette[col%NUM_COLS];
}

void flip() 
{
	gl_swap_buffer();
}

void pal_reset()
{
    for (int i = 0; i < NUM_COLS; ++i)
    {
        palette[i] = pico_colors[i];
    }
}

// transparent is a bool of whether col should be transparent
void palt(int col, int transparent)
{
    int mask = (1 << (col % 16));
    transparent_colors = ((transparent_colors & (~mask)) | transparent << (col % 16));
}

void pal_sub(int col1, int col2)
{
    palette[col1] = pico_colors[col2];
}

int is_transparent(int col)
{
    return transparent_colors & (1 << (col % NUM_COLS));
}

void clear_screen(int col)
{
	gl_clear(get_color(col));
}

void draw_pixel(int x, int y, int col)
{
	color_t color = get_color(col);
    for (int i = 0; i < RESOLUTION_FACTOR; i++) {
        for (int j = 0; j < RESOLUTION_FACTOR; j++) {
            gl_draw_pixel((x * RESOLUTION_FACTOR) + i, (y * RESOLUTION_FACTOR) + j, color);
        }
    }
}

color_t get_pixel(int x, int y)
{
	return gl_read_pixel(x * RESOLUTION_FACTOR, y * RESOLUTION_FACTOR);
}

// Citation: https://stackoverflow.com/questions/9007977/draw-circle-using-pixels-applied-in-an-image-with-for-loop
/*void draw_circfill(int x, int y, int r, int col)
{
    r *= RESOLUTION_FACTOR;

    for (double i = 0; i < 360; i += 0.1) {
        double angle = i;
        double x1 = r * cos(angle * PI / 180);
        double y1 = r * sin(angle * PI / 180);
        draw_pixel(x + x1, y + y1, col);
    }
}*/

void draw_rect(int x, int y, int w, int h, int col)
{
    color_t color = get_color(col);
    draw_line(x, y, x + w, y, color);
    draw_line(x, y + h, x + w, y + h, color);
    draw_line(x, y, x, y + h, color);
    draw_line(x + w, y, x + w, y + h, color);
}

void draw_rectfill(int x, int y, int w, int h, int col)
{
	color_t color = get_color(col);
	gl_draw_rect(x * RESOLUTION_FACTOR, y * RESOLUTION_FACTOR, w * RESOLUTION_FACTOR, h * RESOLUTION_FACTOR, color);
}

void draw_string(int x, int y, const char *str, int col)
{
	color_t color = get_color(col);
	gl_draw_string(x * RESOLUTION_FACTOR, y * RESOLUTION_FACTOR, str, color);
}

void draw_line(int x1, int x2, int y1, int y2, int col)
{
	// CURRENTLY IN WORK
    color_t color = get_color(col);
	double m = ((double)y1 - y2)/(x1-x2);
    for (int x = 0; x < x2; ++x)
    {
        // Using point-slope form: y - y1 = m * (x - x1)
        draw_pixel(x1+x,y1+m*(x-x1), color);
    }
}
