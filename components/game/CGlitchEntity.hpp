#pragma once
#include "CEntity.hpp"
#include "Types.hpp"
#include "GameMath.hpp"
#include <random>

#define GLITCH_PARTICLE_COUNT 8

class CGlitchEntity : public CEntity {

    struct Particle {
        Vector2 position;
        Vector2 size;
        int color;
    };

    Particle particles[GLITCH_PARTICLE_COUNT];

    public:
        virtual void onTick(float deltaTime);
        virtual void onDraw(CCanvas &canvas, CTransformer &transformer);
};