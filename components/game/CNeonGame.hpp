#pragma once
#include "neon.h"
#include "Types.hpp"
#include "CCanvas.hpp"
#include "COutBufferBlitter.hpp"
#include "CPipeEntity.hpp"
#include "CGlitchEntity.hpp"
#include "TGameStates.hpp"
#include "CGameStateMachine.hpp"
#include "CHal.hpp"

class CNeonGame {
    
    CHal hal;
    
    pcolor* bgBuffer;
    pcolor* fgBuffer;
    pcolor* objBuffer;
    pcolor* layers[3];
    CCanvas* canvas;
    COutBufferBlitter* outBlitter;

    GameStates states;
    CGameStateMachine* stateMachine;
    CGlitchEntity glitch;

    public:
        CNeonGame(CHal hal);
        ~CNeonGame();

        bool tick(float deltaTime);
        void render();
};