#pragma once
#include "CSplashScreenState.hpp"

struct GameStates {
    CSplashScreenState splash;

    CGameState* getInitialState() {
        return &splash;
    }
};