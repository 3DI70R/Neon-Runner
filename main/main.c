#include "8bkc-hal.h"
#include "8bkc-ugui.h"
#include "ugui.h"
#include "types.h"
#include "mathg.h"
#include "draw.h"
#include "transform.h"

#define BUFFER_SIZE KC_SCREEN_W * KC_SCREEN_H

byte background_buffer[BUFFER_SIZE];
byte foreground_buffer[BUFFER_SIZE];
byte objects_buffer[BUFFER_SIZE];
unsigned short pocketsprite_buffer[BUFFER_SIZE];

void convert_buffer(unsigned short* pkspr, byte* game, int size) 
{
    color ul = { .r = 0, .g = 128, .b = 255 };
    color ur = { .r = 0, .g = 0,  .b = 255 };
    color dl = { .r = 255,  .g = 0, .b = 128 };
    color dr = { .r = 255, .g = 0,   .b = 0 };

    for(int y = 0; y < 64; y++) 
    {
        color cl = color_lerp(ul, dl, y / 63.0f);
        color cr = color_lerp(ur, dr, y / 63.0f);

        for(int x = 0; x < 80; x++) 
        {
            byte c = *game;

            if(c != 0) 
            {
                float t = c / 255.0f;
                color rgb = color_lerp(cl, cr, x / 79.0f);
                *pkspr = kchal_fbval_rgb(rgb.r * t, rgb.g * t, rgb.b * t);
            }
            else 
            {
                *pkspr = 0;
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

    int x_off = 0;
    int y_off = 0;
    float depth = 1;
    segment s[16];

    while(true) 
    {
        int keys = kchal_get_keys();
        if(keys & KC_BTN_DOWN) { y_off++; }
        if(keys & KC_BTN_UP) { y_off--; }
        if(keys & KC_BTN_LEFT) { x_off--; }
        if(keys & KC_BTN_RIGHT) { x_off++; }
        if(keys & KC_BTN_A) { depth += 0.01f; }
        if(keys & KC_BTN_B) { depth -= 0.01f; };

        bezier b = 
        { 
            { .x = 0.0f, .y = 48.0f },
            { .x = 32.0f, .y = 48.0f  },
            { .x = 68.0f + x_off, .y = 17.0f + y_off },
            { .x = 68.0f, .y = 0.0f }
        };

        bezier_rasterize(b, s, 10, 15, 16);

        for(int i = 1; i < 8; i++) 
        {
            segment seg = segment_evaluate(s, 16, fmod(i / 7.0f + depth, 1.0f));
            
            vector2 t1 = vector2_add(seg.position, vector2_from_angle(seg.angle + DEGTORAD(90), seg.width));
            vector2 t6 = vector2_add(seg.position, vector2_from_angle(seg.angle - DEGTORAD(90), seg.width));
            vector2 t2 = transform_apply(vector2_lerp(t1, t6, 0.2f), 0.9f);
            vector2 t3 = transform_apply(vector2_lerp(t1, t6, 0.4f), 0.85f);
            vector2 t4 = transform_apply(vector2_lerp(t1, t6, 0.6f), 0.85f);
            vector2 t5 = transform_apply(vector2_lerp(t1, t6, 0.8f), 0.9f);

            draw_line(t1.x, t1.y, t2.x, t2.y, 80);
            draw_line(t2.x, t2.y, t3.x, t3.y, 60);
            draw_line(t3.x, t3.y, t4.x, t4.y, 40);
            draw_line(t4.x, t4.y, t5.x, t5.y, 60);
            draw_line(t5.x, t5.y, t6.x, t6.y, 80);
        }

        for(int i = 1; i < 16; i++) 
        {
            segment s1 = s[i - 1];
            segment s2 = s[i];
            
            vector2 u1 = vector2_add(s1.position, vector2_from_angle(s1.angle + DEGTORAD(90), s1.width));
            vector2 u2 = vector2_add(s2.position, vector2_from_angle(s2.angle + DEGTORAD(90), s2.width));
            vector2 d1 = vector2_add(s1.position, vector2_from_angle(s1.angle - DEGTORAD(90), s1.width));
            vector2 d2 = vector2_add(s2.position, vector2_from_angle(s2.angle - DEGTORAD(90), s2.width));

            draw_line(u1.x, u1.y, u2.x, u2.y, 255);
            draw_line(d1.x, d1.y, d2.x, d2.y, 255);
        }

        convert_buffer(pocketsprite_buffer, background_buffer, BUFFER_SIZE);
        kchal_send_fb(pocketsprite_buffer);
        draw_clear(0);
    }
}