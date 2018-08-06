#pragma once
#include "math.h"

#define PI2 (M_PI + M_PI)
#define DEGTORAD(x) ((x) * M_PI / 180.0)

template <typename T> inline T clamp(T value, T min, T max) {
    return value < min ? min : value > max ? max : value;
}

template <typename T> inline T clamp01(T value) {
    return value < 0 ? 0 : value > 1 ? 1 : value;
}

inline float angleWrap(float radAngle)
{
    return radAngle - PI2 * floor(radAngle / PI2);
}

template <typename T> inline T lerp(T src, T dst, float t) {
    return src + (dst - src) * t;
}

inline float slerp(float srcRad, float dstRad, float t)
{
    return lerp(angleWrap(srcRad), angleWrap(dstRad), t);
}