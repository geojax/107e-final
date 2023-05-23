#include "enemies.h"
#include "rand.h"
#include "map.h"
#include "printf.h"
#include "stats.h"
#include "collision.h"
#include "art.h"
#define DEBUG 0

#define MAX_ENEMIES 16
#define ENEMY_TIME_SWAP 100
#define MAX_HP 100
#define NUM_STATES 3
#define NUM_DIRECTIONS 4

// Initialize 2D array storing crop tiles
enemy_t enemies[MAX_ENEMIES];

// helper function to generate random value out of range n
int rand_val(int n) 
{
	return rand() % n;
}

void enemies_init() 
{
	// initialize empty enemies array = enemies are all dead
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemy_t enemy;
		enemy.status = ENEMY_DEAD;

		enemies[i] = enemy;
	}
}

enemy_t create_enemy(int sprite, int hp, enemy_status_t status, int x, int y)
{
	enemy_t enemy;

	enemy.status = status;
	enemy.sprite = sprite;
	enemy.enemy_x = enemy.old_x = x;
	enemy.enemy_y = enemy.old_y = y;
	enemy.hp = hp;
	enemy.time_enemy = 0;

	return enemy;
}

void single_enemy_spawn(int index, int sprite, enemy_status_t status, int x, int y)
{
	enemies[index] = create_enemy(sprite, MAX_HP, status, x, y);
	printf("Enemy spawned at index %d with status %d! \n", index, status);
}

void enemies_spawn(int tile_x, int tile_y) 
{
	int n = 0;

	if (DEBUG) {
		printf("Spawning all enemies ...\n");
	}

	for (int i = 0; i < SCREEN_W/SPRITE_W; i++) {
		for (int j = 0; j < SCREEN_H/SPRITE_H; j++) {
			int tile_n = mget(tile_x + i, tile_y + j);
			if (sprite_check_flag(tile_n, 1)) {
				if (n < MAX_ENEMIES) {
					// initialize new enemy
					enemy_t enemy = create_enemy(SP_ENEMY1_UP, MAX_HP, ENEMY_WAITING, (tile_x + i) * SPRITE_W, (tile_y + j) * SPRITE_H);

					enemies[n] = enemy;
                    printf("enemies.c: enemy at %d, %d\n", (int)enemy.enemy_x, (int)enemy.enemy_y);
					n++;
				}
			}
		}
	}

	if (DEBUG) {
		printf("Spawned %d enemies!\n", n);
	}
}

direction_t invert_direction(direction_t direction)
{
	if (direction <= 2) {
		direction += 2;
	} else {
		direction -= 2;
	}
    return direction;
}

enemy_t enemy_move(enemy_t enemy)
{
    int invert = 0;

    // Movement
    double dx, dy;
    // use player speed / 3 for now for enemy_speed
    double enemy_speed = get_player_speed() / 3;
    enemy.old_x = enemy.enemy_x;
    enemy.old_y = enemy.enemy_y;
    dx = dy = 0;

    if (enemy.direction == LEFT)
    {
        dx -= enemy_speed;
    }
    if (enemy.direction == RIGHT)
    {
        dx += enemy_speed;
    }
    if (enemy.direction == UP)
    {
        dy -= enemy_speed;
    }
    if (enemy.direction == DOWN)
    {
        dy += enemy_speed;
    }

    double new_x = enemy.enemy_x + dx;
    double new_y = enemy.enemy_y + dy;

    if (overlaps_solid(new_x, enemy.enemy_y)) {
        dx = 0;
        invert = 1;
    }
    if (overlaps_solid(enemy.enemy_x, new_y)) {
        dy = 0;
        invert = 1;
    }

    enemy.enemy_x += dx;
    enemy.enemy_y += dy;

    // bound enemy to the screen
    if (enemy.enemy_x + SPRITE_W > SCREEN_W) {
    	enemy.enemy_x = SCREEN_W - SPRITE_W;
    	invert = 1;
    }
    if (enemy.enemy_x < 0) {
    	enemy.enemy_x = 0;
    	invert = 1;
    }
    if (enemy.enemy_y + SPRITE_H > SCREEN_H) {
    	enemy.enemy_y = SCREEN_H - SPRITE_H;
		invert = 1;
	}
    if (enemy.enemy_y < 0) {
    	enemy.enemy_y = 0;
    	invert = 1;
    }

    if (invert) {
    	enemy.direction = invert_direction(enemy.direction);
    }

    return enemy;
}

void update_all_enemies()
{
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].status != ENEMY_DEAD) {
			//printf("%d\n", enemies[i].time_enemy);
			// update state of enemy
			if (enemies[i].time_enemy >= ENEMY_TIME_SWAP) {
				enemies[i].status = rand_val(NUM_STATES);
				enemies[i].direction = rand_val(NUM_DIRECTIONS);

				enemies[i].time_enemy = 0;

				if (DEBUG) {
					printf("Status: %d, Direction: %d\n", enemies[i].status, enemies[i].direction);
				}
			}
			
			// update position of each enemy
			if (enemies[i].status != ENEMY_WALKING) {
				enemies[i] = enemy_move(enemies[i]);
			}

			enemies[i].time_enemy += 1;
            switch (enemies[i].direction) {
                case LEFT:
                    enemies[i].sprite = SP_ENEMY1_RIGHT;
                    break;
                case RIGHT:
                    enemies[i].sprite = SP_ENEMY1_RIGHT;
                    break;
                case UP:
                    enemies[i].sprite = SP_ENEMY1_UP;
                    break;
                case DOWN:
                    enemies[i].sprite = SP_ENEMY1_UP;
                    break;
            }
		}
	}
}

void enemy_update()
{
	// update all enemy timers and states if applicable
	if (DEBUG) {
		//printf("Updating all enemies\n");
	}
	update_all_enemies();
}

void reset_enemies(int tile_x, int tile_y) 
{
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemies[i].status = ENEMY_DEAD;
	}

	enemies_spawn(tile_x, tile_y);
}

enemy_t* get_all_enemies()
{
	return enemies;
}

void enemies_draw()
{
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].status != ENEMY_DEAD || enemies[i].just_died == 1) {
			// draw enemies
            enemy_t e = enemies[i];
            draw_map_around(e.old_x, e.old_y);
			sprite_draw_with_flip(e.sprite, e.enemy_x, e.enemy_y, e.direction == LEFT, e.direction == DOWN);
			enemies[i].just_died = 0;
		}
	}
}

void enemy_damage(int index, int damage)
{
	// kill enemy if damage is enough
	if (damage >= enemies[index].hp) {
		enemies[index].status = ENEMY_DEAD;
		enemies[index].just_died = 1;
	} else {
		enemies[index].hp -= damage;
	}
}
