// player.c
#include "map.h"
#include "printf.h"
#include <stdint.h>
#include "sprite.h"
#include "input.h"
#include "draw.h" // for screen_w and screen_h
#include "stats.h"
#include "collision.h"
#include "enemies.h"
#include "art.h"
#include "menu.h"

#define SWORD_DAMAGE 50

static uint32_t player_sprite = 1;
static double player_x = 65;
static double player_y = 64;
static int player_flip_h = 0;
static int player_flip_v = 0;
static int player_anim_timer = 0;
static int old_x = 65;
static int old_y = 64;
static int old_world_x;
static int old_world_y;
static int anim_frame = 0;
void switch_room(int tile_x, int tile_y)
{
    printf("Switching to room (%d, %d)\n", tile_x, tile_y);
    map_draw(tile_x, tile_y);
    flip();
    map_draw(tile_x, tile_y);
    reset_enemies(tile_x, tile_y);
}
static direction_t player_direction = RIGHT;
static double dx, dy;

enum {
    WALK_LEFT,
    WALK_RIGHT,
    WALK_UP,
    WALK_DOWN,
    IDLE,
    ATK_LEFT,
    ATK_RIGHT,
    ATK_UP,
    ATK_DOWN
};

static int anim_state;

static void update_player_anim();

void player_init()
{
    player_sprite = SP_PLAYER_IDLE;
    player_x = 8;
    player_y = 8;
    old_world_x = 0;
    old_world_y = 0;
    set_player_speed(1);
}

// Helper function to update player animation state in regards to weapon direction
static void update_weapon_anim_state()
{
    if (player_direction == LEFT) {
        anim_state = ATK_LEFT;
    } else if (player_direction == RIGHT) {
        anim_state = ATK_RIGHT;
    } else if (player_direction == UP) {
        anim_state = ATK_UP;
    } else {
        anim_state = ATK_DOWN;
    }
}

// Helper function to initiate player animation (walking)
static void update_player_anim()
{
    player_anim_timer++;

    // if player movement/speed is zero, only modify the "pulling back" of stab (every two frames)
    if (dx == 0 && dy == 0) {
        switch (anim_state) {
            case ATK_RIGHT:
                player_sprite = SP_PLAYER_ATK_RIGHT + anim_frame;
                player_flip_h = 0;
                if (player_anim_timer > 15) player_sprite = SP_PLAYER_RIGHT;
                break;
            case ATK_LEFT:
                player_sprite = SP_PLAYER_ATK_RIGHT + anim_frame;
                player_flip_h = 1;
                if (player_anim_timer > 15) player_sprite = SP_PLAYER_RIGHT;
                break;
            case ATK_UP:
                player_sprite = SP_PLAYER_ATK_UP + anim_frame;
                player_flip_h = 0;
                if (player_anim_timer > 15) player_sprite = SP_PLAYER_UP;
                break;
            case ATK_DOWN:
                player_sprite = SP_PLAYER_ATK_DOWN + anim_frame;
                player_flip_h = 0;
                if (player_anim_timer > 15) player_sprite = SP_PLAYER_DOWN;
                break;
        }
        anim_frame = player_anim_timer % 10 < 5;
        return;
    }

    switch (anim_state)
    {
        case IDLE:
            player_sprite = SP_PLAYER_IDLE;
            anim_frame = 0;
            player_flip_h = 0;
            break;
        case WALK_LEFT:
            player_sprite = SP_PLAYER_RIGHT + anim_frame;
            player_flip_h = 1;
            break;
        case WALK_RIGHT:
            player_sprite = SP_PLAYER_RIGHT + anim_frame;
            player_flip_h = 0;
            break;
        case WALK_UP:
            player_sprite = SP_PLAYER_UP + anim_frame;
            player_flip_h = 0;
            break;
        case WALK_DOWN:
            player_sprite = SP_PLAYER_DOWN + anim_frame;
            player_flip_h = 0;
            break;
    }
    anim_frame = player_anim_timer % 10 < 5;
}

// Get x value (top left corner) of tile player is facing to
int get_front_tile_x() 
{
    if (player_direction == UP) {
        return player_x;
    } else if (player_direction == DOWN) {
        return player_x;
    } else if (player_direction == LEFT) {
        return player_x - SPRITE_W;
    } else if (player_direction == RIGHT) {
        return player_x + SPRITE_W;
    }
    return player_x;
}

// Get y value (top left corner) of tile player is facing to
int get_front_tile_y() 
{
    if (player_direction == UP) {
        return player_y - SPRITE_H;
    } else if (player_direction == DOWN) {
        return player_y + SPRITE_H;
    } else if (player_direction == LEFT) {
        return player_x;
    } else if (player_direction == RIGHT) {
        return player_x;
    }
    return player_y;
}

// Helper function to get bool (0/1) value on whether projected 1D sides with values max and min overlap
static int get_side_overlap(int v1_max, int v1_min, int v2_max, int v2_min) 
{
    return (v1_max >= v2_min) && (v2_max >= v1_min);
}

void player_update(uint8_t input)
{
    // Movement
    old_x = player_x;
    old_y = player_y;
    old_world_x = (int)player_x / 128;
    old_world_y = (int)player_y / 128;
    double player_speed = get_player_speed();
    dx = dy = 0;
    
    update_player_anim();

    if (input & KEY_LEFT) {
        dx -= player_speed;
        player_direction = LEFT;
        anim_state = WALK_LEFT;
        update_player_anim();
    }
    else if (input & KEY_RIGHT) {
        dx += player_speed;
        player_direction = RIGHT;
        anim_state = WALK_RIGHT;
        update_player_anim();
    }
    if (input & KEY_UP) {
        dy -= player_speed;
        player_direction = UP;
        anim_state = WALK_UP;
        update_player_anim();
    }
    else if (input & KEY_DOWN) {
        dy += player_speed;
        player_direction = DOWN;
        anim_state = WALK_DOWN;
        update_player_anim();
    }

    double new_x = player_x + dx;
    double new_y = player_y + dy;

    if (overlaps_solid(new_x, player_y)) {
        dx = 0;
    }
    if (overlaps_solid(player_x, new_y)) {
        dy = 0;
    }
    player_x += dx;
    player_y += dy;
//
    if ((int)player_x / 128 != old_world_x)
    {
        switch_room((int)player_x / 128 * 16, old_world_y * 16);
        old_world_x = player_x / 128;
    }
    if ((int)player_y / 128 != old_world_y)
    {
        switch_room(old_world_x * 16, (int)player_y / 128 * 16);
    }
    // bound player to the screen
//    if (player_x + SPRITE_W > SCREEN_W) player_x = SCREEN_W - SPRITE_W;
//    if (player_x < 0) player_x = 0;
//    if (player_y + SPRITE_H > SCREEN_H) player_y = SCREEN_H - SPRITE_H;
//    if (player_y < 0) player_y = 0;


    // kill player if enemy is touched/there exists overlap between enemy and player
    enemy_t* enemies;
    enemies = get_all_enemies();

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].status != ENEMY_DEAD) {
            if (get_side_overlap(player_x + SPRITE_W - 1, player_x + 1, enemies[i].enemy_x + SPRITE_W - 1, enemies[i].enemy_x + 1) && 
                get_side_overlap(player_y + SPRITE_H - 1, player_y + 1, enemies[i].enemy_y + SPRITE_H - 1, enemies[i].enemy_y + 1)) {                
                game_state = DEATH;
            }
        } 
    }

    if (input & KEY_X) {
        player_anim_timer = 0;
        update_weapon_anim_state();

        int front_x = get_front_tile_x();
        int front_y = get_front_tile_y();

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].status != ENEMY_DEAD) {
                if (get_side_overlap(front_x + SPRITE_W, front_x, enemies[i].enemy_x + SPRITE_W, enemies[i].enemy_x) && 
                    get_side_overlap(front_y + SPRITE_H, front_y, enemies[i].enemy_y + SPRITE_H, enemies[i].enemy_y)) { 
                    anim_state = WALK_DOWN;
                    enemy_damage(i, SWORD_DAMAGE);
                }
            } 
        }
    }
}

void player_draw()
{
//    int top_left, top_right, bot_left, bot_right;
//    top_left = mget(old_x / 8, old_y / 8);
//    top_right = mget((old_x+7) / 8, old_y / 8);
//    bot_left = mget(old_x / 8, (old_y+7) / 8);
//    bot_right = mget((old_x+7) / 8, (old_y+7) / 8);
//
//    sprite_draw(top_left,old_x/8*8, old_y/8*8);
//    sprite_draw(top_right,(old_x+7)/8*8, old_y/8*8);
//    sprite_draw(bot_left,old_x/8*8, (old_y+7)/8*8);
//    sprite_draw(bot_right,(old_x+7)/8*8, (old_y+7)/8*8);
    draw_map_around(old_x, old_y);
    sprite_draw_with_flip(player_sprite,(int)player_x % 128,(int)player_y % 128,player_flip_h,player_flip_v);
}

int get_player_x() 
{
    return player_x;
}

int get_player_y() 
{
    return player_y;
}

int get_player_tile_x() 
{
    return player_x / 8;
}

int get_player_tile_y() 
{
    return player_y / 8;
}
