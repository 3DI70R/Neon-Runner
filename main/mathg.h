#ifndef MATHG_H
#define MATHG_H
#include "types.h"

inline float clamp01(float v) 
{
    return v > 1 ? 1 : v < 0 ? 0 : v;
}

inline float lerp(float src, float dst, float t) {
    return src + (dst - src) * t;
}

vector2 vector2_lerp(vector2 src, vector2 dst, float t) {
    vector2 r;
    r.x = lerp(src.x, dst.x, t);
    r.y = lerp(src.y, dst.y, t);
    return r;
}

float vector2_angle(vector2 from, vector2 to) {
    return 0; // TODO
}

vector2 bezier_evaluate(vector2* points, float t) {
    t = clamp01(t);
    vector2 a1 = vector2_lerp(points[0], points[1], t);
    vector2 a2 = vector2_lerp(points[1], points[2], t);
    vector2 a3 = vector2_lerp(points[2], points[3], t);
    vector2 b1 = vector2_lerp(a1, a2, t);
    vector2 b2 = vector2_lerp(a2, a3, t);
    return vector2_lerp(b1, b2, t);
}

void bezier_rasterize(vector2* points, segment* segments, int segment_count) {
    for(int i = 0; i < segment_count; i++) {
        float t = i / (segment_count - 1);
        float tl = clamp01(t - 0.01f);
        float tr = clamp01(t + 0.01f);

        vector2 lpoint = bezier_evaluate(points, tl);
        vector2 point = bezier_evaluate(points, t);
        vector2 rpoint = bezier_evaluate(points, tr);

        segment s;
        
        s.angle = vector2_angle(lpoint, rpoint);
        s.position = point;
        s.width = 1;

        segments[i] = s;
    }
}

#endif