#pragma once
#include "CCanvas.hpp"
#include "COutBufferBlitter.hpp"

class CGameState {

    public:
        virtual void onEnter() { };
        virtual void onLeave() { };

        virtual void onTick(float deltaTime) = 0;
        virtual void onRender(CCanvas *canvas, COutBufferBlitter *blitter) = 0;
};