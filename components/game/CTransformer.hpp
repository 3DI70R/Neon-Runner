#pragma once
#include "TTransform.hpp"
#include "CCameraTransform.hpp"
#include <stack>

class CTransformer {

    std::stack<Transform> stack;
    Transform current;
    CCameraTransform* camera;
    bool isIdentity;

    public:
        CTransformer(CCameraTransform* camera);

        void pushTransform(Transform transform);
        void popTransform();

        Vector2 apply(float x, float y, float z = 1);
        
        inline Vector2 apply(Vector2 xy, float z = 1) {
            return apply(xy.x, xy.y, z);
        }
};