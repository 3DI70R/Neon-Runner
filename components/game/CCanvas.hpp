#pragma once
#include "Types.hpp"

#define LAYER_BG 0
#define LAYER_FG 1
#define LAYER_OBJ 2

extern pcolor defaultFillPattern[];

class CCanvas {

    int width;
    int height;
    pcolor* buffer;
    pcolor** layers;

    public:

        CCanvas(int width, int height, pcolor** layers);

        inline int getWidth() {
            return width;
        }

        inline int getHeight() {
            return height;
        }

        void setLayer(int layer);
        void drawPixel(int x, int y, pcolor color);
        void drawLine(int xFrom, int yFrom, int xTo, int yTo, pcolor color);
        void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, pcolor color);

        int drawLinePattern(int xFrom, int yFrom, int xTo, int yTo, 
                            pcolor* patternColor, int patternSize, int patternOffset, bool repeat);

        void fill(pcolor color);
        void fillPattern(pcolor* pattern, int patternWidth, int patternHeight, int xOffset, int yOffset);

    private:

        inline void writePixel(int x, int y, pcolor pixel) {
            buffer[x + y * width] = pixel;
        }

        void fillBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, pcolor color);
        void fillTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, pcolor color);
};