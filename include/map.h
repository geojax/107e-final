#ifndef MAP_HEADER
#define MAP_HEADER

#include "sprite.h"
#include "draw.h"

#include <stdint.h>
#include <stddef.h>

#define MAP_W 128
#define MAP_H 64

// Initialize the maps module.
void map_init();
// Get sprite at x,y position of map
int mget(int tile_x, int tile_y);

// Set sprite at x,y position of map
void mset(int n, int tile_x, int tile_y);

// DEPRECATED - don't use!
void map_from_string(const char *data);

// please make data the right size, 128 x 64
void map_from_arr(int data[], int, int);

// x,y in tiles...
void map_draw(int x, int y);

// x, y in pixels...
void draw_map_around(int x, int y);
#endif