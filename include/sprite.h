#ifndef SPRITE_HEADER
#define SPRITE_HEADER

#include <stdint.h>
#include <stddef.h>

#define SPRITE_W 8 // in pixels
#define SPRITE_H 8 // in pixels
#define SPRITESHEET_W 16 // in sprites
#define SPRITESHEET_H 16 // in sprites
#define NUM_SPRITES (SPRITESHEET_W * SPRITESHEET_H)

typedef struct {
    uint8_t pixels[SPRITE_H][SPRITE_W];
    uint8_t flags;
} sprite_t; 

// Initialize the sprites module.
// malloc space for SPRITESHEET_W * SPRITESHEET_H sprites.
// initialize spritesheet to black.
void sprite_init();

// Set nth sprite to `sprite`
// Return the sprite being replaced.
sprite_t sprite_set(uint32_t n, sprite_t sprite);

// Set nth sprite to the sprite represented by `img`.
// `img` is a string of hex characters corresponding to the 16
// colors of the palette. Invalid characters in `img` are skipped.
// Returns sprite being replaced.
sprite_t sprite_from_string(uint32_t n, const char *img);

// oh boy...
void spritesheet_from_string(const char *data, int num_sprites);

// Draw nth sprite at screen coordinates (`x`, `y`)
void sprite_draw(uint32_t n, uint32_t x, uint32_t y);

void sprite_draw_with_flip(uint32_t n, uint32_t x, uint32_t y, int flip_h, int flip_v);
// Sprite multi-draw
// num: Number of the top-left sprite to be drawn.
// x, y: top-left screen-coordinate of where the sprites will be drawn
// w, h: width and height, in sprites, of the sprites to be drawn.
void sprite_mdraw(uint32_t num, uint32_t x, uint32_t y, uint32_t w, uint32_t h);

// n: sprite id, flag: which flag (0-7) to check
int sprite_check_flag(uint32_t n, uint8_t flag);

// free sprite memory.
void sprite_end();
#endif
