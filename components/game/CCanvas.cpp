#include "CCanvas.hpp"
#include <cstring>
#include <cstdlib>
#include <cmath>

#define INLINECOORDSORT(x0, y0, x1, y1) if(y0 > y1) { int xT = x1; int yT = y1; x1 = x0; y1 = y0; x0 = xT; y0 = yT; }

pcolor defaultFillPattern[] = 
{
    128, 0, 0, 0, 128, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 128, 0, 0, 0, 128, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    128, 0, 0, 0, 128, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 128, 0, 0, 0, 128, 0, 
    0, 0, 0, 0, 0, 0, 0, 0
};

CCanvas::CCanvas(int width, int height, pcolor* layers[3]) {
    this->width = width;
    this->height = height;
    this->layers = layers;
    setLayer(LAYER_BG);
}

void CCanvas::setLayer(int layer) {
    this->buffer = layers[layer];
}

void CCanvas::drawPixel(int x, int y, pcolor color) {
    if(x >= 0 && x < width && y >= 0 && y < height) {
        writePixel(x, y, color);
    }
}

void CCanvas::drawLine(int xFrom, int yFrom, int xTo, int yTo, pcolor color) {
    drawLinePattern(xFrom, yFrom, xTo, yTo, &color, 1, 0, true);
}

int CCanvas::drawLinePattern(int xFrom, int yFrom, int xTo, int yTo, 
                             pcolor* patternColor, int patternSize, int patternOffset, bool repeat)
{
    int dx = abs (xTo - xFrom);
    int sx = xFrom < xTo ? 1 : -1;
    int dy = -abs (yTo - yFrom);
    int sy = yFrom < yTo ? 1 : -1; 
    int err = dx + dy, e2;
    int patternIndex = patternOffset;
 
    while(1) 
    {
        if(patternIndex >= patternSize) 
        {
            if(repeat) 
            {
                patternIndex = 0;
            }
            else 
            {
                break;
            }
        }

        int actualIndex = patternIndex++;

        if(actualIndex < 0) {
            actualIndex = 0;
        }

        drawPixel(xFrom, yFrom, patternColor[actualIndex]);

        if (xFrom == xTo && yFrom == yTo) 
        {
            break;
        }

        e2 = 2 * err;

        if (e2 >= dy) 
        {
            err += dy; 
            xFrom += sx; 
        }

        if (e2 <= dx)
        { 
            err += dx; 
            yFrom += sy; 
        }
    }

    return patternIndex;
}

void CCanvas::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, pcolor color) {
    
    INLINECOORDSORT(x0, y0, x1, y1)
    INLINECOORDSORT(x1, y1, x2, y2)
    INLINECOORDSORT(x0, y0, x1, y1)

    if (y1 == y2)
    {
        fillBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    }
    else if (y0 == y1)
    {
        fillTopTriangle(x0, y0, x1, y1, x2, y2, color);
    } 
    else
    {
        int x3 = (int) (x0 + ((float)(y1 - y0) / (float)(y2 - y0)) * (x2 - x0));
        fillBottomTriangle(x0, y0, x1, y1, x3, y1, color);
        fillTopTriangle(x1, y1, x3, y1, x2, y2, color);
    }
}

void CCanvas::fill(pcolor color) {
    memset(buffer, color, sizeof(pcolor) * width * height);
}

void CCanvas::fillPattern(pcolor* pattern, int patternWidth, int patternHeight, int xOffset, int yOffset) {
    int line = yOffset;
    pcolor* targetBuffer = buffer;

    // TODO: xOffset
    // TODO: This function will fail if pattern width % width != 0

    for(int y = 0; y < height; y++) 
    {
        pcolor* pattern_line = &pattern[line * patternWidth];

        for(int x = 0; x < width; x += patternWidth) 
        {
            memcpy(targetBuffer, pattern_line, patternWidth * sizeof(pcolor));
            targetBuffer += patternWidth;
        }

        line++;

        if(line >= patternHeight)
        {
            line = 0;
        }
    }
}

void CCanvas::fillBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, pcolor color)
{
    float invslope1 = (float) (x1 - x0) / (float) (y1 - y0);
    float invslope2 = (float) (x2 - x0) / (float) (y2 - y0);

    float curx1 = x0;
    float curx2 = x0;

    // TODO: clip
    // TODO: draw with memset?

    for (int scanlineY = y0; scanlineY <= y1; scanlineY++)
    {
        drawLine((int) curx1, scanlineY, (int) curx2, scanlineY, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void CCanvas::fillTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, pcolor color)
{
    float invslope1 = (float) (x2 - x0) / (float) (y2 - y0);
    float invslope2 = (float) (x2 - x1) / (float) (y2 - y1);

    float curx1 = x2;
    float curx2 = x2;

    // TODO: clip
    // TODO: draw with memset?

    for (int scanlineY = y2; scanlineY > y0; scanlineY--)
    {
        drawLine((int) curx1, scanlineY, (int) curx2, scanlineY, color);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}