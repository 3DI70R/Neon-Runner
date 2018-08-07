#pragma once
#include "CEntity.hpp"
#include "TCubicBezier.hpp"
#include "TVector2.hpp"

#define BEZIER_TESSELATION_COUNT 16

class CPipeEntity : public CEntity {

    struct TesselatedLine {
        Vector2 points[BEZIER_TESSELATION_COUNT];
        float angles[BEZIER_TESSELATION_COUNT];
    };

    Vector2 bezierPoints[BEZIER_TESSELATION_COUNT];
    Vector2 topPoints[BEZIER_TESSELATION_COUNT];
    Vector2 bottomPoints[BEZIER_TESSELATION_COUNT];
    float angles[BEZIER_TESSELATION_COUNT];
    float startWidth;
    float endWidth;

    public:
        void onDraw(CCanvas &canvas, CTransformer &transform);

        void fromBezier(CubicBezier &bezier, float startWidth, float endWidth);
};