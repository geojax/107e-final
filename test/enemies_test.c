#include "player.h"
#include "input.h"
#include "sprite.h"
#include "enemies.h"
#include "art.h"
static void init_enemies()
{
    player_init();
    enemies_init();
    //device_init(DEVICE_CODE_KEYBOARD);
    load_sprites();

}
static int has_spawned = 0;
static void update_enemies()
{
    //player_update(input_get_all());
    if (!has_spawned) single_enemy_spawn(0, SP_ENEMY1_UP, ENEMY_WAITING, 60, 60 );
    has_spawned = 1;
    enemy_update();
}

static void draw_enemies()
{
    clear_screen(BLACK);
    enemies_draw();
}

void test_enemies() 
{ 
//    init_enemies();
    pico_init(init_enemies, update_enemies, draw_enemies);
//    pico_init(init, update, draw);
}
