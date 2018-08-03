#ifndef MATHG_H
#define MATHG_H
#include "types.h"
#include "math.h"
#include "stdlib.h"
#include <stdio.h>

#define PI 3.14159265358979323846
#define PI2 (PI + PI)
#define DEGTORAD(x) ((x) * PI / 180.0)

inline float clamp01(float v) {
    return v > 1 ? 1 : v < 0 ? 0 : v;
}

inline float lerp(float src, float dst, float t) {
    return src + (dst - src) * t;
}

inline double angle_wrap(float angle)
{
    return angle - PI2 * floor(angle / PI2);
}

float slerp(float src_rad, float dst_rad, float t);

color color_lerp(color src, color dst, float t);

vector2 vector2_lerp(vector2 src, vector2 dst, float t);
float vector2_angle(vector2 from, vector2 to);
vector2 vector2_from_angle(float angle, float distance);
vector2 vector2_add(vector2 from, vector2 to);
vector2 vector2_sub(vector2 from, vector2 to);
vector2 vector2_rotate(vector2 v, float angle);
vector2 vector2_scale(vector2 v, float scale);

vector2 bezier_evaluate(vector2* points, float t);
void bezier_rasterize(vector2* points, segment* segments, float start_width, float end_width, int segment_count);

segment segment_lerp(segment from, segment to, float t);
segment segment_evaluate(segment* segments, int count, float t);

#endif