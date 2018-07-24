#include "8bkc-hal.h"
#include "pkspr_game.h"
#include "CGame.hpp"
#include "CCanvas.hpp"
#include "CColorDrawable.hpp"
#include "CSpriteDrawable.hpp"
#include "CBufferBlurEffect.hpp"
#include "Types.hpp"

CGame game;

color colorBuffer[80 * 64];
pixel_attr colorAttrs[80 * 64];

extern const byte spriteAttrs[] asm("_binary_test_attrs_raw_start");
extern const byte spritePalette[] asm("_binary_test_palette_raw_start");

void start_game() 
{
    kchal_init();

    CCanvas canvas(80, 64, colorBuffer, colorAttrs);
    CSpriteDrawable sprite(24, 24, (pixel_attr*) spriteAttrs, (color*) spritePalette);
    CBufferBlurEffect blur;

    int x = 16;
    int y = 16;

    while(true) {
        canvas.clear();
        for(int i = 0; i < 32; i++) {
            for(int j = 0; j < 32; j++) {
                canvas.draw(x + i * 24, y + j * 24, &sprite);
            }
        }

        int keys = kchal_get_keys();

        if(keys & KC_BTN_DOWN) {
            y++;
        }

        if(keys & KC_BTN_UP) {
            y--;
        }

        if(keys & KC_BTN_LEFT) {
            x--;
        }

        if(keys & KC_BTN_RIGHT) {
            x++;
        }

        if(keys & KC_BTN_A) {
            blur.blur(colorBuffer, 80, 64, 2);
        }

        kchal_send_fb(colorBuffer);
    }
}