#include "player.h"
#include "input.h"
#include "sprite.h"
#include "art.h"
static void init()
{
    player_init();
    load_sprites();
}

static int t = 0;
static void update()
{
    player_update(input_get_all());
}

static void draw()
{
    clear_screen(BLACK);
    sprite_draw(0,0,0);
    sprite_draw(16,8,0);
}

void test_player() 
{ 
    pico_init(init, update, draw);

    init();
    //draw();
//    pico_init(init, update, draw);
}
