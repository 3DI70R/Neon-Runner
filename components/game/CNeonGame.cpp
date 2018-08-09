#include "CNeonGame.hpp"
#include "TCubicBezier.hpp"
#include "CPipeEntity.hpp"
#include "CTransformer.hpp"
#include "CCameraTransform.hpp"
#include "CGlitchEntity.hpp"
#include "string"

CNeonGame::CNeonGame(CHal h) : hal(h) {

    int bufferSize = hal.getScreenWidth() * hal.getScreenHeight();
    
    this->bgBuffer = new pcolor[bufferSize];
    this->fgBuffer = new pcolor[bufferSize];
    this->objBuffer = new pcolor[bufferSize];

    layers[LAYER_BG] = bgBuffer;
    layers[LAYER_FG] = fgBuffer;
    layers[LAYER_OBJ] = objBuffer;

    this->canvas = new CCanvas(hal.getScreenWidth(), hal.getScreenHeight(), layers);
    this->outBlitter = new COutBufferBlitter(bgBuffer, fgBuffer, objBuffer, &hal);
    this->stateMachine = new CGameStateMachine(&hal, &states);
}

CNeonGame::~CNeonGame() {
    delete this->canvas;
    delete this->outBlitter;
    delete this->stateMachine;
    delete[] this->bgBuffer;
    delete[] this->fgBuffer;
    delete[] this->objBuffer;
}

bool CNeonGame::tick(float deltaTime) {
    return stateMachine->tick(deltaTime);
    /*glitch.onTick(deltaTime);

    int keys = hal.getInput();
    if(keys & BTN_DOWN) { glitch.transform.position.y++; }
    if(keys & BTN_UP) { glitch.transform.position.y--; }
    if(keys & BTN_LEFT) { glitch.transform.position.x--; }
    if(keys & BTN_RIGHT) { glitch.transform.position.x++; }
    if(keys & BTN_A) { glitch.transform.scale += 0.01f; }
    if(keys & BTN_B) { glitch.transform.scale -= 0.01f; }
    if(keys & BTN_START) { glitch.transform.angle += 0.01f; }
    if(keys & BTN_SELECT) { glitch.transform.angle -= 0.01f; }*/
}

void CNeonGame::render() {
    stateMachine->render(canvas, outBlitter);

    /*canvas->setLayer(LAYER_BG);
    canvas->fillPattern(defaultFillPattern, 8, 8, 0, 0);
    canvas->setLayer(LAYER_FG);
    canvas->fill(0);
    canvas->setLayer(LAYER_OBJ);
    canvas->fill(0);

    CCameraTransform camera;
    CTransformer transformer(&camera);

    CPipeEntity pipe;
    CubicBezier bezier(
        Vector2(0, 48),
        Vector2(32, 48),
        Vector2(68, 17),
        Vector2(68, 0)
    );

    pipe.fromBezier(bezier, 10, 15);
    pipe.onDraw(*canvas, transformer);

    transformer.pushTransform(glitch.transform);
    glitch.onDraw(*canvas, transformer);
    transformer.popTransform();

    outBlitter->blit();*/
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