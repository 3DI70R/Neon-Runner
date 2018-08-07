#pragma once
#include "Types.hpp"
#include "TVector2.hpp"

struct Transform {
    Vector2 position;
    float angle;
    float scale = 1.0f;
};