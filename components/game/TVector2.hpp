#pragma once
#include "GameMath.hpp"

struct Vector2 {

    float x;
    float y;

    Vector2() { }
    Vector2(const Vector2 &copy) {
        x = copy.x;
        y = copy.y;
    }
    Vector2(float x, float y);

    float angleTo(const Vector2 &otherVector);
    void asLerp(const Vector2 &v1, const Vector2 &v2, float t);
    void rotateBy(float radAngle);
    void scaleBy(float scale);
    void add(const Vector2 &v);
    void sub(const Vector2 &v);
    
    inline void lerpTo(const Vector2 &v, float t) {
        asLerp(*this, v, t);
    }

    static Vector2 lerp(const Vector2 &v1, const Vector2 &v2, float t) {
        Vector2 v;
        v.asLerp(v1, v2, t);
        return v;
    }

    static Vector2 fromAngle(float angle, float distance = 1.0f) {
        Vector2 v(cos(angle) * distance, sin(angle) * distance);
        return v;
    }

    friend Vector2 operator+(const Vector2 &l, const Vector2 &r) {
        Vector2 v(l);
        v.add(r);
        return v;
    }

    friend Vector2 operator-(const Vector2 &l, const Vector2 &r) {
        Vector2 v(l);
        v.sub(r);
        return v;
    }
};