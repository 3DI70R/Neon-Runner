#include "CBufferBlurEffect.hpp"
#include "Utils.hpp"

void CBufferBlurEffect::blur(color* colors, int width, int height, int radius) {
    processHorizontal(colors, width, height, radius);
    processVertical(colors, width, height, radius);
}

void CBufferBlurEffect::processHorizontal(color* colors, int width, int height, int radius) {
    for(int y = 0; y < height; y++) {
        clearAccumulator();
        for(int x = 0; x < width; x++) {
            if(x + radius < width) {
                pushAccumulator(colors[get2DArrayOffset(width, x + radius, y)]);
            }

            if(x - radius > 0) {
                popAccumulator(colors[get2DArrayOffset(width, x - radius, y)]);
            }

            colors[get2DArrayOffset(width, x + radius, y)] = getAccumulatorColor();
        }
    }
}

void CBufferBlurEffect::processVertical(color* colors, int width, int height, int radius) {
    for(int x = 0; x < width; x++) {
        clearAccumulator();
        for(int y = 0; y < height; y++) {
            if(y + radius < height) {
                pushAccumulator(colors[get2DArrayOffset(width, x, y + radius)]);
            }

            if(y - radius > 0) {
                popAccumulator(colors[get2DArrayOffset(width, x, y - radius)]);
            }

            colors[get2DArrayOffset(width, x + radius, y)] = getAccumulatorColor();
        }
    }
}

void CBufferBlurEffect::clearAccumulator() {
    rAcc = 0;
    gAcc = 0;
    bAcc = 0;
    accumulatorSize = 0;
}

void CBufferBlurEffect::pushAccumulator(color c) {
    rAcc += (c & 0xF800) >> 11;
    gAcc += (c & 0x7E0) >> 5;
    bAcc += (c & 0x1F);
    accumulatorSize++;
}

void CBufferBlurEffect::popAccumulator(color c) {
    rAcc -= (c & 0xF800) >> 11;
    gAcc -= (c & 0x7E0) >> 5;
    bAcc -= (c & 0x1F);
    accumulatorSize--;
}

color CBufferBlurEffect::getAccumulatorColor() {
    return ((rAcc / accumulatorSize) << 11) 
         | ((gAcc / accumulatorSize) << 5) 
           | bAcc / accumulatorSize;
}