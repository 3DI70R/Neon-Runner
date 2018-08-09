#pragma once
#include "GameMath.hpp"
#include "TRGBColor.hpp"
#include "TVector2.hpp"

#define CTweenTemplate template<typename T, typename I>

typedef float (*easing)(float);

CTweenTemplate 
class CTween {

    I interpolator;
    T current;
    T from;
    T to;
    float animPosition;
    float animSpeed;
    bool animating;
    easing easingFunc;

    public:

        inline CTween(float duration, easing easingFunc) {
            setDuration(duration);
            setEasing(easingFunc);
        }

        void animate(T from, T to);
        void tick(float deltaTime);

        inline void setEasing(easing easingFunc) {
            this->easingFunc = easingFunc;
        }

        inline void setDuration(float duration) {
            this->animSpeed = 1.0f / duration;
        }

        inline void finish() {
            animating = false;
            current = to;
        }

        inline void cancel() {
            animating = false;
            current = from;
        }

        inline void animate(T value) {
            animate(get(), value);
        }

        inline bool isAnimating() {
            return animating;
        }

        inline void set(T value) {
            current = value;
        }

        inline T get() {
            return current;
        }
};

struct IntInterpolator {
    inline int lerp(int from, int to, float t) {
        return ::lerp(from, to, t);
    }
};

struct FloatInterpolator {
    inline float lerp(float from, float to, float t) {
        return ::lerp(from, to, t);
    }
};

struct Vector2Interpolator {
    inline Vector2 lerp(Vector2 from, Vector2 to, float t) {
        return Vector2::lerp(from, to, t);
    }
};

struct RGBInterpolator {
    inline RGBColor lerp(RGBColor from, RGBColor to, float t) {
        return RGBColor::lerp(from, to, t);
    }
};

typedef CTween<int, easing> CIntTween;
typedef CTween<float, FloatInterpolator> CFloatTween;
typedef CTween<Vector2, Vector2Interpolator> CVector2Tween;
typedef CTween<RGBColor, RGBInterpolator> CRGBTween;