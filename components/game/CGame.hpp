#ifndef GAME_H
#define GAME_H
#include "Types.hpp"
#include "CCanvas.hpp"

class CGame {

    imageOutputFunc imageOutput;
    soundOutputFunc soundOutput;
    controlsInputFunc controlsInput;

    public:
        void setImageOutput(imageOutputFunc image);
        void setSoundOutput(soundOutputFunc sound);
        void setControlsInput(controlsInputFunc input);

        void init();
        void tick();
        void deinit();
};

#endif