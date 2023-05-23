#ifndef CROPS_HEADER
#define CROPS_HEADER 

#include <stdint.h>
#include <stddef.h>
#include "sprite.h"

#define CROPS_W 16 // in pixels
#define CROPS_H 12 // in number of 

#define CROP_AGE_1 300
#define CROP_AGE_2 450
#define CROP_AGE_3 600
#define CROP_AGE_GROWN 750

typedef enum {
    CROP_WHEAT = 1
} crop_type_t;

typedef enum {
    CROP_INVALID = 0,
    CROP_EMPTY = 1,
    CROP_GROWING = 2,
    CROP_COMPLETE = 3
} crop_status_t;


typedef struct {
    crop_status_t status;                
    crop_type_t type;

    //unsigned int time_planted;
    unsigned int time_crop;

    unsigned int water_status;

    sprite_t sprite;  
} crop_t;

typedef struct {
    crop_t crops[CROPS_W][CROPS_H];
} crops_t; 


// Initialize the sprites module.
// malloc space for SPRITESHEET_W * SPRITESHEET_H sprites.
// initialize spritesheet to black.
void crops_init();

// Get status of crop
// Return value crop status
crop_status_t get_crop_status(int x, int y);

// Update crop struct values for each tile to handle crop growing
// Update time and sprites for all crops, kills drowned and dried 
// crops, marks complete crops as such
// No return value
void crops_update(int x, int y);

// Redraw all crops
// No return value
void crops_draw();

#endif