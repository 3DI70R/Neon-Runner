#include "CTransform.hpp"

CTransform::CTransform() {
    setScale(1.f);
    setTranslation(Vector2(0, 0));
    setRotation(0);
}

void CTransform::setTranslation(Vector2 position) {
    this->translation = position;
    this->totalTranslation = position + halfImage;
}

void CTransform::setRotation(float radRotation) {
    this->radRotation = radRotation;
}

void CTransform::setScale(float scale) {
    this->scale = scale;
    this->totalScale = scale;
}

Vector2 CTransform::apply(float x, float y, float z) {
    Vector2 r(x, y);
    r.sub(totalTranslation);
    r.scaleBy(z * totalScale);
    r.rotateBy(radRotation);
    r.add(halfImage);
    return r;
}