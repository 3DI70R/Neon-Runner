#include "CSpriteDrawable.hpp"
#include "Utils.hpp"

CSpriteDrawable::CSpriteDrawable(byte width, byte height, pixel_attr* graphics, color* palette) {
    this->width = width;
    this->height = height;
    this->graphics = graphics;
    this->palette = palette;
}

int CSpriteDrawable::getWidth() {
    return width;
}

int CSpriteDrawable::getHeight() {
    return height;
}

color CSpriteDrawable::getColor(int x, int y) {
    return palette[graphics[get2DArrayOffset(width, x, y)] & paletteIndexMask];
}

pixel_attr CSpriteDrawable::getAttr(int x, int y) {
    return graphics[get2DArrayOffset(width, x, y)] & attributeMask;
}