#ifndef CCANVAS_H
#define CCANVAS_H
#include "Types.hpp"
#include "Utils.hpp"
#include "CDrawable.hpp"

class CCanvas {

    private:
        int width;
        int height;
        color* colors;
        pixel_attr* attrs;

    public:
        CCanvas(int width, int height, color* colorBuffer, pixel_attr* attrs);

        void clear();

        void draw(int x, int y, CDrawable* drawable, pixel_attr attrApplyMask = 0xff);

        inline void writePixel(int x, int y, color pixel) {
            colors[get2DArrayOffset(width, x, y)] = pixel;
        }

        inline void writeAttr(int x, int y, pixel_attr attr) {
            attrs[get2DArrayOffset(width, x, y)] = attr;
        }

    private:
        void drawUnclipped(int x, int y, CDrawable* drawable, pixel_attr attrApplyMask = 0xff);
};

#endif