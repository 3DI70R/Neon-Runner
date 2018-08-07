#pragma once
#include "TVector2.hpp"

struct CubicBezier {

    Vector2 points[4];

    CubicBezier() {}
    
    inline CubicBezier(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4) {
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;
    }

    Vector2 evaluate(float t);
    float getAngleAt(float t);
};