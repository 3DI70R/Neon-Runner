#include "CTransformer.hpp"
#include "GameMath.hpp"

CTransformer::CTransformer(CCameraTransform* camera) {
    this->camera = camera;
}

void CTransformer::pushTransform(Transform transform) {
    stack.push(current);
    current.position = apply(transform.position, 1);
    current.angle = angleWrap(current.angle + transform.angle);
    current.scale *= transform.scale;
    isIdentity = false;
}

void CTransformer::popTransform() {
    current = stack.top();
    stack.pop();

    if(stack.empty()) {
        isIdentity = true;
    }
}

Vector2 CTransformer::apply(float x, float y, float z) {
    Vector2 v(x, y);

    if(!isIdentity) {
        v.rotateBy(current.angle);
        v.scaleBy(current.scale);
        v.add(current.position);
    }
    
    return camera->apply(v, z);
}