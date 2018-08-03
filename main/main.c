#include "8bkc-hal.h"
#include "8bkc-ugui.h"
#include "ugui.h"
#include "types.h"
#include "mathg.h"
#include "draw.h"
#include "transform.h"
#include "string.h"
#include "pipe.h"

#define IMAGE_WIDTH KC_SCREEN_W
#define IMAGE_HEIGHT KC_SCREEN_H
#define BUFFER_SIZE IMAGE_WIDTH * IMAGE_HEIGHT

byte fill_pattern[] = 
{
    255, 0, 0, 0, 0,   0, 0, 0, 
    0,   0, 0, 0, 0,   0, 0, 0, 
    0,   0, 0, 0, 255, 0, 0, 0, 
    0,   0, 0, 0, 0,   0, 0, 0, 
    255, 0, 0, 0, 0,   0, 0, 0, 
    0,   0, 0, 0, 0,   0, 0, 0,
    0,   0, 0, 0, 255, 0, 0, 0,
    0,   0, 0, 0, 0,   0, 0, 0,
};

color bg_palette[] =
{
    { .r = 255, .g = 206, .b = 13  },
    { .r = 82,  .g = 244, .b = 156 },
    { .r = 255, .g = 55,  .b = 170 },
    { .r = 106, .g = 154, .b = 235 }
};

color fg_palette[] =
{
    { .r = 255, .g = 0,   .b = 0   },
    { .r = 255, .g = 0,   .b = 128 },
    { .r = 0,   .g = 0,   .b = 255 },
    { .r = 0,   .g = 128, .b = 255 }
};

bezier bezier1 = 
{ 
    { .x = 0.0f, .y = 48.0f },
    { .x = 32.0f, .y = 48.0f  },
    { .x = 68.0f, .y = 17.0f },
    { .x = 68.0f, .y = 0.0f }
};

bezier bezier2 = 
{ 
    { .x = 68.0f, .y = 0.0f },
    { .x = 68.0f, .y = -25.0f },
    { .x = 24.0f, .y = -38.0f },
    { .x = -15.0f, .y = -38.0f }
};

bezier bezier3 = 
{ 
    { .x = -15.0f, .y = -38.0f },
    { .x = -40, .y = -70  },
    { .x = -80, .y = -70  },
    { .x = -60, .y = -130 }
};

bezier bezier4 = 
{ 
    { .x = 0.0f, .y = 48.0f + 80 },
    { .x = 32.0f, .y = 48.0f + 80  },
    { .x = 68.0f, .y = 17.0f + 80 },
    { .x = 68.0f, .y = 0.0f + 80 }
};

byte background_buffer[BUFFER_SIZE];
byte foreground_buffer[BUFFER_SIZE];
byte objects_buffer[BUFFER_SIZE];
unsigned short pocketsprite_buffer[BUFFER_SIZE];

vector2 position;
float angle = 0;
float scale = 1;

void blit_buffer_with_palette(unsigned short* pkspr, byte* game, color* palette) 
{
    color ul = palette[0];
    color ur = palette[1];
    color dl = palette[2];
    color dr = palette[3];

    for(int y = 0; y < IMAGE_HEIGHT; y++) 
    {
        color cl = color_lerp(ul, dl, y / 63.0f);
        color cr = color_lerp(ur, dr, y / 63.0f);

        for(int x = 0; x < IMAGE_WIDTH; x++) 
        {
            byte c = *game;

            if(c != 0) 
            {
                float t = c / 255.0f;
                color rgb = color_lerp(cl, cr, x / 79.0f);
                *pkspr = kchal_fbval_rgb(rgb.r * t, rgb.g * t, rgb.b * t);
            }

            pkspr++;
            game++;
        }
    }
}

void app_main() 
{
    kchal_init();

    draw_set_layer_params(LAYER_BG, KC_SCREEN_W, KC_SCREEN_H, background_buffer);
    draw_set_layer_params(LAYER_FG, KC_SCREEN_W, KC_SCREEN_H, foreground_buffer);
    draw_set_layer_params(LAYER_OBJ, KC_SCREEN_W, KC_SCREEN_H, objects_buffer);
    
    pipe p1 = pipe_create_from_bezier(&bezier1, 10, 20);
    pipe p2 = pipe_create_from_bezier(&bezier2, 20, 10);
    pipe p3 = pipe_create_from_bezier(&bezier3, 10, 10);
    pipe p4 = pipe_create_from_bezier(&bezier4, 10, 10);

    while(true) 
    {
        int keys = kchal_get_keys();
        if(keys & KC_BTN_DOWN) { position.y++; }
        if(keys & KC_BTN_UP) { position.y--; }
        if(keys & KC_BTN_LEFT) { position.x--; }
        if(keys & KC_BTN_RIGHT) { position.x++; }
        if(keys & KC_BTN_A) { scale += 0.01f; }
        if(keys & KC_BTN_B) { scale -= 0.01f; }
        if(keys & KC_BTN_START) { angle += 0.01f; }
        if(keys & KC_BTN_SELECT) { angle -= 0.01f; }

        transform_set_translation(position);
        transform_set_rotation(angle);
        transform_set_scale(scale);

        draw_switch_layer(LAYER_BG);
        draw_fill_pattern(fill_pattern, 8, 8, 0, 0);

        draw_switch_layer(LAYER_FG);
        draw_fill(0);

        pipe_draw(&p1);
        pipe_draw(&p2);
        pipe_draw(&p3);
        pipe_draw(&p4);

        memset(pocketsprite_buffer, 0, sizeof(unsigned short) * BUFFER_SIZE);
        blit_buffer_with_palette(pocketsprite_buffer, background_buffer, bg_palette);
        blit_buffer_with_palette(pocketsprite_buffer, foreground_buffer, fg_palette);
        kchal_send_fb(pocketsprite_buffer);
    }
}