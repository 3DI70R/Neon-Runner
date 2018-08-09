#pragma once
#include "CGameState.hpp"

class CSplashScreenState : public CGameState {

    pcolor fillPattern[8] = { 255, 192, 164, 128, 96, 64, 32, 0 };
    int patternPosition = 0;

    public:
        virtual void onTick(float deltaTime);
        virtual void onRender(CCanvas *canvas, COutBufferBlitter *blitter);
};