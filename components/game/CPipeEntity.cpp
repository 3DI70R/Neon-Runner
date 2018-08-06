#include "CPipeEntity.hpp"

void CPipeEntity::onDraw(CCanvas &canvas, CTransform &transform) {
    
    canvas.setLayer(LAYER_FG);

    for(int i = 1; i < BEZIER_TESSELATION_COUNT; i += 2) 
    {
        Vector2 u = topPoints[i];
        Vector2 d = bottomPoints[i];

        Vector2 t1 = transform.apply(u, 1);
        Vector2 t2 = transform.apply(Vector2::lerp(u, d, 0.2f), 0.9f);
        Vector2 t3 = transform.apply(Vector2::lerp(u, d, 0.4f), 0.85f);
        Vector2 t4 = transform.apply(Vector2::lerp(u, d, 0.6f), 0.85f);
        Vector2 t5 = transform.apply(Vector2::lerp(u, d, 0.8f), 0.9f);
        Vector2 t6 = transform.apply(d, 1);

        canvas.drawLine(t1.x, t1.y, t2.x, t2.y, 80);
        canvas.drawLine(t2.x, t2.y, t3.x, t3.y, 60);
        canvas.drawLine(t3.x, t3.y, t4.x, t4.y, 40);
        canvas.drawLine(t4.x, t4.y, t5.x, t5.y, 60);
        canvas.drawLine(t5.x, t5.y, t6.x, t6.y, 80);
    }

    for(int i = 1; i < BEZIER_TESSELATION_COUNT; i++) 
    {
        Vector2 u1 = transform.apply(topPoints[i - 1], 1);
        Vector2 u2 = transform.apply(topPoints[i], 1);
        Vector2 d1 = transform.apply(bottomPoints[i - 1], 1);
        Vector2 d2 = transform.apply(bottomPoints[i], 1);

        canvas.setLayer(LAYER_FG);
        canvas.drawLine(u1.x, u1.y, u2.x, u2.y, 255);
        canvas.drawLine(d1.x, d1.y, d2.x, d2.y, 128);

        canvas.setLayer(LAYER_BG);
        canvas.drawTriangle(u1.x, u1.y, u2.x, u2.y, d1.x, d1.y, 0);
        canvas.drawTriangle(d1.x, d1.y, d2.x, d2.y, u2.x, u2.y, 0);
    }
}

void CPipeEntity::fromBezier(CubicBezier &bezier, float startWidth, float endWidth) {
    this->startWidth = startWidth;
    this->endWidth = endWidth;

    for(int i = 0; i < BEZIER_TESSELATION_COUNT; i++) {

        float t = i / (BEZIER_TESSELATION_COUNT - 1.0f);
        float w = ::lerp(startWidth, endWidth, t);
        float angle = bezier.getAngleAt(t);

        Vector2 center = bezier.evaluate(t);
        Vector2 rotation = Vector2::fromAngle(angle - DEGTORAD(90), w);

        this->topPoints[i] = center + rotation;
        this->bottomPoints[i] = center - rotation;
        this->bezierPoints[i] = center;
        this->angles[i] = angle;
    }
}