#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "keyboard.h"
#include <stdint.h>

#define DEVICE_CODE_KEYBOARD 0x0
#define DEVICE_CODE_CONTROLLER 0x1

#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_UP 4
#define KEY_DOWN 8
#define KEY_Z 16
#define KEY_X 32
#define KEY_PAUSE 64


void device_init(int device);


void input_start();


uint8_t input_get_all();


int is_key_down(uint8_t key);


void new_device(unsigned int clock_gpio, unsigned int data_gpio);


void update_active(unsigned char keycode);


#endif
