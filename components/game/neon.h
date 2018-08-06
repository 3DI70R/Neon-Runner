#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Hardware abstraction layer structure
typedef struct 
{
    // width of screen surface
    int screen_width;

    // height of screen surface
    int screen_height;

    // function that draws pixel to result buffer
    // x and y will be always in valid range
    void (*screen_draw_pixel)(int x, int y, unsigned char r, unsigned char g, unsigned char b);

    // function that clears result buffer
    void (*screen_clear)();

    // function that gets player input
    unsigned int (*input_get)();
}
neon_hal;

typedef void* neon_state;

// initializes new game state with specified HAL settings
neon_state* neon_init(neon_hal params);

// Advances game state to specified delta time
int neon_tick(neon_state* state, float delta_time);

// Renders current game state to target buffer using screen_draw_pixel from HAL
void neon_render(neon_state* state);

// Destroys allocated resources
void neon_destroy(neon_state* state);

#ifdef __cplusplus
}
#endif

