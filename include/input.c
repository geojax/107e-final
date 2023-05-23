#include "input.h"
#include "printf.h"
#include "ps2.h"
#include "ps2_keys.h"
#include "interrupts.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "gpio_interrupts.h"
#include "malloc.h"
#include "timer.h"
#include "uart.h"


struct ps2_device {
    unsigned int clock;
    unsigned int data;

    unsigned int count;
    unsigned int index;

    unsigned char scancode;
};

int DEVICE_CODE = 0;

int release = 0;   // keep track of F0
int extended = 0;  // keep track of E0

uint8_t keys_active = 0;
static ps2_device_t *dev;


// helper function to discard any partial scancode and 
// re-start on new start bit as you did previously
void clear_iteration()
{
    dev->count = 0;
    dev->index = 0;
    dev->scancode = 0x0;
}

void update_active(unsigned char keycode)
{
	if (keycode == 0xF0) {
        release = 1;
    //} else if (keycode == 0xE0) {
    //    extended = 1;
    } else if (keycode == 0x4D || keycode == 0x76) {
        if (release == 0) {
            keys_active |= KEY_PAUSE;
        } else {
            keys_active &= ~KEY_PAUSE;
            release = 0;
        }
    } else if (keycode == 0x1A) {
        if (release == 0) {
            keys_active |= KEY_Z;
        } else {
            keys_active &= ~KEY_Z;
            release = 0;
        }
    } else if (keycode == 0x22) { 
        if (release == 0) {
            keys_active |= KEY_X;
        } else {
            keys_active &= ~KEY_X;
            release = 0;
        }

    } else if (keycode == 0x75) {
        //if (extended == 1) {
            if (release == 0) {
                keys_active |= KEY_UP;
            } else {
                keys_active &= ~KEY_UP;
                release = 0;
            }
            extended = 0;
        //}
    } else if (keycode == 0x6B) {
        //if (extended == 1) {
            if (release == 0) {
                keys_active |= KEY_LEFT;
            } else {
                keys_active &= ~KEY_LEFT;
                release = 0;
            }
            extended = 0;
        //}
    } else if (keycode == 0x72) {
        //if (extended == 1) {
            if (release == 0) {
                keys_active |= KEY_DOWN;
            } else {
                keys_active &= ~KEY_DOWN;
                release = 0;
            }
            extended = 0;
        //}
    } else if (keycode == 0x74) {
        //if (extended == 1) {
            if (release == 0) {
                keys_active |= KEY_RIGHT;
            } else {
                keys_active &= ~KEY_RIGHT;
                release = 0;
            }
            extended = 0;
        //}
    } else {
        release = 0;
        extended = 0;
    }
}

void input_read(unsigned int pc, void *aux_data) 
{
    //ps2_device_t *dev = (ps2_device_t *)aux_data;
    unsigned char bit = gpio_read(dev->data);

    // first bit is start bit
    if (dev->index == 0) {
        // check validity (low), restart if invalid
        if (bit != 0) {
            clear_iteration();
        } else {
            dev->index++;
        }

    // bit 1-8 bit are data bits, store into scancode
    } else if (dev->index < 9) {

        dev->scancode |= bit << (dev->index - 1);
        dev->count += bit;

        dev->index++;

    // bit 9 is parity bit
    } else if (dev->index == 9) {
        // check validity, restart if invalid
        if ((bit + dev->count) % 2 == 0) {
            clear_iteration();
        } else {
            dev->index++;
        }

    // bit 10 is stop bit
    } else {
        // check validity (high), restart if invalid
        if (bit != 1) {
            clear_iteration();
        } else {
        	update_active(dev->scancode);
            clear_iteration();
        }

    }

    gpio_clear_event(dev->clock);
}

void new_device(unsigned int clock_gpio, unsigned int data_gpio)
{
    interrupts_init();
    gpio_init();
    timer_init();

    dev = malloc(sizeof(*dev));

    dev->clock = clock_gpio;
    gpio_set_input(dev->clock);
    gpio_set_pullup(dev->clock);

    dev->data = data_gpio;
    gpio_set_input(dev->data);
    gpio_set_pullup(dev->data);

    // enable detection of falling edge events on the device's clock GPIO
    printf("Initializing interrupts!\n");
    gpio_interrupts_init();
    gpio_enable_event_detection(dev->clock, GPIO_DETECT_FALLING_EDGE);
    gpio_interrupts_register_handler(dev->clock, input_read, dev);
    gpio_interrupts_enable();
    printf("Interrupts Initialized!\n");

}

void device_init(int device) 
{
	if (device == DEVICE_CODE_KEYBOARD) {
		DEVICE_CODE = device;
		new_device(KEYBOARD_CLOCK, KEYBOARD_DATA);

	} else if (device == DEVICE_CODE_CONTROLLER) {
		// TO BE CONFIGURED
	} else {
		printf("DEVICE: %x NOT CONFIGURED!", device);
	}
}


uint8_t input_get_all() 
{
	return keys_active;
}

int is_key_down(uint8_t key) 
{
	return keys_active & (1 << key);
}
