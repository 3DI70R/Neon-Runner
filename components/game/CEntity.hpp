#pragma once
#include "CCanvas.hpp"
#include "TTransform.hpp"
#include "CTransformer.hpp"

class CEntity {
    
    public:
        Transform transform;

    public:
        virtual void onTick(float deltaTime) { /* noop */ };
        virtual void onDraw(CCanvas &canvas, CTransformer &transformer) = 0;
};