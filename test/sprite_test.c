#include "pico.h"
#include "sprite.h"
#include "draw.h"
#include "input.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "gpio_interrupts.h"
#include "assert.h"
#include "printf.h"
#include "art.h"
/* following test is outdated...
void test_sprites(void)
{
    pico_init();

    sprite_t white_square;
    for (int y = 0; y < SPRITE_H; ++y)
    {
        for (int x = 0; x < SPRITE_W; ++x)
        {
            white_square.pixels[y][x] = WHITE;
        }
    }
    sprite_set(0, white_square);

    // should be in center of screen
    sprite_draw(0, 64, 64);

    sprite_t spr = sprite_from_string(1,"88888888899999988999999888999998008c8800000080008888888800008000");
    // set red transparent
    palt(RED);
    // set red not transparent
    palt(RED);
    // swap red and green
    pal_sub(RED, GREEN);
    // reset palette
    pal_reset();
    sprite_draw(1,32,32);
    flip();
}*/

int x = 64, y = 64;
int plr_spr = 1;
sprite_t get_sprite(int);
static void test_sprite_init()
{
    const char * data = "111000000bbbbb00b0baaaa000afcfc0000ffff00003b30000b3b4440b03b4a400040444";
   sprite_from_string(plr_spr, data);
   sprite_from_string(2, data);
   sprite_from_string(3, data);
//   sprite_t spr = get_sprite(1);
//   printf("%d", spr.flags);
   assert(sprite_check_flag(1,0));
   assert(sprite_check_flag(1,1));
   assert(sprite_check_flag(1,2));
   assert(!sprite_check_flag(0,3));
   assert(!sprite_check_flag(0,4));
   assert(!sprite_check_flag(0,5));

   load_sprites();
   assert(!sprite_check_flag(SP_SANDTILE,0));
   assert(sprite_check_flag(SP_BUSHTILE,0));
}

static void test_sprite_update()
{
    x += 1;
}

static void test_sprite_draw()
{
    clear_screen(BLACK);
    for (int i = 0; i < 24; ++i)
    {
        sprite_draw(i, i / 16 * 8, i % 16 * 8);
    }
    for (int i = 0; i < 24; ++i)
    {
       sprite_draw_with_flip(i, i / 16 * 8 + 32, i % 16 * 8, 1, 0);
    }
}

// new file to be created, temporarily here
void test_input(void)
{
    device_init(DEVICE_CODE_KEYBOARD);
}

void sprite_main(void)
{
    //test_input();
    //interrupts_global_enable();
    pico_init(test_sprite_init, test_sprite_update, test_sprite_draw);
}
