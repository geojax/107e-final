#include "crops.h"
#include "../stats.h"

double watering_can_capacity;
unsigned int fert_multiplier;

// Track location size of top right  
int TOP_LEFT_X;
int TOP_LEFT_Y;
int TILE_SIZE;

// Initialize 2D array storing crop tiles
crop_t crops[CROPS_H][CROPS_W];

void crops_init(int top_left_x, int top_left_y, int tile_size) 
{
	watering_can_capacity = 0;
	fert_multiplier = 1;

	set_watering_can_capacity(watering_can_capacity);
	set_fert_multiplier(fert_multiplier);

	// Initialize crop location and size
	TOP_LEFT_X = top_left_x;
	TOP_LEFT_Y = top_left_y;
	TILE_SIZE = tile_size;
}

// Helper function to get index of tile in 2D array from x/y coordinates
// type can be either 'x' or 'y'
int get_tile_index(int value, char type)
{
	int rel_value = 0;

	if (type == 'x') {
		rel_value = TOP_LEFT_X - value;
	} else if (type == 'y') {
		rel_value = TOP_LEFT_Y - value;
	}

	return rel_value / TILE_SIZE;
}

crop_status_t get_crop_status(int x, int y)
{
	// track players position relative to top 
	// left corner of the crop tiles
	int relative_x = TOP_LEFT_X - x;
	int relative_y = TOP_LEFT_Y - y;

	if (relative_x >= 0 && relative_y >= 0) {
		int tile_x = relative_x / TILE_SIZE;
		int tile_y = relative_y / TILE_SIZE;

		return crops[tile_y][tile_x].status;
	}

	return CROP_INVALID;
}

void update_all_crops()
{
	for (int i = 0; i < CROPS_H; i++) {
		for (int j  = 0; j < CROPS_W; j++) {
			// update timer, incorporate fertilizer
			crops[i][j].time_crop += fert_multiplier;

			// TODO: ...

			// update status according to water and timer
			if (crops[i][j].time_crop >= CROP_AGE_GROWN) {
				crops[i][j].status = CROP_COMPLETE;
			}
		}
	}
}

void crops_update(unsigned char input, int x, int y)
{
	fert_multiplier = get_fert_multiplier();
	watering_can_capacity = get_watering_can_capacity();

	// first update all crops properties
	update_all_crops();

	// track players position relative to top 
	// left corner of the crop tiles
	int relative_x = TOP_LEFT_X - x;
	int relative_y = TOP_LEFT_Y - y;

	if (relative_x >= 0 && relative_y >= 0) {
		int tile_x = relative_x / TILE_SIZE;
		int tile_y = relative_y / TILE_SIZE;
	}
}

void crops_draw() 
{
	for (int i = 0; i < CROPS_H; i++) {
		for (int j  = 0; j < CROPS_W; j++) {
			// ...
		}
	}
}

