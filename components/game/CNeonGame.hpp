#pragma once
#include "neon.h"
#include "Types.hpp"
#include "CCanvas.hpp"
#include "CTransform.hpp"
#include "COutBufferBlitter.hpp"
#include "CPipeEntity.hpp"
#include "CHal.hpp"

class CNeonGame {
    
    CHal hal;
    pcolor* bgBuffer;
    pcolor* fgBuffer;
    pcolor* objBuffer;
    pcolor* layers[3];

    CCanvas* canvas;
    CTransform* transform;
    COutBufferBlitter* outBlitter;

    // Test
    Vector2 position;
    float scale = 1.f;
    float angle;
    CPipeEntity pipe;

    public:
        CNeonGame(CHal hal);
        ~CNeonGame();

        bool tick(float deltaTime);
        void render();
};