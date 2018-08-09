#include "CGameStateMachine.hpp"

CGameStateMachine::CGameStateMachine(CHal* hal, GameStates* states) {
    this->hal = hal;
    this->allStates = states;
    changeState(allStates->getInitialState());
}

GameStates* CGameStateMachine::getStates() {
    return allStates;
}

void CGameStateMachine::changeState(CGameState *state) {
    nextState = state;
}

bool CGameStateMachine::tick(float deltaTime) {

    if(nextState != nullptr) {
        previousState = currentState;
        currentState = nextState;
        nextState = nullptr;

        if(previousState != nullptr) {
            previousState->onLeave();
        }

        if(currentState != nullptr) {
            currentState->onEnter();
        }
    }

    //transition.tick(deltaTime);

    //if(!transition.isAnimating()) {
        previousState = nullptr;
    //}

    if(currentState != nullptr) {
        currentState->onTick(deltaTime);
    }

    return currentState != nullptr;
}

void CGameStateMachine::render(CCanvas *canvas, COutBufferBlitter *blitter) {

    /*if(previousState != nullptr) {
        previousState->onRender(canvas, blitter);
        blitter->blit();
    }*/

    if(currentState != nullptr) {
        currentState->onRender(canvas, blitter);
        blitter->blit();
    }
}