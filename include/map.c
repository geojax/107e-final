#include "map.h"
#include "printf.h"
#define MAP_EMPTY 0
#define SCREEN_TILE_W 16
#define SCREEN_TILE_H 16

uint8_t map[MAP_H][MAP_W];

void map_init() 
{
	// initialize map to be empty
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			map[i][j] = MAP_EMPTY;
		}
	}
}

int mget(int tile_x, int tile_y)
{
	return map[tile_y % MAP_H][tile_x % MAP_W];
}

void mset(int n, int tile_x, int tile_y)
{
	map[tile_x % MAP_W][tile_y % MAP_H] = n;
}

void map_from_string(const char *data)
{
    for (int i = 0; i < MAP_H * MAP_W; ++i)
    {
        int x = i % MAP_W;
        int y = i / MAP_H;
        map[y][x] = data[i];
    }
}

void map_draw(int tile_x, int tile_y)
{
    palt(BLACK, 0);
    for (int y = tile_y; y < tile_y + SCREEN_TILE_H; ++y)
    {
        for (int x = tile_x; x < tile_x + SCREEN_TILE_W; ++x)
        {
            int pixel_x = x * 8;
            int pixel_y = y * 8;
            int sprite_id = map[y][x];
            sprite_draw(sprite_id, pixel_x % 128, pixel_y % 128);
        }
    }
    palt(BLACK,1);
}

void map_from_arr(int data[], int w, int h)
{
    for (int y = 0; y < MAP_H && y < h; ++y)
    {
        for (int x = 0; x < MAP_W && x < w; ++x)
        {
            map[y][x] = data[y * MAP_W + x];
        }
    }
}

void draw_map_around(int x, int y)
{
    int top_left, top_right, bot_left, bot_right;
    top_left = mget(x / 8, y / 8);
    top_right = mget((x+7) / 8, y / 8);
    bot_left = mget(x / 8, (y+7) / 8);
    bot_right = mget((x+7) / 8, (y+7) / 8);

    sprite_draw(top_left,x/8*8 % 128, y/8*8 % 128);
    sprite_draw(top_right,(x+7)/8*8 % 128, y/8*8 % 128);
    sprite_draw(bot_left,x/8*8 % 128, (y+7)/8*8 % 128);
    sprite_draw(bot_right,(x+7)/8*8 % 128, (y+7)/8*8 % 128);
}
