//
// Created by wiche on 3/21/2023.
//
#include "draw.h"
#include "sprites.h"
#inclue "stats.c"
#define MAX_ROBOTS 64
#define Y_BOUND_HIGH SCREEN_H
#define Y_BOUND_LOW 64 // should be the top of the crops
struct robot {
    double x, y;
    int dir_y; // the direction this robot is facing. -1 when robot reverses direction
    int column; // the column this robot will harvest
    int sprite;
};
robot robots[MAX_ROBOTS];
double robot_speed;

void robots_init()
{
}

void robots_update()
{
    int n_robots = get_n_robots();
    for (int i = 0; i < n_robots && i < MAX_ROBOTS; ++i)
    {
        robots[i].y += robot_speed * robots[i].dir_y;
        if (robots[i].y > SCREEN_H || robots[i].y )
    }
}

void robots_draw()
{
    int n_robots = get_n_robots();
    for (int i = 0; i < n_robots && i < MAX_ROBOTS; ++i)
    {
        struct robot r = robots[i];
        sprite_draw(r.sprite, r.x, r.y);
    }
}