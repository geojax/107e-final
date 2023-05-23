//
// Created by wiche on 3/22/2023.
//
#include "sprite.h"
#include "map.h"
int is_solid(int x, int y)
{
    int sprite_id = mget(x/8, y/8);
    return sprite_check_flag(sprite_id, 0);
}

int overlaps_solid(int x, int y)
{
    return is_solid(x, y)
        || is_solid(x + 7, y)
        || is_solid(x, y+7)
        || is_solid(x+7,y+7);
}
