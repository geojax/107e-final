#include "draw.h"
#include "sprite.h"
#include "timer.h"
#include "input.h"
#include "pico.h"
#include "interrupts.h"
#include "menu.h"

static volatile int ticks = 0;

static int paused = 0;

// initialize all the relevant modules.
void pico_init(void (*fn_init)(void), void (*fn_update)(void), void (*fn_draw)(void))
{
    draw_init();
    sprite_init();
    device_init(DEVICE_CODE_KEYBOARD);
    interrupts_global_enable();
    // input_init();
    // sound_init();
//     map_init();
    fn_init();
    palt(BLACK, 1);

    while (1)
    {
        fn_update();
        fn_draw();
        pico_flip();
        fn_draw();
    }
}

void pico_flip()
{
    flip();
    while (timer_get_ticks() - ticks < 40000);
    ticks = timer_get_ticks();
}

void pico_update();
void pico_main();
