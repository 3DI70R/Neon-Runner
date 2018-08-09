#pragma once
#include "TGameStates.hpp"
#include "CGameState.hpp"
#include "CHal.hpp"

class CGameStateMachine {
    
    CHal* hal;
    GameStates* allStates;
    CGameState* previousState = nullptr;
    CGameState* currentState = nullptr;
    CGameState* nextState = nullptr;

    public:

        CGameStateMachine(CHal* hal, GameStates* states);

        GameStates* getStates();

        bool tick(float deltaTime);
        void render(CCanvas *canvas, COutBufferBlitter *blitter);

        void changeState(CGameState *state);
};