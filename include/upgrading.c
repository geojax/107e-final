//
// Created by wiche on 3/21/2023.
//
#include "player.h"
#include "crops.h"

#define NUM_UPGRADES 5
enum Upgrades {
    UPGRADE_FERTILIZER,
    UPGRADE_WATERING_CAN,
    UPGRADE_SPEED,
    UPGRADE_ROBOTS,
    UPGRADE_SPRINKLERS,
};

static int selected_upgrade = 0;

void upgrading_main_update(uint8_t input)
{
    if (input & KEY_UP) --selected_upgrade;
    if (input & KEY_DOWN) ++selected_upgrade;
    selected_upgrade %= NUM_UPGRADES;

    if (input & KEY_X)
    {
        switch (selected_upgrade)
        {
            case UPGRADE_FERTILIZER:
                // increase fertilizer mult
                break;
            case UPGRADE_WATERING_CAN:
                // increase watering can capacity
                break;
            case UPGRADE_SPEED:
                player_speed += 0.1;
                break;
            case UPGRADE_ROBOTS:
//                ++n_robots;
                break;
            case UPGRADE_SPRINKLERS:
//                ++n_sprinklers;
                break;
            case default:
                // uh oh!
        }
    }
}

void upgrading_update()
{
    switch (upgrading_state)
    {
        case UPGRADING_START_ANIM:
            // slide on to the screen.
            break;
        case UPGRADING_MAIN: {
            uint8_t input = input_get_all();
            upgrading_main_update(input);
            break;
        }
        case default:
            // uh oh!
    }
}