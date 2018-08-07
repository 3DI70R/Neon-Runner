#include "CGlitchEntity.hpp"

void CGlitchEntity::onTick(float deltaTime) {
    int particle = randomRange(1, GLITCH_PARTICLE_COUNT - 1);
    particles[particle].position = Vector2(randomRange(-10, 10), randomRange(-10, 10));
    particles[particle].size = Vector2(randomRange(1, 4), randomRange(1, 10));
    particles[particle].color = randomRange(64, 256);
}

void CGlitchEntity::onDraw(CCanvas &canvas, CTransformer &transformer) {
    canvas.setLayer(LAYER_FG);

    for(int i = 0; i < GLITCH_PARTICLE_COUNT; i++) {

        Vector2 s = particles[i].size;
        Vector2 v1 = transformer.apply(particles[i].position + s, 1);
        Vector2 v2 = transformer.apply(particles[i].position + Vector2(-s.x, s.y), 1);
        Vector2 v3 = transformer.apply(particles[i].position + Vector2(s.x, -s.y), 1);
        Vector2 v4 = transformer.apply(particles[i].position - s, 1);

        canvas.drawTriangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, particles[i].color);
        canvas.drawTriangle(v2.x, v2.y, v3.x, v3.y, v4.x, v4.y, particles[i].color);
    }
}