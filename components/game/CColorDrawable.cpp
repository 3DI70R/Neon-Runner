#include "CColorDrawable.hpp"

CColorDrawable::CColorDrawable(int width, int height, color fillColor, pixel_attr attr = 0) {
    this->width = width;
    this->height = height;
    this->fillColor = fillColor;
    this->attr = attr;
}

int CColorDrawable::getWidth() {
    return width;
}

int CColorDrawable::getHeight() {
    return height;
}

color CColorDrawable::getColor(int x, int y) {
    return fillColor;
}

pixel_attr CColorDrawable::getAttr(int x, int y) {
    return attr;
}