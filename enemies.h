#ifndef ENEMIES_HEADER
#define ENEMIES_HEADER 

#include <stdint.h>
#include <stddef.h>
#include "sprite.h"

#define MAX_ENEMIES 16

typedef enum {
    ENEMY_WAITING = 0,
    ENEMY_WALKING = 1,
    ENEMY_SHOOTING = 2,
    ENEMY_DEAD = 10
} enemy_status_t;

typedef enum {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
} direction_t;


typedef struct {
    enemy_status_t status;  

    direction_t direction;  

    unsigned int time_enemy;

    int sprite;  

    int hp;

    double enemy_x;
    double enemy_y;
    double old_x;
    double old_y;

    int just_died;
} enemy_t;


// Initialize the sprites module.
// malloc space for SPRITESHEET_W * SPRITESHEET_H sprites.
// initialize spritesheet to black.
void enemies_init();

// Spawn single enemy for test purposes

void single_enemy_spawn(int index, int sprite, enemy_status_t status, int x, int y);

// Spawn all enemies on given map based on flag of each tile.
void enemies_spawn(int tile_x, int tile_y);

// Update enemy struct values for each tile to handle enemy walking,
// shooting, and waiting. Shooting involves shooting on bullet
// from bullet.c
void enemy_update();

// Redraw all enemies
// No return value
void enemies_draw();

// When player moves into new room, destroy all enemies in previous room and spawn new ones according to map layout
void reset_enemies(int tile_x, int tile_y);

// Return all enemies in array
enemy_t* get_all_enemies();

void enemy_damage(int index, int damage);

#endif