#include "TRGBColor.hpp"
#include "GameMath.hpp"

RGBColor::RGBColor(byte r, byte g, byte b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void RGBColor::asLerp(const RGBColor &c1, const RGBColor &c2, float t) {
    r = ::lerp(c1.r, c2.r, t);
    g = ::lerp(c1.g, c2.g, t);
    b = ::lerp(c1.b, c2.b, t);
}