#ifndef MENU_HEADER
#define MENU_HEADER

enum {
    MAIN,
    START,
    DEATH,
    PAUSE,
};

extern int game_state;

void start_menu();

void pause_menu();

void death_menu();

#endif