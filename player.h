// player.h
#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include <stdint.h>

void player_init();

void player_update(uint8_t input);

void player_draw();

int get_player_x();

int get_player_y();

int get_player_tile_x();

int get_player_tile_y();

void switch_room(int tile_x, int tile_y);

#endif
