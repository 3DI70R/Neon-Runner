#include "8bkc-hal.h"
#include "8bkc-ugui.h"
#include "ugui.h"
#include "string.h"
#include "neon.h"

#define BUFFER_COUNT 2

// TODO: actual double buffering

unsigned short screen_buffer[2][KC_SCREEN_W * KC_SCREEN_H];
unsigned short* current_buffer;
int current_buffer_id;

void screen_clear() 
{
    memset(current_buffer, 0, sizeof(unsigned short) * KC_SCREEN_W * KC_SCREEN_H);
}

void screen_draw_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) 
{
    current_buffer[x + y * KC_SCREEN_W] = kchal_fbval_rgb(r, g, b);
}

unsigned short* get_next_buffer() 
{
    current_buffer_id++;

    if(current_buffer_id >= BUFFER_COUNT) {
        current_buffer_id = 0;
    }

    return screen_buffer[current_buffer_id];
}

void display_buffer(unsigned short* buffer) 
{
    kchal_send_fb((const unsigned short*) screen_buffer);
}

void app_main() 
{
    kchal_init();

    neon_hal hal;

    hal.screen_width = KC_SCREEN_W;
    hal.screen_height = KC_SCREEN_H;
    hal.screen_clear = &screen_clear;
    hal.screen_draw_pixel = &screen_draw_pixel;
    hal.input_get = &kchal_get_keys;

    current_buffer = get_next_buffer();
    neon_state* neon = neon_init(hal);

    while(neon_tick(neon, 0.016f)) 
    {
        neon_render(neon);

        display_buffer(current_buffer);
        current_buffer = get_next_buffer();
    }

    neon_destroy(neon);
}