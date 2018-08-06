#pragma once
#include "Types.hpp"

struct RGBColor {
    
    byte r;
    byte g;
    byte b;

    RGBColor() { }
    RGBColor(byte r, byte g, byte b);

    void asLerp(const RGBColor &c1, const RGBColor &c2, float t);

    inline void lerpTo(const RGBColor &c, float t) {
        asLerp(*this, c, t);
    }

    inline void scale(float value) {

        if(value == 1) {
            return;
        }

        r *= value;
        g *= value;
        b *= value;
    }

    static RGBColor lerp(const RGBColor &c1, const RGBColor &c2, float t) {
        RGBColor c;
        c.asLerp(c1, c2, t);
        return c;
    }
};