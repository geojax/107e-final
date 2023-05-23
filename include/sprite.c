#include "sprite.h"
#include "draw.h"
#include "malloc.h"
#include "assert.h"
#include "strings.h"
#include "printf.h"
static sprite_t sprite_mem[NUM_SPRITES];
void sprite_init()
{
    size_t n_sprites = SPRITESHEET_W * SPRITESHEET_H;
    size_t n_bytes = n_sprites * sizeof(sprite_t);
//    sprite_mem = malloc(n_bytes);
    memset(sprite_mem, n_bytes, 0);
}

sprite_t sprite_set(uint32_t n, sprite_t sprite)
{
    sprite_t ret = sprite_mem[n % NUM_SPRITES];
    sprite_mem[n] = sprite;
    return ret;
}

// last char of img is the sprite's flags + 1.
// rest of img is the rows of pixel data.
sprite_t sprite_from_string(uint32_t n, const char *img)
{
    printf("setting sprite #%d\n", (int)n);
    sprite_t *spr = &(sprite_mem[n % NUM_SPRITES]);
    sprite_t ret = *spr;

    // flags
    uint8_t flags = 0;
    for (int i = 0 ; i < 8; ++i)
    {
        // least significant flag is first
        if (img[i] == '1')
        {
            flags |= 1 << i;
        }
    }

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            char c = img[y * 8 + x + 8];
            uint8_t *px = &(spr->pixels[y][x]);
            if ('0' <= c && c <= '9')
                *px = c - '0';
            else if ('a' <= c && c <= 'f')
                *px = c - 'a' + 10;

        }
    }
    spr->flags = flags;
    return ret;
}

// num_sprites: the number of sprites being entered, in case not receiving
// a full spritesheet
void spritesheet_from_string(const char *data, int num_sprites)
{
    int sprite_str_len = 72; // 8x8 sprite + 8 chars for flags
    for (int i = 0; i < num_sprites && i < NUM_SPRITES; ++i)
    {
        const char *c = &data[i * sprite_str_len];
        sprite_from_string(i, c);
    }
}

void sprite_draw(uint32_t n, uint32_t x, uint32_t y)
{
    sprite_t spr = sprite_mem[n % NUM_SPRITES];
    for (int sy = 0; sy < SPRITE_H; ++sy)
    {
        for (int sx = 0; sx < SPRITE_W; ++sx)
        {
            int p = spr.pixels[sy][sx];
            if (!is_transparent(p))
            {
                draw_pixel(x + sx, y + sy, spr.pixels[sy][sx]);
            }
        }
    }
}
void sprite_draw_with_flip(uint32_t n, uint32_t x, uint32_t y, int flip_h, int flip_v)
{
    sprite_t spr = sprite_mem[n % NUM_SPRITES];
    for (int sy = 0; sy < SPRITE_H; ++sy)
    {
        for (int sx = 0; sx < SPRITE_W; ++sx)
        {
            int px = sx;
            int py = sy;
            if (flip_h) px = SPRITE_W - 1 - px;
            if (flip_v) py = SPRITE_H - 1 - py;
            int p = spr.pixels[py][px];
            if (!is_transparent(p))
            {
                draw_pixel(x + sx, y + sy, p);
            }
        }
    }
}

void sprite_mdraw(uint32_t n, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            sprite_draw(i * SPRITESHEET_W + j + n, x + j * SPRITE_W, y + i * SPRITE_H);
        }
    }
}

// 0 <= flag <= 7
int sprite_check_flag(uint32_t n, uint8_t flag)
{
    return sprite_mem[n % NUM_SPRITES].flags & (1 << flag);
}

// 0 <= flag <= 7
void sprite_set_flag(uint32_t n, uint8_t flag)
{
    sprite_mem[n % NUM_SPRITES].flags |= (1 << flag);
}

sprite_t get_sprite(int n)
{
    return sprite_mem[n];
}
//
//void sprite_end()
//{
//    free(sprite_mem);
//}
