#include "pipe.h"
#include "mathg.h"
#include "draw.h"
#include "transform.h"

pipe pipe_create_from_bezier(bezier* bezier, float start_width, float end_width)
{
    pipe p;
    p.bezier = bezier;
    p.start_width = start_width;
    p.end_width = end_width;
    bezier_rasterize(bezier, p.segments, start_width, end_width, PIPE_SEGMENT_TESSELATION_COUNT);
    return p;
}

void pipe_draw(pipe* pipe) 
{
    segment* segments = pipe->segments;

    draw_switch_layer(LAYER_FG);

    for(int i = 1; i < 8; i++) 
    {
        segment seg = segment_evaluate(segments, 16, i / 7.0f);
        
        vector2 u = vector2_add(seg.position, vector2_from_angle(seg.angle + DEGTORAD(90), seg.width));
        vector2 d = vector2_add(seg.position, vector2_from_angle(seg.angle - DEGTORAD(90), seg.width));

        vector2 t1 = transform_apply(u, 1);
        vector2 t2 = transform_apply(vector2_lerp(u, d, 0.2f), 0.9f);
        vector2 t3 = transform_apply(vector2_lerp(u, d, 0.4f), 0.85f);
        vector2 t4 = transform_apply(vector2_lerp(u, d, 0.6f), 0.85f);
        vector2 t5 = transform_apply(vector2_lerp(u, d, 0.8f), 0.9f);
        vector2 t6 = transform_apply(d, 1);

        draw_line(t1.x, t1.y, t2.x, t2.y, 80);
        draw_line(t2.x, t2.y, t3.x, t3.y, 60);
        draw_line(t3.x, t3.y, t4.x, t4.y, 40);
        draw_line(t4.x, t4.y, t5.x, t5.y, 60);
        draw_line(t5.x, t5.y, t6.x, t6.y, 80);
    }

    for(int i = 1; i < 16; i++) 
    {
        segment s1 = segments[i - 1];
        segment s2 = segments[i];
        
        vector2 u1 = transform_apply(vector2_add(s1.position, vector2_from_angle(s1.angle + DEGTORAD(90), s1.width)), 1);
        vector2 u2 = transform_apply(vector2_add(s2.position, vector2_from_angle(s2.angle + DEGTORAD(90), s2.width)), 1);
        vector2 d1 = transform_apply(vector2_add(s1.position, vector2_from_angle(s1.angle - DEGTORAD(90), s1.width)), 1);
        vector2 d2 = transform_apply(vector2_add(s2.position, vector2_from_angle(s2.angle - DEGTORAD(90), s2.width)), 1);

        draw_switch_layer(LAYER_FG);
        draw_line(u1.x, u1.y, u2.x, u2.y, 255);
        draw_line(d1.x, d1.y, d2.x, d2.y, 255);

        draw_switch_layer(LAYER_BG);
        draw_triangle(u1.x, u1.y, u2.x, u2.y, d1.x, d1.y, 0);
        draw_triangle(d1.x, d1.y, d2.x, d2.y, u2.x, u2.y, 0);
    }
}