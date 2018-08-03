#include "mathg.h"
#include "math.h"

float slerp(float src_rad, float dst_rad, float t) 
{
    return lerp(angle_wrap(src_rad), angle_wrap(dst_rad), t);
}

vector2 vector2_lerp(vector2 src, vector2 dst, float t) 
{
    vector2 r;
    r.x = lerp(src.x, dst.x, t);
    r.y = lerp(src.y, dst.y, t);
    return r;
}

float vector2_angle(vector2 from, vector2 to) 
{
    return atan2f(to.y - from.y, to.x - from.x);
}

vector2 vector2_from_angle(float angle, float distance) 
{
    vector2 v;
    v.x = cos(angle) * distance;
    v.y = sin(angle) * distance;
    return v;
}

vector2 vector2_add(vector2 v1, vector2 v2) 
{
    vector2 v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

vector2 vector2_sub(vector2 v1, vector2 v2) 
{
    vector2 v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

vector2 vector2_rotate(vector2 v, float angle)
{
    vector2 r;
    float c = cos(angle);
    float s = sin(angle);
    r.x = v.x * c - v.y * s;
    r.y = v.x * s + v.y * c;
    return r;
}

vector2 vector2_scale(vector2 vector, float scale) 
{
    vector2 v;
    v.x = vector.x * scale;
    v.y = vector.y * scale;
    return v;
}

color color_lerp(color src, color dst, float t) 
{
    color c;
    c.r = (byte) lerp(src.r, dst.r, t);
    c.g = (byte) lerp(src.g, dst.g, t);
    c.b = (byte) lerp(src.b, dst.b, t);
    return c;
}

vector2 bezier_evaluate(vector2* points, float t) 
{
    t = clamp01(t);
    vector2 a1 = vector2_lerp(points[0], points[1], t);
    vector2 a2 = vector2_lerp(points[1], points[2], t);
    vector2 a3 = vector2_lerp(points[2], points[3], t);
    vector2 b1 = vector2_lerp(a1, a2, t);
    vector2 b2 = vector2_lerp(a2, a3, t);
    return vector2_lerp(b1, b2, t);
}

void bezier_rasterize(vector2* points, segment* segments, float start_width, float end_width, int segment_count) 
{
    for(int i = 0; i < segment_count; i++) 
    {
        float t = i / (float) (segment_count - 1);
        float tl = clamp01(t - 0.01f);
        float tr = clamp01(t + 0.01f);

        vector2 lpoint = bezier_evaluate(points, tl);
        vector2 point = bezier_evaluate(points, t);
        vector2 rpoint = bezier_evaluate(points, tr);

        segment s;
        
        s.width = lerp(start_width, end_width, t);
        s.angle = vector2_angle(rpoint, lpoint);
        s.position = point;
        
        segments[i] = s;
    }
}

segment segment_lerp(segment from, segment to, float t)
{
    segment s;
    s.position = vector2_lerp(from.position, to.position, t);
    s.width = lerp(from.width, to.width, t);
    s.angle = slerp(from.angle, to.angle, t);
    return s;
}

segment segment_evaluate(segment* segments, int count, float t) 
{
    t = clamp01(t) * (count - 1);
    int index = floor(t);
    float l = t - index;

    if(l == 0) 
    {
        return segments[index];
    }
    else 
    {
        return segment_lerp(segments[index], segments[index + 1], l);
    }
}