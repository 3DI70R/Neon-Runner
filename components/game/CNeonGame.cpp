#include "CNeonGame.hpp"
#include "TCubicBezier.hpp"
#include "CPipeEntity.hpp"
#include "string"

CNeonGame::CNeonGame(CHal h) : hal(h) {

    int bufferSize = hal.getScreenWidth() * hal.getScreenHeight();;
    
    this->bgBuffer = new pcolor[bufferSize];
    this->fgBuffer = new pcolor[bufferSize];
    this->objBuffer = new pcolor[bufferSize];

    layers[LAYER_BG] = bgBuffer;
    layers[LAYER_FG] = fgBuffer;
    layers[LAYER_OBJ] = objBuffer;

    this->canvas = new CCanvas(hal.getScreenWidth(), hal.getScreenHeight(), layers);
    this->outBlitter = new COutBufferBlitter(bgBuffer, fgBuffer, objBuffer, &hal);
    this->transform = new CTransform();

    CubicBezier bezier;

    bezier.points[0] = Vector2(0, 48);
    bezier.points[1] = Vector2(32, 48);
    bezier.points[2] = Vector2(68, 17);
    bezier.points[3] = Vector2(68, 0);

    pipe.fromBezier(bezier, 10, 15);
}

CNeonGame::~CNeonGame() {
    delete this->canvas;
    delete this->transform;
    delete this->outBlitter;
    delete[] this->bgBuffer;
    delete[] this->fgBuffer;
    delete[] this->objBuffer;
}

void CNeonGame::render() {
    canvas->setLayer(LAYER_BG);
    canvas->fillPattern(defaultFillPattern, 8, 8, 0, 0);
    canvas->setLayer(LAYER_FG);
    canvas->fill(0);
    canvas->setLayer(LAYER_OBJ);
    canvas->fill(0);

    int keys = hal.getInput();
    if(keys & BTN_DOWN) { position.y++; }
    if(keys & BTN_UP) { position.y--; }
    if(keys & BTN_LEFT) { position.x--; }
    if(keys & BTN_RIGHT) { position.x++; }
    if(keys & BTN_A) { scale += 0.01f; }
    if(keys & BTN_B) { scale -= 0.01f; }
    if(keys & BTN_START) { angle += 0.01f; }
    if(keys & BTN_SELECT) { angle -= 0.01f; }

    transform->setTranslation(position);
    transform->setRotation(angle);
    transform->setScale(scale);

    pipe.onDraw(*canvas, *transform);

    outBlitter->blit();
}

bool CNeonGame::tick(float deltaTime) {
    return true;
}

// C wrapper functions

neon_state* neon_init(neon_hal params)
{
    return (neon_state*) new CNeonGame(CHal(params));
}

int neon_tick(neon_state* state, float delta_time) 
{
    if(state == nullptr) {
        return 0;
    }

    return ((CNeonGame*) state)->tick(delta_time) ? 1 : 0;
}

void neon_render(neon_state* state) 
{
    if(state == nullptr) {
        return;
    }

    ((CNeonGame*) state)->render();
}

void neon_destroy(neon_state* state) 
{
    if(state == nullptr) {
        return;
    }

    delete ((CNeonGame*) state);
}