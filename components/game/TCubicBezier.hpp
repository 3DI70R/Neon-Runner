#pragma once
#include "TVector2.hpp"

struct CubicBezier {

    Vector2 points[4];

    Vector2 evaluate(float t);
    float getAngleAt(float t);
};