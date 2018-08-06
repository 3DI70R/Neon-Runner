#pragma once
#include "CCanvas.hpp"
#include "CTransform.hpp"

class CEntity {
    public:
        virtual void onDraw(CCanvas &canvas, CTransform &transform) = 0;
};