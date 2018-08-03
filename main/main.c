#include "8bkc-hal.h"
#include "8bkc-ugui.h"
#include "ugui.h"
#include "types.h"
#include "mathg.h"
#include "draw.h"
#include "transform.h"
#include "string.h"

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

bezier bezier_curve = 
{ 
    { .x = 0.0f, .y = 48.0f },
    { .x = 32.0f, .y = 48.0f  },
    { .x = 68.0f, .y = 17.0f },
    { .x = 68.0f, .y = 0.0f }
};

byte background_buffer[BUFFER_SIZE];
byte foreground_buffer[BUFFER_SIZE];
byte objects_buffer[BUFFER_SIZE];
unsigned short pocketsprite_buffer[BUFFER_SIZE];

segment segments[16];
vector2 position;
float angle = 0;
float scale = 1;

void blit_buffer(unsigned short* pkspr, byte* game, color* palette) 
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

    draw_set_buffer(KC_SCREEN_W, KC_SCREEN_H, background_buffer);
    bezier_rasterize(bezier_curve, segments, 10, 15, 16);

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

        vector2 p0 = { .x = 0, .y = 0 };
        vector2 p1 = { .x = 79, .y = 63 };
        vector2 v1 = transform_apply(p0, 1);
        vector2 v2 = transform_apply(p0, 0.8f);
        vector2 v3 = transform_apply(p1, 1);
        vector2 v4 = transform_apply(p1, 0.8f);

        draw_set_buffer(KC_SCREEN_W, KC_SCREEN_H, background_buffer);
        draw_fill_pattern(fill_pattern, 8, 8, 0, 0);

        draw_set_buffer(KC_SCREEN_W, KC_SCREEN_H, foreground_buffer);
        draw_fill(0);

        // debug
        draw_line(v1.x, v1.y, v2.x, v2.y, 255);
        draw_line(v3.x, v3.y, v4.x, v4.y, 255);

        for(int i = 1; i < 8; i++) 
        {
            segment seg = segment_evaluate(segments, 16, i / 7.0f);
            
            vector2 u = vector2_add(seg.position, vector2_from_angle(seg.angle + DEGTORAD(90), seg.width));
            vector2 d = vector2_add(seg.position, vector2_from_angle(seg.angle - DEGTORAD(90), seg.width));

            vector2 t1 = transform_apply(u, 1);
            vector2 t2 = transform_apply(vector2_lerp(u, d, 0.2f), 0.9f);
            vector2 t3 = transform_apply(vector2_lerp(u, d, 0.4f), 0.85f);
            vector2 t4 = transform_apply(vector2_lerp(u, d, 0.6f), 0.85f);
            vector2 t5 = transform_apply(vector2_lerp(u, d, 0.8f), 0.9f);
            vector2 t6 = transform_apply(d, 1);

            draw_line(t1.x, t1.y, t2.x, t2.y, 80);
            draw_line(t2.x, t2.y, t3.x, t3.y, 60);
            draw_line(t3.x, t3.y, t4.x, t4.y, 40);
            draw_line(t4.x, t4.y, t5.x, t5.y, 60);
            draw_line(t5.x, t5.y, t6.x, t6.y, 80);
        }

        for(int i = 1; i < 16; i++) 
        {
            segment s1 = segments[i - 1];
            segment s2 = segments[i];
            
            vector2 u1 = transform_apply(vector2_add(s1.position, vector2_from_angle(s1.angle + DEGTORAD(90), s1.width)), 1);
            vector2 u2 = transform_apply(vector2_add(s2.position, vector2_from_angle(s2.angle + DEGTORAD(90), s2.width)), 1);
            vector2 d1 = transform_apply(vector2_add(s1.position, vector2_from_angle(s1.angle - DEGTORAD(90), s1.width)), 1);
            vector2 d2 = transform_apply(vector2_add(s2.position, vector2_from_angle(s2.angle - DEGTORAD(90), s2.width)), 1);

            draw_set_buffer(KC_SCREEN_W, KC_SCREEN_H, foreground_buffer);
            draw_line(u1.x, u1.y, u2.x, u2.y, 255);
            draw_line(d1.x, d1.y, d2.x, d2.y, 255);

            draw_set_buffer(KC_SCREEN_W, KC_SCREEN_H, background_buffer);
            draw_triangle(u1.x, u1.y, u2.x, u2.y, d1.x, d1.y, 0);
            draw_triangle(d1.x, d1.y, d2.x, d2.y, u2.x, u2.y, 0);
        }

        memset(pocketsprite_buffer, 0, sizeof(unsigned short) * BUFFER_SIZE);
        blit_buffer(pocketsprite_buffer, background_buffer, bg_palette);
        blit_buffer(pocketsprite_buffer, foreground_buffer, fg_palette);
        kchal_send_fb(pocketsprite_buffer);
    }
}