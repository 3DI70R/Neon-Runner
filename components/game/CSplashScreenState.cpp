#include "CSplashScreenState.hpp"

void CSplashScreenState::onTick(float deltaTime) {
    patternPosition -= 2;
}

void CSplashScreenState::onRender(CCanvas *canvas, COutBufferBlitter *blitter) {

    canvas->setLayer(LAYER_BG);
    canvas->fill(0);
    canvas->setLayer(LAYER_FG);
    canvas->fill(0);
    canvas->setLayer(LAYER_OBJ);
    canvas->fill(0);

    canvas->setLayer(LAYER_FG);

    int position = patternPosition;

    // N
    position = canvas->drawLinePattern(8, 46, 16, 14, fillPattern, 8, position, false);
    position = canvas->drawLinePattern(16, 14, 21, 35, fillPattern, 8, position, false);
    position = canvas->drawLinePattern(21, 35, 26, 14, fillPattern, 8, position, false);

    // E
    position = canvas->drawLinePattern(31, 14, 26, 35, fillPattern, 8, position, false);
    canvas->drawLinePattern(31, 14, 39, 14, fillPattern, 8, position, false);
    canvas->drawLinePattern(28, 24, 35, 24, fillPattern, 8, position, false);
    canvas->drawLinePattern(26, 35, 34, 35, fillPattern, 8, position, false);

    // O
    position = canvas->drawLinePattern(44, 14, 53, 14, fillPattern, 8, position, false);
    position = canvas->drawLinePattern(39, 35, 48, 35, fillPattern, 8, position, false);
    position = canvas->drawLinePattern(44, 14, 39, 35, fillPattern, 8, position, false);
    position = canvas->drawLinePattern(53, 14, 48, 35, fillPattern, 8, position, false);

    // N
    position = canvas->drawLinePattern(53, 35, 58, 14, fillPattern, 8, position, false);
    position = canvas->drawLinePattern(58, 14, 63, 35, fillPattern, 8, position, false);
    position = canvas->drawLinePattern(63, 35, 71, 3, fillPattern, 8, position, false);
}