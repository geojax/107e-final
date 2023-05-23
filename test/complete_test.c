//
// Created by wiche on 3/21/2023.
//
#include "pico.h"
#include "player.h"
#include "crops.h"
#include "input.h"
#include <stdint.h>



enum State {
    START_MENU,
    MAIN,
    UPGRADING,
};

static State state = MAIN;
void complete_init()
{
    player_init();
    crops_init();
}

void complete_main_update()
{
    uint8_t input = input_get_all();
    player_update(input); // move player based on input
    crops_update(input); // crops grow or die
}

void complete_upgrading_update()
{
    uint8_t input = input_get_all();
    player_update(input); // move player based on input

}

void complete_update()
{
    switch (state)
    {
        case START_MENU:
            // stuff
            break;
        case MAIN:
            complete_main_update();
            break;
        case UPGRADING:
            complete_upgrading_update();
            break;
        case default:
            // uh oh!
    }
}

void complete_draw()
{

}

void complete_test()
{
    pico_init(complete_init, complete_update, complete_draw);
}