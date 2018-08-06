#pragma once
#include "TVector2.hpp"
#include "GameMath.hpp"

#define REFERENCE_IMAGE_WIDTH 80
#define REFERENCE_IMAGE_HEIGHT 64
#define REFERENCE_HALF_IMAGE_WIDTH (REFERENCE_IMAGE_WIDTH / 2)
#define REFERENCE_HALF_IMAGE_HEIGHT (REFERENCE_IMAGE_HEIGHT / 2)

class CTransform {

    Vector2 halfImage = Vector2(REFERENCE_HALF_IMAGE_WIDTH, REFERENCE_HALF_IMAGE_HEIGHT);
    Vector2 translation;
    Vector2 totalTranslation;
    float radRotation;
    float scale;
    float totalScale;

    public:
        CTransform();

        void setTranslation(Vector2 translation);
        void setRotation(float radRotation);
        void setScale(float scale);

        Vector2 apply(float x, float y, float z);

        inline Vector2 apply(Vector2 v, float z) {
            return apply(v.x, v.y, z);
        }
};