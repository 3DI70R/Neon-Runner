#include "TCubicBezier.hpp"

Vector2 CubicBezier::evaluate(float t) {
    t = clamp01(t);
    Vector2 a1 = Vector2::lerp(points[0], points[1], t);
    Vector2 a2 = Vector2::lerp(points[1], points[2], t);
    Vector2 a3 = Vector2::lerp(points[2], points[3], t);
    Vector2 b1 = Vector2::lerp(a1, a2, t);
    Vector2 b2 = Vector2::lerp(a2, a3, t);
    return Vector2::lerp(b1, b2, t);
}

float CubicBezier::getAngleAt(float t) {
    Vector2 lpoint = evaluate(clamp01(t - 0.01f));
    Vector2 rpoint = evaluate(clamp01(t + 0.01f));
    return lpoint.angleTo(rpoint);
}