#include "CTween.hpp"

CTweenTemplate
void CTween<T, I>::tick(float deltaTime) {
    if(animating) {
        animPosition = clamp01(animPosition + animSpeed * deltaTime);
        
        if(this->easing != nullptr) {
            current = interpolator.lerp(from, to, easing(animPosition));
        } else {
            current = interpolator.lerp(from, to, animPosition);
        }

        if(animPosition == 1) {
            animating = false;
        }
    }
}

CTweenTemplate
void CTween<T, I>::animate(T from, T to) {
    this->from = from;
    this->to = to;
    this->animating = true;
    this->animPosition = 0.0f;
}