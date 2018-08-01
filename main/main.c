#include "8bkc-hal.h"
#include "8bkc-ugui.h"
#include "ugui.h"
#include "types.h"
#include "mathg.h"
#include "draw.h"

#define BUFFER_SIZE KC_SCREEN_W * KC_SCREEN_H

byte background_buffer[BUFFER_SIZE];
byte foreground_buffer[BUFFER_SIZE];
byte objects_buffer[BUFFER_SIZE];
unsigned short pocketsprite_buffer[BUFFER_SIZE];

void convert_buffer(unsigned short* pkspr, byte* game, int size) 
{
    color ul = { .r = 255, .g = 0, .b = 0 };
    color ur = { .r = 0, .g = 255,  .b = 0 };
    color dl = { .r = 0,  .g = 0, .b = 255 };
    color dr = { .r = 255, .g = 255,   .b = 0 };

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
    segment s[16];
    byte pattern[] = { 24, 24, 24, 0, 0, 0, 0, 0, 0 };

    while(true) 
    {
        int keys = kchal_get_keys();
        if(keys & KC_BTN_DOWN) { y_off++; }
        if(keys & KC_BTN_UP) { y_off--; }
        if(keys & KC_BTN_LEFT) { x_off--; }
        if(keys & KC_BTN_RIGHT) { x_off++; }

        bezier b = 
        { 
            { .x = 0.0f, .y = 48.0f },
            { .x = 32.0f, .y = 48.0f  },
            { .x = 68.0f + x_off, .y = 17.0f + y_off },
            { .x = 68.0f, .y = 0.0f }
        };

        bezier_rasterize(b, s, 10, 15, 16);
        int offset = 0;

        for(int i = 1; i < 16; i++) 
        {
            segment s1 = s[i - 1];
            segment s2 = s[i];

            vector2 u1 = vector2_add(s1.position, vector2_from_angle(s1.angle, s1.width));
            vector2 u2 = vector2_add(s2.position, vector2_from_angle(s2.angle, s2.width));
            vector2 d1 = vector2_add(s1.position, vector2_from_angle(s1.angle + DEGTORAD(180), s1.width));
            vector2 d2 = vector2_add(s2.position, vector2_from_angle(s2.angle + DEGTORAD(180), s2.width));

            offset = draw_line_pattern((int) s1.position.x, (int) s1.position.y, 
                                       (int) s2.position.x, (int) s2.position.y, 
                                       pattern, 9, offset, true);

            draw_line((int) u1.x, (int) u1.y, (int) u2.x, (int) u2.y, 255);
            draw_line((int) d1.x, (int) d1.y, (int) d2.x, (int) d2.y, 255);
        }

        convert_buffer(pocketsprite_buffer, background_buffer, BUFFER_SIZE);
        kchal_send_fb(pocketsprite_buffer);
        draw_clear(0);
    }
}