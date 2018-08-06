#include "TVector2.hpp"
#include "cmath"
#include "GameMath.hpp"

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector2::angleTo(const Vector2 &otherVector) {
    return atan2f(otherVector.y - y, otherVector.x - x);
}

void Vector2::rotateBy(float radAngle) {
    float c = cos(radAngle);
    float s = sin(radAngle);
    float xNew = x * c - y * s;
    y = x * s + y * c;
    x = xNew;
}

void Vector2::scaleBy(float scale) {
    x *= scale;
    y *= scale;
}

void Vector2::add(const Vector2 &v) {
    x += v.x;
    y += v.y;
}

void Vector2::sub(const Vector2 &v) {
    x -= v.x;
    y -= v.y;
}

void Vector2::asLerp(const Vector2& v1, const Vector2& v2, float t) {
    x = ::lerp(v1.x, v2.x, t);
    y = ::lerp(v1.y, v2.y, t);
}