#pragma once
#include "neon.h"
#include "Types.hpp"

class CHal {

    neon_hal hal;

    public:

        CHal(neon_hal hal) {
            this->hal = hal;
        }

        inline int getInput() {
            return hal.input_get();
        }

        inline void clearScreen() {
            hal.screen_clear();
        }

        inline void drawPixel(int x, int y, byte r, byte g, byte b) {
            hal.screen_draw_pixel(x, y, r, g, b);
        }

        inline int getScreenWidth() {
            return hal.screen_width;
        }

        inline int getScreenHeight() {
            return hal.screen_height;
        }
};