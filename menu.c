#include "draw.h"
#include "menu.h"

int game_state = START;

void start_menu() {
    clear_screen(3);
    draw_string(0, 50, "arrow key", 15);
}

void pause_menu() {
    clear_screen(3);
    draw_string(0, 50, "ESC/P key", 15);
}

void death_menu() {
    clear_screen(3);
    draw_string(0, 50, "DEATH", 15);
}