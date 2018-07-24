#include "CCanvas.hpp"
#include <cstring>
#include <algorithm>

using namespace std;

CCanvas::CCanvas(int width, int height, color* colorBuffer, pixel_attr* attrs) {
    this->width = width;
    this->height = height;
    this->colors = colorBuffer;
    this->attrs = attrs;
}

void CCanvas::draw(int x, int y, CDrawable* drawable, pixel_attr attrMask) {

    int xStart = -min(0, x);
    int yStart = -min(0, y);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    int xEnd = min(drawable->getWidth(), this->width - x);
    int yEnd = min(drawable->getHeight(), this->height - y);

    if(xStart >= xEnd || yStart >= yEnd) {
        return;
    }

    int drawWidth = xEnd - xStart;
    int drawHeight = yEnd - yStart;

    if(x < 0) {
        x = 0;
    }

    if(y < 0) {
        y = 0;
    }

    for(int yDraw = drawHeight - 1; yDraw >= 0; yDraw--) {
        for(int xDraw = drawWidth - 1; xDraw >= 0; xDraw--) {

            int xFrom = xStart + xDraw;
            int yFrom = yStart + yDraw;
            int xTo = x + xDraw;
            int yTo = y + yDraw;

            pixel_attr attr = drawable->getAttr(xFrom, yFrom) & attrMask;
            writeAttr(xTo, yTo, attr);

            if(attr & ATTR_TRANSPARENT) {
                continue;
            }

            writePixel(xTo, yTo, drawable->getColor(xFrom, yFrom));
        }
    }
}

void CCanvas::clear() {
    memset(colors, 0, sizeof(color) * this->width * this->height);
    memset(attrs, 0, sizeof(pixel_attr) * this->width * this->height);
}