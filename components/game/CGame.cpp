#include "CGame.hpp"
#include  <cstdlib>

void CGame::setImageOutput(imageOutputFunc image) {
    imageOutput = image;
}

void CGame::setSoundOutput(soundOutputFunc sound) {
    soundOutput = sound;
}

void CGame::setControlsInput(controlsInputFunc input) {
    controlsInput = input;
}

void CGame::init() {

}

void CGame::tick() {
    
}

void CGame::deinit() {
    
}