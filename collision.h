//
// Created by wiche on 3/22/2023.
//
#ifndef COLLISION_HEADER
#define COLLISION_HEADER

#include "sprite.h"

int is_solid(int x, int y);

// x, y are the top left of an 8x8 square.
// return whether the 8x8 square is
// overlapping a solid tile.
int overlaps_solid(int x, int y);
#endif //MENU_C_COLLISION_H
