#include "CCameraTransform.hpp"

CCameraTransform::CCameraTransform() {
    setScale(1.f);
    setTranslation(Vector2(0, 0));
    setRotation(0);
}

void CCameraTransform::setTranslation(Vector2 position) {
    this->translation = position;
    this->totalTranslation = position + halfImage;
}

void CCameraTransform::setRotation(float radRotation) {
    this->radRotation = radRotation;
}

void CCameraTransform::setScale(float scale) {
    this->scale = scale;
    this->totalScale = scale;
}

Vector2 CCameraTransform::apply(Vector2 point, float z) {
    Vector2 r(point);
    r.sub(totalTranslation);
    r.scaleBy(z * totalScale);
    r.rotateBy(radRotation);
    r.add(halfImage);
    return r;
}